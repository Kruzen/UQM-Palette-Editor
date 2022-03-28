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

unsigned int FManager::FileManager::getFileExtensionCode(String^ fName)
{
    String^ extention = Path::GetExtension(fName);
    int count = System::Text::Encoding::ASCII->GetByteCount(extention);

    if (count > 4 || count < 2)
        throw gcnew FormatException("Wrong file format!");

    if (count < 4)
    {
        for (int i = 0; i < (4 - count); i++)
            extention += " ";
    }
    return BitConverter::ToInt32(System::Text::Encoding::ASCII->GetBytes(extention), 0);
}

void FManager::FileManager::checkCT(BinaryReader^ br, String^ fName)
{// check format of .ct file
    long pos;
    unsigned int p_count;
    array<int>^ p_lengths;

    // Check compression {0xFFFFFFFF}
    if (br->ReadUInt32() != CT)
    {
        pos = br->BaseStream->Position;
        br->Close();
        throw gcnew FormatException("File is not compressed! Byte: " + pos);
    }

    // Check White spot {0x0000}
    if (br->ReadUInt16() != 0)
    {
        pos = br->BaseStream->Position;
        br->Close();
        throw gcnew FormatException("File is damaged! Byte: " + pos);
    }

    // Get Num of color tables {0x0001}
    p_count = br->ReadUInt16();
    p_count = FLIP_INT16(p_count);
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
        p_lengths[i] = FLIP_INT32(p_lengths[i]);

        if (p_lengths[i] == 0 || (p_lengths[i] - 2) % 3 != 0)// not 3 bytes per color
        {
            pos = br->BaseStream->Position;
            br->Close();
            throw gcnew FormatException("Incorrect length of table " + (i + 1) + "! Byte: " + p_lengths[i]);
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
    int p_count = 1;
    array<int>^ p_lengths = gcnew array<int>(p_count);

    // Check signature
    if (br->ReadUInt32() != RIFF)
    {
        pos = br->BaseStream->Position;
        br->Close();
        throw gcnew FormatException("Wrong file length! Byte: " + pos);
    }

    // Check length of file
    if (br->ReadUInt32() != br->BaseStream->Length - 8)
    {
        pos = br->BaseStream->Position;
        br->Close();
        throw gcnew FormatException("Wrong file length! Byte: " + pos);
    }

    // Check PAL signature
    if (br->ReadUInt32() != PAL)
    {
        pos = br->BaseStream->Position;
        br->Close();
        throw gcnew FormatException("RIFF file is not PAL! Byte: " + pos);
    }

    // Check data signature
    if (br->ReadUInt32() != DATA)
    {
        pos = br->BaseStream->Position;
        br->Close();
        throw gcnew FormatException("File is corrupted! Byte: " + pos);
    }

    // Check data length
    if (br->ReadUInt32() != br->BaseStream->Length - br->BaseStream->Position)
    {
        pos = br->BaseStream->Position;
        br->Close();
        throw gcnew FormatException("Wrong data length! Byte: " + pos);
    }

    // Check version
    if (br->ReadUInt16() == 0)
    {
        pos = br->BaseStream->Position;
        br->Close();
        throw gcnew FormatException("Wrong version! Byte: " + pos);
    }

    // Check length
    p_lengths[0] = br->ReadUInt16() * BYTES_PER_COLOR_RIFF;
    if (p_lengths[0] == 0)
    {
        pos = br->BaseStream->Position;
        br->Close();
        throw gcnew FormatException("Wrong palette length! Byte: " + pos);
    }

    this->reInitValues(fName, p_count, p_lengths);// values verified - accept them
}
void FManager::FileManager::checkACT(BinaryReader^ br, String^ fName)
{
    //throw gcnew FormatException("Length " + br->BaseStream->Length);
    if (br->BaseStream->Length == 768)
        this->reInitValues(fName, 1, gcnew array<int>{ MAX_COLORS_PER_TABLE * BYTES_PER_COLOR });
    else if (br->BaseStream->Length == 772)
    {
        br->BaseStream->Position = 769;
        this->reInitValues(fName, 1, gcnew array<int>{br->ReadByte() * BYTES_PER_COLOR});
    }
    else
        throw gcnew FormatException("Wrong file length! Adobe format");
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

FManager::FileManager::FileManager(String^ filename, int fileType, int paletteCount, array<int>^ paletteLengths)
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
}

FManager::FileManager::~FileManager(void)
{// destructor
    this->!FileManager();
}

void FManager::FileManager::checkFileFormat(String^ fname)
{// checking file format by their inner structure
    BinaryReader^ br = gcnew BinaryReader(gcnew FileStream(fname, FileMode::Open));

    switch (this->getFileExtensionCode(fname))
    {
        case CT_SIGNATURE:
        {
            fileType = CT_FILE;
            this->checkCT(br, fname);
            break;
        }
        case PAL_SIGNATURE:
        {
            fileType = RIFF_FILE;
            this->checkRIFF(br, fname);
            break;
        }
        case ACT_SIGNATURE:
        {
            fileType = ACT_FILE;
            this->checkACT(br, fname);
            break;
        }
        default:
        {
            br->Close();
            throw gcnew FormatException("Unknonw file format!");
        }
    }
   
    br->Close();
}

array<Byte>^ FManager::FileManager::extractColorBytes(void)
{// extract color bytes from file
    BinaryReader^ br = gcnew BinaryReader(gcnew FileStream(fileName, FileMode::Open));
    array<Byte>^ cBytes;
    int start;
    int length;

    switch (fileType)
    {
        case CT_FILE:
        {
            br->BaseStream->Position = CT_TECH_BYTE_LENGTH + (NUM_BYTES_PER_TABLE_LENGTH * paletteCount);
            length = br->BaseStream->Length - br->BaseStream->Position;
            break;
        }
        case RIFF_FILE:
        {
            br->BaseStream->Position = RIFF_TECH_BYTE_LENGTH;
            length = br->BaseStream->Length - br->BaseStream->Position;
            break;
        }
        case ACT_FILE:
        {
            br->BaseStream->Position = 0;
            length = paletteLengths[0];
            break;
        }
        default:
        {
            br->Close();
            throw gcnew FormatException("Wrong file format!");
            break;
        }
    }   

    cBytes = gcnew array<Byte>(length);

    for (int i = 0; i < length; i++)
        cBytes[i] = br->ReadByte();

    br->Close();

    return cBytes;
}
String^ FManager::FileManager::getFileNameFromPath(void)
{
    return Path::GetFileName(fileName);
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
        delete paletteLengths;
    }
}
