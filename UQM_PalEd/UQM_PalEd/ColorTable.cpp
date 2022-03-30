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
// Plus several misc maintenance funcs

#include "ColorTable.h"
#include "constdef.h"

/*
 *
 *
 *	Public methods
 *
 */
CTable::ColorTable::ColorTable(void)
{// default constructor
    paletteCount = 1;
}

CTable::ColorTable::ColorTable(int paletteCount)
{// constructor - used in file opening
    this->paletteCount = paletteCount;
    this->palettes = gcnew array<Palette^>(this->paletteCount);
}

CTable::ColorTable::ColorTable(int paletteCount, array<int>^ paletteLengths)
{// constructor - used in creating New table
    this->paletteCount = paletteCount;
    this->palettes = gcnew array<Palette^>(this->paletteCount);

    bool isPlanet = false;
    
    if (this->paletteCount == 3)// condition for a planet.ct
        isPlanet = (paletteLengths[0] == 128 && paletteLengths[1] == 128 && paletteLengths[2] == 128);

    for (int i = 0; i < this->paletteCount; i++)// for every palette determine the amount of segments and then fill them
    {// fill structures from selected file
        int segs;

        segs = paletteLengths[i] / MAX_COLORS_PER_TABLE;

        if (segs < 1)
            segs = 1;// one segment of less than 256 colors (i.e. planet table)
        else
            segs += ((paletteLengths[i] % MAX_COLORS_PER_TABLE) != 0);// +1 segment if it's <256 colors in length

        palettes[i] = gcnew Palette(segs, paletteLengths[i], isPlanet, true);
    }
}

CTable::ColorTable::~ColorTable(void)
{// destructor
    this->!ColorTable();
}

array<Color>^ CTable::ColorTable::mergeColorArrays(array<Color>^ a, array<Color>^ b)
{// returns new merged table

    if (!b)
    {
        b = a;
        return b;
    }
    else
    {
        array<Color>^ res = gcnew array<Color>(a->Length + b->Length);
        int k = 0;

        for (int j = 0; j < b->Length; j++, k++)
            res[k] = b[j];

        for (int i = 0; i < a->Length; i++, k++)
            res[k] = a[i];

        return res;
    }

    return b;
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

array<Color>^ CTable::ColorTable::getsubColorArray(unsigned int start_index, unsigned int length, array<Color>^ colors)
{// same, but with colors
    if (start_index + length > colors->Length)
        throw gcnew System::Exception("Wrong subarray length!");

    array<Color>^ subArray = gcnew array<Color>(length);

    for (int i = 0; i < length; i++)
        subArray[i] = colors[start_index + i];

    return subArray;
}

array<Color>^ CTable::ColorTable::bytesToColors(array<Byte>^ bytes)
{// transform byte array into color array
    array<Color>^ colors;

    array<Byte>^ clr = gcnew array<Byte>(BYTES_PER_COLOR);

    colors = gcnew array<Color>(MIN(bytes->Length / BYTES_PER_COLOR, MAX_COLORS_PER_TABLE));

    for (int i = 0; i < colors->Length; i++)
    {
        for (int j = 0; j < BYTES_PER_COLOR; j++)
        {
            clr[j] = bytes[i * BYTES_PER_COLOR + j];
        }

        colors[i] = Color::FromArgb(clr[RED], clr[GREEN], clr[BLUE]);
    }

    return colors;
}

array<Byte>^ CTable::ColorTable::colorsToBytes(array<Color>^ colors)
{// transform color array into byte array
    array<Byte>^ bytes;

    for (int i = 0; i < colors->Length; i++)
    {
        bytes[i * BYTES_PER_COLOR + RED] = colors[i].R;
        bytes[i * BYTES_PER_COLOR + GREEN] = colors[i].G;
        bytes[i * BYTES_PER_COLOR + BLUE] = colors[i].B;
    }

    return bytes;
}

void CTable::ColorTable::distrubutePalettes(array<Byte>^ bytes, array<int>^ paletteLengths)
{// fill all color table structures with provided colors from byte array
    
    int currByte_index = 0;
    int endByte_index;
    int numBytes;
    bool isPlanet = false;

    if (paletteCount == 3)// condition for a planet.ct
        isPlanet = (paletteLengths[0] == 128 && paletteLengths[1] == 128 && paletteLengths[2] == 128);

    for (int i = 0; i < paletteCount; i++)// for every palette determine the amount of segments and then fill them
    {// fill structures from selected file
        int segs;

        segs = paletteLengths[i] / MAX_COLORS_PER_TABLE;

        if (segs < 1)
            segs = 1;// one segment of less than 256 colors (i.e. planet table)
        else
            segs += ((paletteLengths[i] % MAX_COLORS_PER_TABLE) != 0);// +1 segment if it's <256 colors in length

        palettes[i] = gcnew Palette(segs, paletteLengths[i], isPlanet);

        endByte_index = currByte_index + (paletteLengths[i] * BYTES_PER_COLOR);

        for (int j = 0; j < segs; j++)
        {// Fill segments
            numBytes = MIN(MAX_BYTES_PER_SEGMENT, endByte_index - currByte_index);
            palettes[i]->setSeg(j, this->bytesToColors(this->getsubArray(currByte_index, numBytes, bytes)));
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
    palettes[p_index]->setNumColors(palettes[p_index]->getNumColors() - palettes[p_index]->getSegLength(s_index) + c->Length);

    if (paletteCount == 3)
    {
        bool isPlanet = (palettes[0]->getNumColors() == 128 && palettes[1]->getNumColors() == 128 && palettes[2]->getNumColors() == 128);
        palettes[0]->setPlanetCond(isPlanet);
        palettes[1]->setPlanetCond(isPlanet);
        palettes[2]->setPlanetCond(isPlanet);
    }
    palettes[p_index]->setSeg(s_index, c);    

    this->reshuffleSegmentsInPalette(p_index, s_index);

    return palettes[p_index]->returnSeg(s_index);
}

void CTable::ColorTable::reshuffleSegmentsInPalette(int p_index, int s_index)
{// re-arrange segments in case of color shift in the middle
    int segs = palettes[p_index]->getNumSegs();

    if (segs > 1 && segs != (s_index + 1))
    {// not 1 and not last
        array<Color>^ fullPalette;
        for (int s_index = 0; s_index < segs; s_index++)
            fullPalette = this->mergeColorArrays(palettes[p_index]->returnSeg(s_index), fullPalette);

        {// re-shuffle segments
            int curr_index = 0;
            int numColors;
            bool isPlanet = false;

            if (paletteCount == 3)
            {
                palettes[p_index]->setNumColors(fullPalette->Length);
                isPlanet = (palettes[0]->getNumColors() == 128 && palettes[1]->getNumColors() == 128 && palettes[2]->getNumColors() == 128);
                palettes[0]->setPlanetCond(isPlanet);
                palettes[1]->setPlanetCond(isPlanet);
                palettes[2]->setPlanetCond(isPlanet);
            }

            segs = fullPalette->Length / MAX_COLORS_PER_TABLE;

            if (segs < 1)
                segs = 1;// one segment of less than 256 colors (i.e. planet table)
            else
                segs += ((fullPalette->Length % MAX_COLORS_PER_TABLE) != 0);// +1 segment if it's <256 colors in length

            palettes[p_index] = gcnew Palette(segs, fullPalette->Length, isPlanet);

            for (int j = 0; j < segs; j++)
            {// Fill segments
                numColors = MIN(MAX_COLORS_PER_TABLE, fullPalette->Length - curr_index);
                palettes[p_index]->setSeg(j, this->getsubColorArray(curr_index, numColors, fullPalette));
                curr_index += numColors;
            }
        }
    }
}

/*
 *
 *
 *	Finalizer
 *
 */
CTable::ColorTable::!ColorTable(void)
{
    paletteCount = 0;

    if (palettes)
    {
        for (int i = 0; i < palettes->Length; i++)
        {
            if (palettes[i])
                palettes[i]->~Palette();
        }

        delete palettes;
    }
}
