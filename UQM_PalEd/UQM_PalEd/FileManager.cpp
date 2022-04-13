// Ur-Quan Masters Palette Editor

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

array<Byte>^ FManager::FileManager::decryptOldCT(BinaryReader^ br)
{// based on old UQM code
 // sourceforge.net/p/sc2/uqm/ci/initial/tree/sc2/src/sc2code/libs/graphics/cmap.c @line 41

    array<Byte>^ decBytes = gcnew array<Byte>(MAX_BYTES_PER_SEGMENT * paletteCount);
    Byte r, g, b;
    int cval;
    int k;

    for (int p = 0; p < paletteCount; p++)
    {
        br->BaseStream->Position += 2;

        for (int i = 0; i < 32;)
        {
            cval = br->ReadUInt32();

            cval = FLIP_INT32(cval);

            r = (cval >> 26) & 0x1f;
            g = (cval >> 21) & 0x1f;
            b = (cval >> 16) & 0x1f;

            for (int j = 0; j < 8; ++j)
            {
                k = ((j << 5) + i) + (MAX_COLORS_PER_TABLE * p);

                decBytes[(k * BYTES_PER_COLOR) + RED] = r * (j + 1);
                decBytes[(k * BYTES_PER_COLOR) + GREEN] = g * (j + 1);
                decBytes[(k * BYTES_PER_COLOR) + BLUE] = b * (j + 1);
            }

            ++i;

            r = (cval >> 10) & 0x1f;
            g = (cval >> 5) & 0x1f;
            b = cval & 0x1f;

            for (int j = 0; j < 8; ++j)
            {
                k = ((j << 5) + i) + (MAX_COLORS_PER_TABLE * p);

                decBytes[(k * BYTES_PER_COLOR) + RED] = r * (j + 1);
                decBytes[(k * BYTES_PER_COLOR) + GREEN] = g * (j + 1);
                decBytes[(k * BYTES_PER_COLOR) + BLUE] = b * (j + 1);
            }

            ++i;
        }
    }
    
    return decBytes;
}

void FManager::FileManager::checkCT(String^ fName)
{// check format of .ct file
    BinaryReader^ br = gcnew BinaryReader(gcnew FileStream(fName, FileMode::Open));
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
            if (p_lengths[i] == 66)
            {
                fileType = OLD_CT_FILE;
            }
            else
            {
                pos = br->BaseStream->Position;
                br->Close();
                throw gcnew FormatException("Incorrect length of table " + (i + 1) + "! Byte: " + p_lengths[i]);
            }
        }
    }

    // Check remaining length
    {
        int controlSum = CT_TECH_BYTE_LENGTH + (NUM_BYTES_PER_TABLE_LENGTH * p_count);

        for (int i = 0; i < p_count; i++)
        {
            controlSum += p_lengths[i];

            p_lengths[i] -= 2;
            if (fileType == OLD_CT_FILE)
                p_lengths[i] = MAX_COLORS_PER_TABLE;// old .ct always had 256 colors after decryption
            else
                p_lengths[i] /= BYTES_PER_COLOR;// leave only colors
        }

        if (br->BaseStream->Length != controlSum)
        {
            pos = br->BaseStream->Length;
            br->Close();
            throw gcnew FormatException("File length is incorrect! Control sum: " + controlSum + ". Stream length: " + pos);
        }
    }
    br->Close();

    this->reInitValues(fName, p_count, p_lengths);// values verified - accept them
}

void FManager::FileManager::checkRIFF(String^ fName)
{// check format of .pal file
    BinaryReader^ br = gcnew BinaryReader(gcnew FileStream(fName, FileMode::Open));
    int pos;
    int p_count = 1;
    array<int>^ p_lengths = gcnew array<int>(p_count);

    // Check signature
    if (br->ReadUInt32() != RIFF)
    {
        pos = br->BaseStream->Position;
        br->Close();
        throw gcnew FormatException("Wrong file format! Byte: " + pos);
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
    p_lengths[0] = br->ReadUInt16();
    if (p_lengths[0] == 0)
    {
        pos = br->BaseStream->Position;
        br->Close();
        throw gcnew FormatException("Wrong palette length! Byte: " + pos);
    }

    br->Close();

    this->reInitValues(fName, p_count, p_lengths);// values verified - accept them
}
void FManager::FileManager::checkACT(String^ fName)
{// chack ACT file
    BinaryReader^ br = gcnew BinaryReader(gcnew FileStream(fName, FileMode::Open));
    if (br->BaseStream->Length == 768)
        this->reInitValues(fName, 1, gcnew array<int>{ MAX_COLORS_PER_TABLE});
    else if (br->BaseStream->Length == 772)
    {
        br->BaseStream->Position = 769;
        this->reInitValues(fName, 1, gcnew array<int>{br->ReadByte()});
    }
    else
    {
        br->Close();
        throw gcnew FormatException("Wrong file length! Adobe format");
    }
    br->Close();
}

void FManager::FileManager::checkXLT(String^ fName)
{
    BinaryReader^ br = gcnew BinaryReader(gcnew FileStream(fName, FileMode::Open));
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
    if (p_count != 1)
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

        if (p_lengths[i] != 262)
        {
            pos = br->BaseStream->Position;
            br->Close();
            throw gcnew FormatException("Incorrect length of table " + (i + 1) + "! Byte: " + p_lengths[i]);

        }
    }
    br->Close();

    this->reInitValues(fName, p_count, p_lengths);// values verified - accept them
}

void FManager::FileManager::writeCT(BinaryWriter^ bw, array<Byte>^ bytes)
{// write uqm .ct file
    bool isPlanet = false;
    int j = 0;

    // tech bytes
    bw->Write(CT);

    bw->Write((unsigned short)0);

    bw->Write((unsigned short)FLIP_INT16(paletteCount));

    bw->Write((unsigned int)0);

    for (int i = 0; i < paletteCount; i++)
        bw->Write((unsigned int)FLIP_INT32((paletteLengths[i] * BYTES_PER_COLOR) + 2));

    if (paletteCount == 3)
        isPlanet = (paletteLengths[0] == 128 && paletteLengths[1] == 128 && paletteLengths[2] == 128);

    // palettes
    for (int i = 0; i < paletteCount; i++)
    {
        int start_index;
        int end_index;

        if (!isPlanet)
        {
            start_index = 0x0A;
            end_index = start_index;
            int segs = paletteLengths[i] / MAX_COLORS_PER_TABLE;

            if (segs < 1)
                segs = 1;// one segment of less than 256 colors (i.e. planet table)
            else
                segs += ((paletteLengths[i] % MAX_COLORS_PER_TABLE) != 0);// +1 segment if it's <256 colors in length

            // to cap some limitations
            if (segs > 20)
                start_index = 0x00;

            end_index += (segs - 1);

            if (end_index > 0xFF)
                end_index = 0xFF;
        }
        else
        {
            start_index = 0x80;
            end_index = 0xFF;
        }


        bw->Write((unsigned char)start_index);
        bw->Write((unsigned char)end_index);

        for (int k = 0; k < paletteLengths[i]; k++)
        {
            bw->Write((unsigned char)bytes[(j * BYTES_PER_COLOR) + RED]);
            bw->Write((unsigned char)bytes[(j * BYTES_PER_COLOR) + GREEN]);
            bw->Write((unsigned char)bytes[(j * BYTES_PER_COLOR) + BLUE]);
            j++;
        }
    }
}

void FManager::FileManager::writeRIFF(BinaryWriter^ bw, array<Byte>^ bytes)
{// write RIFF file
    int length = paletteLengths[0] * BYTES_PER_COLOR_RIFF + RIFF_TECH_BYTE_LENGTH;// determine length of the final file in bytes

    // write tech bytes
    bw->Write(RIFF);

    bw->Write(length - 8);

    bw->Write(PAL);

    bw->Write(DATA);

    bw->Write(length - 20);

    bw->Write((unsigned short)768);

    bw->Write((unsigned short)paletteLengths[0]);

    // write colors (FLAG byte is always 0x00)
    for (int i = 0; i < paletteLengths[0]; i++)
    {
        bw->Write((unsigned char)bytes[(i * BYTES_PER_COLOR) + RED]);
        bw->Write((unsigned char)bytes[(i * BYTES_PER_COLOR) + GREEN]);
        bw->Write((unsigned char)bytes[(i * BYTES_PER_COLOR) + BLUE]);
        bw->Write((unsigned char)0x00);
    }
}
void FManager::FileManager::writeACT(BinaryWriter^ bw, array<Byte>^ bytes)
{
    for (int i = 0; i < paletteLengths[0]; i++)
    {
        bw->Write((unsigned char)bytes[(i * BYTES_PER_COLOR) + RED]);
        bw->Write((unsigned char)bytes[(i * BYTES_PER_COLOR) + GREEN]);
        bw->Write((unsigned char)bytes[(i * BYTES_PER_COLOR) + BLUE]);
    }

    if (paletteLengths[0] < 256)
    {
        for (int i = 0; i < (256 - paletteLengths[0]) * BYTES_PER_COLOR; i++)
            bw->Write((unsigned char)0x00);

        bw->Write((unsigned char)0x00);
        bw->Write((unsigned char)paletteLengths[0]);
        bw->Write((unsigned short)0xFFFF);
    }
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

FManager::FileManager::FileManager(String^ filename, int paletteCount, array<int>^ paletteLengths)
{// constructor
    this->fileName = filename;
    this->fileType = NON;
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
    switch (this->getFileExtensionCode(fname))
    {
        case CT_SIGNATURE:
        {
            fileType = CT_FILE;
            this->checkCT(fname);
            break;
        }
        case PAL_SIGNATURE:
        {
            fileType = RIFF_FILE;
            this->checkRIFF(fname);
            break;
        }
        case ACT_SIGNATURE:
        {
            fileType = ACT_FILE;
            this->checkACT(fname);
            break;
        }
        case XLT_SIGNATURE:
        {
            fileType = XLT_FILE;
            this->checkXLT(fname);
            break;
        }
        default:
            throw gcnew FormatException("Unknonw file format!");
    }   
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
            length = br->BaseStream->Length - br->BaseStream->Position - (2 * paletteCount);

            int k = 0;
            cBytes = gcnew array<Byte>(length);

            for (int i = 0; i < paletteCount; i++)
            {
                br->BaseStream->Position += 2;
                for (int j = 0; j < paletteLengths[i] * BYTES_PER_COLOR; j++, k++)
                    cBytes[k] = br->ReadByte();
            }
            br->Close();
            break;
        }
        case OLD_CT_FILE:
        {
            br->BaseStream->Position = CT_TECH_BYTE_LENGTH + (NUM_BYTES_PER_TABLE_LENGTH * paletteCount);
            
            cBytes = this->decryptOldCT(br);

            br->Close();
            break;
        }
        case RIFF_FILE:
        {
            br->BaseStream->Position = RIFF_TECH_BYTE_LENGTH;
            length = paletteLengths[0] * BYTES_PER_COLOR;

            cBytes = gcnew array<Byte>(length);

            for (int i = 0; i < paletteLengths[0]; i++)
            {
                cBytes[i * BYTES_PER_COLOR + RED] = br->ReadByte();
                cBytes[i * BYTES_PER_COLOR + GREEN] = br->ReadByte();
                cBytes[i * BYTES_PER_COLOR + BLUE] = br->ReadByte();
                br->BaseStream->Position++;
            }

            br->Close();
            break;
        }
        case ACT_FILE:
        {
            br->BaseStream->Position = 0;
            length = paletteLengths[0] * BYTES_PER_COLOR;           

            cBytes = gcnew array<Byte>(length);

            for (int i = 0; i < length; i++)
                cBytes[i] = br->ReadByte();

            br->Close();
            break;
        }
        case XLT_FILE:
        {
            br->BaseStream->Position = CT_TECH_BYTE_LENGTH + paletteCount + 6;
            length = 256;

            cBytes = gcnew array<Byte>(length);

            for (int i = 0; i < length; i++)
                cBytes[i] = br->ReadByte();

            br->Close();
            break;
        }
        default:
        {
            br->Close();
            throw gcnew FormatException("Wrong file format!");
            break;
        }
    }

    return cBytes;
}
String^ FManager::FileManager::getFileNameFromPath(void)
{
    return Path::GetFileName(fileName);
}
void FManager::FileManager::writeIntupFile(array<Byte>^ bytes)
{
    if (!fileName)
        return;

    BinaryWriter^ bw; 

    if (File::Exists(fileName))
    {
        int index = 1;
        String^ newName = fileName + ".bak" + index;

        while (File::Exists(newName) && index != 5)
        {// up to 5 backups
            index++;
            newName = fileName + ".bak" + index;
        }

        File::Copy(fileName, newName, true);

        File::Delete(fileName);
    }
    
    bw = gcnew BinaryWriter(gcnew FileStream(fileName, FileMode::Create, FileAccess::Write));

    switch (this->getFileExtensionCode(fileName))
    {
    case CT_SIGNATURE:
    {
        this->writeCT(bw, bytes);
        break;
    }
    case PAL_SIGNATURE:
    {
        if (paletteCount > 1 || paletteLengths[0] > 256)
        {
            bw->Close();
            throw gcnew FormatException("Incorrect data array!");
        }
        this->writeRIFF(bw, bytes);
        break;
    }
    case ACT_SIGNATURE:
    {
        if (paletteCount > 1 || paletteLengths[0] > 256)
        {
            bw->Close();
            throw gcnew FormatException("Incorrect data array!");
        }
        this->writeACT(bw, bytes);
        break;
    }
    default:
        bw->Close();
        throw gcnew FormatException("Unknonw file format!");
    }

    bw->Close();
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
