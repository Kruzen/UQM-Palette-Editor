// Ur-Quan Masters Palette Editor v0.0.9

/*
 *	This program is created as a tool to view/modify/create
 *	Ur-Quan Masters .ct (color table) files. No source code from
 *	the original game was used. Program algorithms are based on dev doc
 *	file (see ..\doc\devel\strtab file in Ur-Quan Masters repository).
 *
 *	"Ur-Quan Masters" was originally created by Fred Ford and Paul Reiche III.
 *	Copyright Paul Reiche, Fred Ford. 1992-2002
 *	All trademarks belong to their respective owners.
 *
 *	This is a FREE software. DO NOT use it for financial profit.
 *	Created by Kruzen. 2022
 */

 // .ct file manager cpp
#include "FileManager.h"
#include "constdef.h"

using namespace FManager;

/* private methods */
void FManager::FileManager::reInitValues(String^ fName, int p_count, array<int>^ p_lengths)
{
    fileName = fName;
    paletteCount = p_count;

    if (paletteLengths)
    {
        Array::Clear(paletteLengths, 0, paletteLengths->Length);
        delete paletteLengths;
    }
    paletteLengths = gcnew array<int>(paletteCount);
    paletteLengths = p_lengths;
}

void FManager::FileManager::checkCT(BinaryReader^ br, String^ fName)
{// check format of .ct file
    long pos;
    unsigned int p_count;
    array<int>^ p_lengths;

    // Check White spot {0x0000}
    if (br->ReadUInt16() != 0)
    {
        pos = br->BaseStream->Position;
        br->Close();
        throw gcnew FormatException("File is damaged! Byte: " + pos);
    }

    // Get Num of color tables {0x0001}
    p_count = br->ReadUInt16();
    if (p_count == 0)
    {
        pos = br->BaseStream->Position;
        br->Close();
        throw gcnew FormatException("Wrong number of tables! Byte: " + pos);
    }

    // Check unused space of 4 bytes {0x00000000}
    if (br->ReadUInt32() != 0)
    {
        pos = br->BaseStream->Position;
        br->Close();
        throw gcnew FormatException("File is not correct in unused space! Byte: " + pos);
    }

    // Get length of tables {0x00000302}
    p_lengths = gcnew array<int>(p_count);
    for (unsigned int i = 0; i < p_count; i++)
    {
        p_lengths[i] = br->ReadUInt32();

        if (p_lengths[i] == 0 || (p_lengths[i] - 2) % 3 != 0)// not 3 bytes per color
        {
            pos = br->BaseStream->Position;
            br->Close();
            throw gcnew FormatException("Incorrect length of table " + (i + 1) + "! Byte: " + pos);
        }
    }

    // Check remaining length
    {
        int controlSum = CT_TECH_BYTE_LENGTH + (NUM_BYTES_PER_TABLE_LENGTH * p_count);

        for (int i = 0; i < p_count; i++)
        {
            controlSum += p_lengths[i];
        }

        if (br->BaseStream->Length != controlSum)
        {
            pos = br->BaseStream->Length;
            br->Close();
            throw gcnew FormatException("File length is incorrect! Control sum: " + controlSum + ". Stream length: " + pos);
        }
    }

    this->reInitValues(fName, p_count, p_lengths);// values verified - accept them
}

void FManager::FileManager::checkRIFF(BinaryReader^ br, String^ fName)
{// check format of .pal file
    int pos;
    array<int>^ p_lengths;


}
/*
 *
 *
 *
 *
 * public methods */
FManager::FileManager::FileManager(void)
{// default constructor

    fileName = "Unidentified";
    fileType = CT_FILE;
    paletteCount = 1;

    if (paletteLengths)
    {
        Array::Clear(paletteLengths, 0, paletteLengths->Length);
        delete paletteLengths;
    }
    this->paletteLengths = gcnew array<int>(paletteCount);
    this->paletteLengths[0] = 1;
}

FManager::FileManager::FileManager(String^ filename, int fileType, int paletteCount, array<int>^ paletteLengths, array<Byte>^ cBytes)
{// constructor
    this->fileName = filename;
    this->fileType = fileType;
    this->paletteCount = paletteCount;

    if (this->paletteLengths)
    {
        Array::Clear(this->paletteLengths, 0, this->paletteLengths->Length);
        delete this->paletteLengths;
    }
    this->paletteLengths = gcnew array<int>(this->paletteCount);
    this->paletteLengths = paletteLengths;

    if (this->cBytes)
    {
        Array::Clear(this->cBytes, 0, this->cBytes->Length);
        delete this->cBytes;
    }
    this->cBytes = gcnew array<Byte>(cBytes->Length);
    this->cBytes = cBytes;
}

FManager::FileManager::~FileManager(void)
{// destructor
    this->!FileManager();
}

void FManager::FileManager::checkFileFormat(String^ fname)
{// checking file format by their inner structure
    BinaryReader^ br = gcnew BinaryReader(gcnew FileStream(fname, FileMode::Open));

    unsigned int sign = br->ReadUInt32();

    if (sign == CT_SIGNATURE)
    {
        fileType = CT_FILE;
        this->checkCT(br, fname);
    }
    else if (sign == RIFF_SIGNATURE)
    {
        fileType = RIFF_FILE;
        this->checkRIFF(br, fname);
    }
    else
    {
        br->Close();
        throw gcnew FormatException("Wrong file format!");
    }
    br->Close();
}

void FManager::FileManager::extractColorBytes(void)
{// main setter for cBytes
    BinaryReader^ br = gcnew BinaryReader(gcnew FileStream(fileName, FileMode::Open));

    int start;
    int length;

    if (fileType == CT_FILE)
        br->BaseStream->Position = CT_TECH_BYTE_LENGTH + (NUM_BYTES_PER_TABLE_LENGTH * paletteCount);
    else if (fileType == CT_FILE)
        br->BaseStream->Position = RIFF_TECH_BYTE_LENGTH;
    else
    {
        br->Close();
        throw gcnew FormatException("Wrong file format!");
    }

    br->BaseStream->Position = CT_TECH_BYTE_LENGTH + (NUM_BYTES_PER_TABLE_LENGTH * paletteCount);
    length = br->BaseStream->Length - br->BaseStream->Position;

    if (cBytes)
    {
        Array::Clear(cBytes, 0, cBytes->Length);
        delete this->cBytes;
    }
    cBytes = gcnew array<Byte>(length);

    for (int i = 0; i < length; i++)
        cBytes[i] = br->ReadByte();

    br->Close();    
}
/*
 *
 *
 *
 *
 * get methods */
String^ FManager::FileManager::getFileName(void)
{
    return fileName;
}

int FManager::FileManager::getFileType(void)
{
    return fileType;
}

int FManager::FileManager::getPaletteCount(void)
{
    return paletteCount;
}

array<int>^ FManager::FileManager::getPaletteLengths(void)
{
    return paletteLengths;
}

array<Byte>^ FManager::FileManager::getColorBytes(void)
{
    if (cBytes)
        return cBytes;
    else
        throw gcnew NullReferenceException("Color bytes are not declared!");
}
/*
 *
 *
 *
 *
 * set methods */
void FManager::FileManager::setFileName(String^ fileName)
{
    this->fileName = fileName;
}

void FManager::FileManager::setFileType(int type)
{
    fileType = type;

    if (fileType > LAST_FILE_TYPE)
        fileType = LAST_FILE_TYPE;
    if (fileType < CT_FILE)
        fileType = CT_FILE;
}

void FManager::FileManager::setPaletteCount(int paletteCount)
{
    this->paletteCount = paletteCount;
}

void FManager::FileManager::setPaletteLengths(array<int>^ paletteLengths)
{
    if (this->paletteLengths)
    {
        Array::Clear(this->paletteLengths, 0, this->paletteLengths->Length);
        delete this->paletteLengths;
    }
    this->paletteLengths = gcnew array<int>(paletteLengths->Length);
    this->paletteLengths = paletteLengths;
}

void FManager::FileManager::setColorBytes(array<Byte>^ cBytes)
{
    if (this->cBytes)
    {
        Array::Clear(this->cBytes, 0, this->cBytes->Length);
        delete this->cBytes;
    }
    this->cBytes = gcnew array<Byte>(cBytes->Length);
    this->cBytes = cBytes;
}
/*
 *
 *
 *
 *
 * finalizer */
FManager::FileManager::!FileManager(void)
{
    fileName = "";
    paletteCount = 0;
    fileType = 0;

    if (paletteLengths)
    {
        Array::Clear(paletteLengths, 0, paletteLengths->Length);
        delete this->paletteLengths;
    }

    if (cBytes)
    {
        Array::Clear(cBytes, 0, cBytes->Length);
        delete this->cBytes;
    }
}
