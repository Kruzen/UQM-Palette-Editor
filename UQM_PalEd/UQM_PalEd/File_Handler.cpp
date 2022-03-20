// Ur-Quan Masters Palette Editor v0.0.5

/*
 *	This program is created as a tool to view/modify/create
 *	Ur-Quan Masters .ct (color table) files. No source code from
 *	the original game was used besides a couple of macros to form in-game planet
 *  colors. Program algorithms are based on dev doc	file
 *  (see ..\doc\devel\strtab file in Ur-Quan Masters repository).
 *
 *	"Ur-Quan Masters" was originally created by Fred Ford and Paul Reiche III.
 *	Copyright Paul Reiche, Fred Ford. 1992-2002
 *	All trademarks belong to their respective owners.
 *
 *	This is a FREE software. You are free to edit and distribute it.
 *  DO NOT use it for financial profit.
 *	Created by Kruzen. 2022
 */


//.ct handling

#include "File_Handler.h"

using namespace Handler;

void File_Handler::reInitValues(String^ fileName, int tableCount, array<int>^ tableLength)
{// "constructor"
    this->fileName = fileName;
    this->tableCount = tableCount;
    this->tableLength = tableLength;
    table = gcnew array<ColorTable^>(this->tableCount);
    for (int i = 0; i < this->tableCount; i++)
        table[i] = gcnew ColorTable();
}

File_Handler::File_Handler(void)
{// default constructor
    fileName = "Unidentified";
    tableLength = gcnew array<int>(1);
    table = gcnew array<ColorTable^>(1);
    content = "No Data\n";
    tableCount = 0;
}

File_Handler::~File_Handler()
{// destructor
    this->!File_Handler();
}

void File_Handler::checkFileFormat(String^ fname)
{// check if selected file is in correct format and can be read by UQM code
    FileStream^ fs = gcnew FileStream(fname, FileMode::Open);
    BinaryReader^ br = gcnew BinaryReader(fs);

    int pos;
    int t_count;
    array<int>^ t_length;

    // Check compression {0xFFFFFFFF}
    {
        while (br->BaseStream->Position < ENCRYPTION_LENGTH)
        {
            if (br->ReadByte() != 0xFF)
            {
                pos = br->BaseStream->Position;
                fs->Close();
                throw gcnew CTException("File is not correctly compressed or damaged! Byte: " + pos, true);
                return;
            }
        }
    }

    // Check White spot {0x0000}
    {
        while (br->BaseStream->Position < WHITE_SPOT_LENGTH)
        {
            if (br->ReadByte() != 0x00)
            {
                pos = br->BaseStream->Position;
                fs->Close();
                throw gcnew CTException("File is damaged! Byte: " + pos, false);
                return;
            }
        }
    }

    // Get Num of color tables {0x0001}
    {
        array<Byte>^ bytes = gcnew array<Byte>(2);
        for (int i = 1; br->BaseStream->Position < NUM_OF_TABLES; i--)
        {
            bytes[i] = br->ReadByte();
        }
        t_count = BitConverter::ToInt16(bytes, 0);// converts in reverse

        if (t_count < 1)
        {
            pos = br->BaseStream->Position;
            fs->Close();
            throw gcnew CTException("Wrong number of tables! Byte: " + pos, true);
            return;
        }
    }

    // Check unused space of 4 bytes {0x00000000}
    {
        while (br->BaseStream->Position < UNUSED)
        {
            if (br->ReadByte() != 0x00)
            {
                pos = br->BaseStream->Position;
                fs->Close();
                throw gcnew CTException("File is not correct in unused space! Byte: " + pos, false);
                return;
            }
        }
    }

    // Get length of tables {0x00000302}
    {
        array<Byte>^ bytes = gcnew array<Byte>(NUM_BYTES_PER_TABLE_LENGTH);
        t_length = gcnew array<int>(t_count);

        for (int i = 0; i < t_count; i++)
        {
            for (int j = 3; br->BaseStream->Position < UNUSED + NUM_BYTES_PER_TABLE_LENGTH * (i + 1); j--)
            {
                bytes[j] = br->ReadByte();
            }
            t_length[i] = BitConverter::ToInt32(bytes, 0);// converts in reverse

            if (t_length[i] < 1 || (t_length[i] - 2) % 3 != 0)// not 3 bytes per color
            {
                pos = br->BaseStream->Position;
                fs->Close();
                throw gcnew CTException("Incorrect length of table " + (i + 1) + "! Byte: " + pos, true);
                return;
            }
        }
    }
    // Check remaining length
    {
        int controlSum = LENGTH_OF_TECH_BYTES + (NUM_BYTES_PER_TABLE_LENGTH * t_count);

        for (int i = 0; i < t_count; i++)
        {
            controlSum += t_length[i];
        }

        if (br->BaseStream->Length != controlSum)
        {
            pos = br->BaseStream->Length;
            fs->Close();
            throw gcnew CTException("File length is incorrect! Control sum: " + controlSum + ". Stream length: " + pos, true);
            return;
        }
    }

    fs->Close();

    this->reInitValues(fname, t_count, t_length);// values verified - accept them
}

void Handler::File_Handler::extractContent(void)
{// fill all segments of all tables
    FileStream^ fs = gcnew FileStream(fileName, FileMode::Open);
    BinaryReader^ br = gcnew BinaryReader(fs);
    int endByte_index;
    int numBytes;

    br->BaseStream->Position = LENGTH_OF_TECH_BYTES + (NUM_BYTES_PER_TABLE_LENGTH * tableCount);

    for (int i = 0; i < tableCount; i++)// for every table determine the amount of segments and then fill them
    {// fill structures from selected file.ct
        int segs = (tableLength[i] - 2) / (MAX_BYTES_PER_SEGMENT);

        if (segs < 1)
            segs = 1;// one segment of less than 256 colors (i.e. planet table)
        else
            segs += (((tableLength[i] - 2) % (MAX_BYTES_PER_SEGMENT)) != 0);// +1 segment if it's <256 colors in length 

        table[i]->setNumSegs(segs);
        table[i]->setNumColors((tableLength[i] - 2) / 3);

        endByte_index = br->BaseStream->Position + tableLength[i];
        br->BaseStream->Position += 2; // skip indexes and go straight to colors

        for (int j = 0; j < segs; j++)
        {// Fill segments
            numBytes = MIN(MAX_BYTES_PER_SEGMENT, endByte_index - br->BaseStream->Position);
            table[i]->setSegLength(j, numBytes / 3);
            table[i]->setSeg(j, br->ReadBytes(numBytes));
        }
    }

    fs->Close();
}

array<Color>^ File_Handler::getTable(int t_index, int s_index)
{
    return table[t_index]->returnSeg(s_index);
}

array<Color>^ Handler::File_Handler::getTable(void)
{
    return table[0]->returnSeg(0);
}

int Handler::File_Handler::getNumSegs(int t_index)
{
    return table[t_index]->getNumSegs();
}

int Handler::File_Handler::getNumColors(int t_index)
{
    return table[t_index]->getNumColors();
}

void File_Handler::setFileName(String^ name)
{
	if (name)
		fileName = name;
	else
		fileName = "Unidentified";
}

String^ File_Handler::getFileName(void)
{// get filename from full path
    String^ fname = Path::GetFileName(fileName);
    return fname;
}

int File_Handler::getNumTables(void)
{
    return tableCount;
}

int Handler::File_Handler::getNumSegColors(int t_index, int s_index)
{
    return table[t_index]->getSegLength(s_index);
}

File_Handler::!File_Handler()
{// finalizer
    delete fileName;
    delete tableLength;
    delete content;
    tableCount = 0;
}
/* Custom exception - contains a boolean to determine: is it a warning or an error? */
Handler::CTException::CTException(void)
{
    message = "Unknown error";
    warning = false;
}

Handler::CTException::CTException(String^ message, bool warning)
{
    this->message = message;
    this->warning = warning;
}

bool Handler::CTException::IsWarning(void)
{
    return warning;
}

String^ Handler::CTException::ToString(void)
{
    return message;
}
