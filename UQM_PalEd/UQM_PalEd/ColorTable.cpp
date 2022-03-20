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


#include "ColorTable.h"

using namespace CTable;

/* Segment */
CTable::Segment::Segment(void)
{// constructor
    length = 1;
}

CTable::Segment::~Segment(void)
{// destructor
    this->!Segment();
}

int CTable::Segment::getSegLength(void)
{
    return length;
}

void CTable::Segment::setSegLength(int l)
{
    length = l;
}

void CTable::Segment::fillTable(array<Byte>^ b)
{// build colors from byte array that has been read from file
    if (length != (b->Length / 3))
        throw gcnew System::Exception("Length of current segment is not matched to amount of presented bytes!");

    array<Byte>^ clr = gcnew array<Byte>(BYTES_PER_COLOR);

    table = gcnew array<Color>(length);

    for (int i = 0; i < table->Length; i++)
    {
        for (int j = 0; j < BYTES_PER_COLOR; j++)
        {
            clr[j] = b[i * BYTES_PER_COLOR + j];
        }

        table[i] = Color::FromArgb(clr[RED], clr[GREEN], clr[BLUE]);
    }
}

array<Color>^ CTable::Segment::returnTable(void)
{
    return table;
}

CTable::Segment::!Segment(void)
{// finalizer
    length = 0;
    if (table)
        Array::Clear(table, 0, table->Length);

    delete table;
}

/* Color table */
ColorTable::ColorTable(void)
{// constructor
    numSegs = 1;
    numColors = MAX_COLORS_PER_TABLE;
}

CTable::ColorTable::~ColorTable(void)
{// destructor
    this->!ColorTable();
}

int CTable::ColorTable::getNumSegs(void)
{
    return numSegs;
}

int CTable::ColorTable::getNumColors(void)
{
    return numColors;
}

int CTable::ColorTable::getSegLength(int index)
{
    return seg[index]->getSegLength();
}

void CTable::ColorTable::setNumSegs(int num)
{// set number of segments and declare them
    numSegs = num;
    seg = gcnew array<Segment^>(numSegs);
    for (int i = 0; i < numSegs; i++)
        seg[i] = gcnew Segment();
}

void CTable::ColorTable::setNumColors(int num)
{
    numColors = num;
}

void CTable::ColorTable::setSegLength(int index, int l)
{
    seg[index]->setSegLength(l);
}

void CTable::ColorTable::setSeg(int index, array<Byte>^ b)
{
    seg[index]->fillTable(b);
}

array<Color>^ CTable::ColorTable::returnSeg(int index)
{
    if (index < numSegs)
        return seg[index]->returnTable();
    else
        throw gcnew System::Exception("Incorrect seg index!");
}

CTable::ColorTable::!ColorTable(void)
{// finalizer
    numSegs = 0;
    numColors = 0;

    if (seg)
        Array::Clear(seg, 0, seg->Length);

    delete seg;
}
