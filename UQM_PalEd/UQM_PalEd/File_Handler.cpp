// DLL for .ct handling


#include "File_Handler.h"

using namespace Handler;
using namespace System::Windows::Forms;

void File_Handler::provokeMessageBox(String^ s, bool err)
{
    MessageBox::Show(s, err ? "Error" : "Warning", MessageBoxButtons::OK, err ? MessageBoxIcon::Error : MessageBoxIcon::Warning);
}

bool File_Handler::checkFileFormat(BinaryReader^ br)
{
    // Check compression
    {
        while (br->BaseStream->Position < ENCRYPTION_LENGTH)
        {
            if (br->ReadByte() != 0xFF)
            {
                provokeMessageBox("File is not correctly compressed or damaged!", true);
                return false;
            }
        }
    }

    // Check White spot
    {
        while (br->BaseStream->Position < WHITE_SPOT_LENGTH)
        {
            if (br->ReadByte() != 0x00)
            {
                provokeMessageBox("File is damaged at pos " + br->BaseStream->Position, false);
            }
        }
    }

    // Get Num of color tables
    {
        array<Byte>^ bytes = gcnew array<Byte>(2);
        for (int i = 1; br->BaseStream->Position < NUM_OF_TABLES; i--)
        {
            bytes[i] = br->ReadByte();
        }
        tableCount = BitConverter::ToInt16(bytes, 0);

        if (tableCount < 1)
        {
            provokeMessageBox("Wrong number of tables!", true);
            return false;
        }
    }

    // Check unused space of 4 bytes
    {
        while (br->BaseStream->Position < UNUSED)
        {
            if (br->ReadByte() != 0x00)
            {
                provokeMessageBox("File is not correct in unused space! Please check at pos " + br->BaseStream->Position, false);
            }
        }
    }

    // Get length of tables
    {
        array<Byte>^ bytes = gcnew array<Byte>(NUM_BYTES_PER_TABLE_LENGTH);
        
        for (int i = 0; i < tableCount; i++)
        {
            for (int j = 3; br->BaseStream->Position < UNUSED + NUM_BYTES_PER_TABLE_LENGTH * (i + 1); j--)
            {
                bytes[j] = br->ReadByte();
            }
            tableLength[i] = BitConverter::ToInt32(bytes, 0);

            if (tableLength[i] < 1)
            {
                provokeMessageBox("Incorrect length of table " + (i + 1), true);
                return false;
            }
            if (tableLength[i] > (256 * 3 + 2))
            {
                if (tableCount != 1 || (tableLength[i] - 2) % 256 != 0)
                {
                    provokeMessageBox("Table length is too large and do not reflect uqm.ct format!", true);
                    return false;
                }

                segMode = true;
                segCount = (tableLength[i] - 2) / (256 * BYTES_PER_COLOR);
            }
            else
            {
                segMode = false;
                segCount = 0;
            }
        }
    }
    // Check remaining length
    {
        int controlSum = LENGTH_OF_TECH_BYTES + (NUM_BYTES_PER_TABLE_LENGTH * tableCount);

        for (int i = 0; i < tableCount; i++)
        {
            controlSum += tableLength[i];
        }

        //provokeMessageBox("Length is " + tableLength[0], false);

        if (br->BaseStream->Length != controlSum)
        {
            provokeMessageBox("File length is incorrect!", true);
            return false;
        }
    }
    return true;
}

File_Handler::File_Handler(void)
{
    fileName = "Unidentified";
    tableLength = gcnew array<int>(MAX_TABLES);
    content = "No Data\n";
    tableCount = 0;
    currTable = gcnew array<Color>(MAX_COLORS_PER_TABLE);
    currIndex = 0;
    segMode = false;
    segCount = 0;
}

File_Handler::~File_Handler()
{
    this->!File_Handler();
}

void File_Handler::setFileName(String^ name)
{
	if (name)
		fileName = name;
	else
		fileName = "Unidentified";
}

void File_Handler::extractContent(void)
{
    try
    {
        FileStream^ fs = gcnew FileStream(fileName, FileMode::Open);
        BinaryReader^ br = gcnew BinaryReader(fs);
        
        if (checkFileFormat(br))
        {
            fs->Close();
            setCurrentTable(0);
        }
        else
            fs->Close();
    }
    catch (Exception^ e)
    {
        if (dynamic_cast<FileNotFoundException^>(e))
            provokeMessageBox("Cannot find file with that name!", true);
        else
            provokeMessageBox(e->ToString(), true);
    }
}

array<Color>^ File_Handler::getCurrentTable()
{
    return currTable;
}

void File_Handler::setCurrentTable(int index)
{
    int start = LENGTH_OF_TECH_BYTES + (NUM_BYTES_PER_TABLE_LENGTH * tableCount);
    int end = start;
    int i = 0;
    int plMultiplyer = 1;// for planet in-game view TODO: implement later

    if (!segMode)
    {
        if (index > tableCount)
        {
            provokeMessageBox("Incorrect index!", true);
            return;
        }

        end += tableLength[0];

        while (i < index)
        {
            start = end;
            end += tableLength[i];
            i++;
        }

        if ((end - start) == 0 || (end - start - 2) % BYTES_PER_COLOR != 0)
        {
            provokeMessageBox("Incorrect number of cluts!", true);
            return;
        }
        start += 2;// skip indexes of first and last clut
    }
    else
    {
        start = end + 2 + (index * (MAX_COLORS_PER_TABLE * BYTES_PER_COLOR));
        end = start + (MAX_COLORS_PER_TABLE * BYTES_PER_COLOR);
    }

    try
    {
        FileStream^ fs = gcnew FileStream(fileName, FileMode::Open);
        BinaryReader^ br = gcnew BinaryReader(fs);
        int r, g, b = 0;

        br->BaseStream->Position = start;

        for (int j = 0; br->BaseStream->Position < end; j++)
        {
            r = br->ReadByte();
            g = br->ReadByte();
            b = br->ReadByte();
            
            currTable[j] = Color::FromArgb(r, g, b);
        }
        fs->Close();
        currIndex = index;
    }
    catch (Exception^ e)
    {
        if (dynamic_cast<FileNotFoundException^>(e))
            provokeMessageBox("Cannot read colors!", true);
        else
            provokeMessageBox(e->ToString(), true);
    }
}

String^ File_Handler::getFileName(void)
{
    String^ fname = Path::GetFileName(fileName);
    return fname;
}

int Handler::File_Handler::getNumTables(void)
{
    if (!segMode)
        return tableCount;
    else
        return segCount;
}

int Handler::File_Handler::getCurrIndex(void)
{
    return currIndex;
}

File_Handler::!File_Handler()
{
    delete fileName;
    delete currTable;
    delete tableLength;
    delete content;
    currIndex = 0;
    tableCount = 0;
}
