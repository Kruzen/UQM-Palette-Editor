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


// Color table is a structure that contains palettes from opened file in arrays of colors
// Also can transform these colors to array of bytes for file writer and vice versa

#include "ColorTable.h"
#include "constdef.h"

CTable::ColorTable::ColorTable(void)
{// default constructor
    paletteCount = 1;
    paletteLengths = gcnew array<int>(1);
    paletteLengths[0] = 1;
}

CTable::ColorTable::ColorTable(int paletteCount, array<int>^ paletteLengths)
{// constructor - used in file opening
    this->paletteCount = paletteCount;
    this->paletteLengths = gcnew array<int>(paletteCount);
    this->paletteLengths = paletteLengths;
    this->palettes = gcnew array<Palette^>(this->paletteCount);
}

CTable::ColorTable::ColorTable(int paletteCount, array<int>^ paletteLengths, Color c)
{// constructor - used in creating New table
    this->paletteCount = paletteCount;
    this->paletteLengths = gcnew array<int>(this->paletteCount);
    this->paletteLengths = paletteLengths;
    this->palettes = gcnew array<Palette^>(this->paletteCount);

    bool isPlanet = false;
    
    if (this->paletteCount == 3)// condition for a planet.ct
        isPlanet = (this->paletteLengths[0] == 386 && this->paletteLengths[1] == 386 && this->paletteLengths[2] == 386);

    for (int i = 0; i < this->paletteCount; i++)// for every palette determine the amount of segments and then fill them
    {// fill structures from selected file
        int segs;

        segs = (this->paletteLengths[i] - 2) / (MAX_BYTES_PER_SEGMENT);

        if (segs < 1)
            segs = 1;// one segment of less than 256 colors (i.e. planet table)
        else
            segs += (((this->paletteLengths[i] - 2) % (MAX_BYTES_PER_SEGMENT)) != 0);// +1 segment if it's <256 colors in length

        palettes[i] = gcnew Palette(segs, (this->paletteLengths[i] - 2) / BYTES_PER_COLOR, isPlanet, c);
    }
}

CTable::ColorTable::~ColorTable(void)
{// destructor
    this->!ColorTable();
}

array<Byte>^ CTable::ColorTable::getsubArray(unsigned int start_index, unsigned int length, array<Byte>^ bytes)
{// getting a byte subarray of "length" starting from "start_index" of parent array
 // dividing whole palette into segments
    if (start_index + length > bytes->Length)
        throw gcnew System::Exception("Wrong subarray length!");

    array<Byte>^ subArray = gcnew array<Byte>(length);

    for (int i = 0; i < length; i++)
        subArray[i] = bytes[start_index + i];

    return subArray;
}

array<Color>^ CTable::ColorTable::bytesToColors(array<Byte>^ bytes, int format)
{// transform byte array into color array
    array<Color>^ colors;
    int bytesInColor;

    switch (format)
    {
        case RIFF_FILE:
        {
            bytesInColor = BYTES_PER_COLOR_RIFF;
            break;
        }
        case CT_FILE:
        default:
        {
            bytesInColor = BYTES_PER_COLOR;
            break;
        }
    }
    array<Byte>^ clr = gcnew array<Byte>(bytesInColor);

    colors = gcnew array<Color>(MIN(bytes->Length / bytesInColor, MAX_COLORS_PER_TABLE));

    for (int i = 0; i < colors->Length; i++)
    {
        for (int j = 0; j < bytesInColor; j++)
        {
            clr[j] = bytes[i * bytesInColor + j];
        }

        colors[i] = Color::FromArgb(clr[RED], clr[GREEN], clr[BLUE]);
    }

    return colors;
}

array<Byte>^ CTable::ColorTable::colorsToBytes(array<Color>^ colors, int format)
{// transform color array into byte array
    array<Byte>^ bytes;

    switch (format)
    {
        case RIFF_FILE:
        {
            bytes = gcnew array<Byte>(colors->Length * BYTES_PER_COLOR_RIFF);

            for (int i = 0; i < colors->Length; i++)
            {
                bytes[i * BYTES_PER_COLOR_RIFF + RED] = colors[i].R;
                bytes[i * BYTES_PER_COLOR_RIFF + GREEN] = colors[i].G;
                bytes[i * BYTES_PER_COLOR_RIFF + BLUE] = colors[i].B;
                bytes[i * BYTES_PER_COLOR_RIFF + FLAG] = 0x00;
            }
            break;
        }
        case CT_FILE:
        default:
        {
            bytes = gcnew array<Byte>(colors->Length * BYTES_PER_COLOR);

            for (int i = 0; i < colors->Length; i++)
            {
                bytes[i * BYTES_PER_COLOR + RED] = colors[i].R;
                bytes[i * BYTES_PER_COLOR + GREEN] = colors[i].G;
                bytes[i * BYTES_PER_COLOR + BLUE] = colors[i].B;
            }
            break;
        }
    }

    return bytes;
}

void CTable::ColorTable::distrubutePalettes(array<Byte>^ bytes, int format)
{// fill all color table structures with provided colors from byte array
    int bytesInSegment;
    int bytesInColor;
    int byteOffset;

    switch (format)// set values depending on the file format (determined by signature in File manager)
    {
        case ACT_FILE:
        {
            bytesInSegment = MAX_BYTES_PER_SEGMENT;
            bytesInColor = BYTES_PER_COLOR;
            byteOffset = 0;
            break;
        }
        case RIFF_FILE:
        {
            bytesInSegment = MAX_BYTES_PER_SEGMENT_RIFF;
            bytesInColor = BYTES_PER_COLOR_RIFF;
            byteOffset = 0;
            break;
        }
        case CT_FILE:
        default:
        {
            bytesInSegment = MAX_BYTES_PER_SEGMENT;
            bytesInColor = BYTES_PER_COLOR;
            byteOffset = 2;
            break;
        }
    }

    int currByte_index = 0;
    int endByte_index;
    int numBytes;
    bool isPlanet = false;

    if (paletteCount == 3)// condition for a planet.ct
        isPlanet = (paletteLengths[0] == 386 && paletteLengths[1] == 386 && paletteLengths[2] == 386);

    for (int i = 0; i < paletteCount; i++)// for every palette determine the amount of segments and then fill them
    {// fill structures from selected file
        int segs;

        segs = (paletteLengths[i] - byteOffset) / bytesInSegment;

        if (segs < 1)
            segs = 1;// one segment of less than 256 colors (i.e. planet table)
        else
            segs += (((paletteLengths[i] - byteOffset) % (bytesInSegment)) != 0);// +1 segment if it's <256 colors in length

        palettes[i] = gcnew Palette(segs, (paletteLengths[i] - byteOffset) / bytesInColor, isPlanet);

        endByte_index = currByte_index + paletteLengths[i];
        currByte_index += byteOffset; // skip indexes and go straight to colors in .ct (0 if otherwise)

        for (int j = 0; j < segs; j++)
        {// Fill segments
            numBytes = MIN(bytesInSegment, endByte_index - currByte_index);
            palettes[i]->setSeg(j, this->bytesToColors(this->getsubArray(currByte_index, numBytes, bytes), format));
            currByte_index += numBytes;
        }
    }
}

array<Color>^ CTable::ColorTable::getColorPalette(int p_index, int s_index)
{
    return palettes[p_index]->returnSeg(s_index);
}

array<Color>^ CTable::ColorTable::getColorPalette(int p_index, int s_index, bool isPlanet)
{
    return palettes[p_index]->returnSeg(s_index, isPlanet);
}

int CTable::ColorTable::getPaletteCount(void)
{
    return paletteCount;
}

int CTable::ColorTable::getSegCount(int p_index)
{
    return palettes[p_index]->getNumSegs();
}

bool CTable::ColorTable::getPlanetCond(int p_index)
{
    return palettes[p_index]->getPlanetCond();
}

int CTable::ColorTable::getPaletteColorCount(int p_index)
{
    return palettes[p_index]->getNumColors();
}

int CTable::ColorTable::getSegmentColorCount(int p_index, int s_index)
{
    return palettes[p_index]->getSegLength(s_index);
}

array<Color>^ CTable::ColorTable::setPaletteSegment(int p_index, int s_index, array<Color>^ c)
{
    paletteLengths[p_index] -= palettes[p_index]->getSegLength(s_index) * BYTES_PER_COLOR;
    palettes[p_index]->setNumColors(palettes[p_index]->getNumColors() - palettes[p_index]->getSegLength(s_index));
    paletteLengths[p_index] += MIN(c->Length, MAX_COLORS_PER_TABLE) * BYTES_PER_COLOR;

    if (paletteCount == 3)
    {
        bool isPlanet = (paletteLengths[0] == 386 && paletteLengths[1] == 386 && paletteLengths[2] == 386);;
        palettes[0]->setPlanetCond(isPlanet);
        palettes[1]->setPlanetCond(isPlanet);
        palettes[2]->setPlanetCond(isPlanet);
    }
    palettes[p_index]->setSeg(s_index, c);
    palettes[p_index]->setNumColors(palettes[p_index]->getNumColors() + palettes[p_index]->getSegLength(s_index));

    return c;
}

CTable::ColorTable::!ColorTable(void)
{
    paletteCount = 0;

    if (paletteLengths)
    {
        Array::Clear(paletteLengths, 0, paletteLengths->Length);
        delete paletteLengths;
    }

    if (palettes)
    {
        for (int i = 0; i < palettes->Length; i++)
            palettes[i]->~Palette();

        delete palettes;
    }
}
