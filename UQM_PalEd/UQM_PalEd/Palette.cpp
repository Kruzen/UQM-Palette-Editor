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

// palettes
#include "Palette.h"
#include "constdef.h"

using namespace CPalette;
using namespace System;

												/* Segment */
/*
 *
 *
 *	Public methods
 *
 */
void CPalette::Segment::tableToPTable(void)
{// forming in-game view for planets
	p_colors = gcnew array<Color>(length);
	array<Byte>^ clr = gcnew array<Byte>(BYTES_PER_COLOR);

	for (int i = 0; i < length; i++)
	{
		clr[RED] = colors[i].R >> 1;
		clr[GREEN] = colors[i].G >> 1;
		clr[BLUE] = colors[i].B >> 1;

		p_colors[i] = Color::FromArgb(CC5TO8(clr[RED]), CC5TO8(clr[GREEN]), CC5TO8(clr[BLUE]));
	}
}

CPalette::Segment::Segment(void)
{// default constructor
	length = 1;
	colors = gcnew array<Color>(1);
	colors[0] = Color::FromArgb(0, 0, 0);
	//p_colors should be null if not declared
}

CPalette::Segment::Segment(unsigned int length, array<Color>^ colors, bool isPlanet)
{// constructor
	this->length = length;
	this->colors = gcnew array<Color>(this->length);
	this->colors = colors;
	if (isPlanet)
		this->tableToPTable();
}

CPalette::Segment::Segment(unsigned int length, bool isPlanet)
{
	this->length = length;
	this->colors = gcnew array<Color>(this->length);

	for (int i = 0; i < this->length; i++)
		this->colors[i] = Color::FromArgb(127 * (i % 3), 42 * (i % 3), 27 * (i % 3));

	if (isPlanet)
		this->tableToPTable();
}

CPalette::Segment::~Segment(void)
{// destructor
	this->!Segment();
}
/*
 *
 *
 *	"get" methods
 *
 */
int CPalette::Segment::getSegLength(void)
{
	return length;
}

array<Color>^ CPalette::Segment::returnArray(void)
{
	return colors;
}

array<Color>^ CPalette::Segment::returnPArray(void)
{
	if (p_colors)
		return p_colors;
	else
		return colors;
}
/*
 *
 *
 *	"set" methods
 *
 */
void CPalette::Segment::setSegLength(unsigned int l)
{
	length = l;
}

void CPalette::Segment::fillArray(array<Color>^ c)
{
	if (colors)
	{
		Array::Clear(colors, 0, colors->Length);
		delete this->colors;
	}
	length = MIN(c->Length, MAX_COLORS_PER_TABLE);		// new array - set new length to avoid de-sync
	colors = gcnew array<Color>(length);
	for (int i = 0; i < length; i++)
		colors[i] = c[i];
}
/*
 *
 *
 *	Finalizer
 *
 */
CPalette::Segment::!Segment(void)
{
	length = 0;
	if (colors)
	{
		Array::Clear(colors, 0, colors->Length);
		delete colors;
	}
	if (p_colors)
	{
		Array::Clear(p_colors, 0, p_colors->Length);
		delete p_colors;
	}
}


												/* Palette */
/*
 *
 *
 *	Public methods
 *
 */
CPalette::Palette::Palette(void)
{// default constructor
	numSegs = 1;
	numColors = MAX_COLORS_PER_TABLE;
	isPlanet = false;
	seg = gcnew array<Segment^>(1);
	seg[0] = gcnew Segment();
}

CPalette::Palette::Palette(unsigned int numSegs, unsigned int numColors, bool isPlanet)
{// primary constructor (used after file opening)
	this->numSegs = numSegs;
	this->numColors = numColors;
	this->isPlanet = isPlanet;
	this->seg = gcnew array<Segment^>(this->numSegs);
	for (int i = 0; i < this->numSegs; i++)
		this->seg[i] = gcnew Segment();
}

CPalette::Palette::Palette(unsigned int numSegs, unsigned int numColors, bool isPlanet, bool c)
{
	this->numSegs = numSegs;
	this->numColors = numColors;
	this->isPlanet = isPlanet;
	seg = gcnew array<Segment^>(this->numSegs);

	unsigned int remainColors = this->numColors;
	for (int i = 0; i < this->numSegs; i++)
	{
		seg[i] = gcnew Segment(MIN(remainColors, MAX_COLORS_PER_TABLE), this->isPlanet);
		remainColors -= MAX_COLORS_PER_TABLE;
	}
}

CPalette::Palette::~Palette(void)
{// destructor
	this->!Palette();
}

int CPalette::Palette::getSegLength(int index)
{
	return seg[index]->getSegLength();
}

void CPalette::Palette::setSegLength(int index, int l)
{
	seg[index]->setSegLength(l);
}
/*
 *
 *
 *	"get" methods
 *
 */
int CPalette::Palette::getNumSegs(void)
{
	return numSegs;
}

int CPalette::Palette::getNumColors(void)
{
	return numColors;
}

bool CPalette::Palette::getPlanetCond(void)
{
	return isPlanet;
}

array<Color>^ CPalette::Palette::returnSeg(int index)
{
	if (index >= seg->Length)
		return seg[seg->Length - 1]->returnArray();

	return seg[index]->returnArray();
}

array<Color>^ CPalette::Palette::returnSeg(int index, bool isPlanet)
{
	if (isPlanet)
		return seg[index]->returnPArray();
	else
		return seg[index]->returnArray();
}
/*
 *
 *
 *	"set" methods
 *
 */
void CPalette::Palette::setNumSegs(int numSegs)
{
	this->numSegs = numSegs;
}

void CPalette::Palette::setNumColors(int numColors)
{
	this->numColors = numColors;
}

void CPalette::Palette::setPlanetCond(bool isPlanet)
{
	this->isPlanet = isPlanet;
}

void CPalette::Palette::setSeg(int index, array<Color>^ c)
{
	seg[index]->fillArray(c);
	if (isPlanet)					// if out palette is a planet - also generate filtered array
		seg[index]->tableToPTable();
}
/*
 *
 *
 *	Finalizer
 *
 */
CPalette::Palette::!Palette(void)
{
	if (seg)
	{
		for (int i = 0; i < numSegs; i++)
		{
			seg[i]->~Segment();
			delete seg[i];
		}
		delete seg;
	}
	numSegs = 0;
	numColors = 0;
	isPlanet = false;
}
