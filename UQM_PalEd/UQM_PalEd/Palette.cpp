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

#include "Palette.h"

void CPalette::Segment::tableToPTable(void)
{
	throw gcnew System::NotImplementedException();
}

CPalette::Segment::Segment(void)
{
	throw gcnew System::NotImplementedException();
}

CPalette::Segment::~Segment(void)
{
	throw gcnew System::NotImplementedException();
}

int CPalette::Segment::getSegLength(void)
{
	return 0;
}

array<Color>^ CPalette::Segment::returnArray(void)
{
	throw gcnew System::NotImplementedException();
	// TODO: вставьте здесь оператор return
}

array<Color>^ CPalette::Segment::returnPArray(void)
{
	throw gcnew System::NotImplementedException();
	// TODO: вставьте здесь оператор return
}

void CPalette::Segment::setSegLength(unsigned int l)
{
	throw gcnew System::NotImplementedException();
}

void CPalette::Segment::fillArray(array<Color>^ c)
{
	throw gcnew System::NotImplementedException();
}

CPalette::Segment::!Segment(void)
{
	throw gcnew System::NotImplementedException();
}

CPalette::Palette::Palette(void)
{
	throw gcnew System::NotImplementedException();
}

CPalette::Palette::~Palette(void)
{
	throw gcnew System::NotImplementedException();
}

int CPalette::Palette::getSegLength(int index)
{
	return 0;
}

void CPalette::Palette::setSegLength(int index, int l)
{
	throw gcnew System::NotImplementedException();
}

int CPalette::Palette::getNumSegs(void)
{
	return 0;
}

int CPalette::Palette::getNumColors(void)
{
	return 0;
}

bool CPalette::Palette::getPlanetCond(void)
{
	return false;
}

array<Color>^ CPalette::Palette::returnSeg(int index)
{
	throw gcnew System::NotImplementedException();
	// TODO: вставьте здесь оператор return
}

array<Color>^ CPalette::Palette::returnSeg(int index, bool isPlanet)
{
	throw gcnew System::NotImplementedException();
	// TODO: вставьте здесь оператор return
}

void CPalette::Palette::setNumSegs(int num)
{
	throw gcnew System::NotImplementedException();
}

void CPalette::Palette::setNumColors(int num)
{
	throw gcnew System::NotImplementedException();
}

void CPalette::Palette::setPlanetCond(bool isPlanet)
{
	throw gcnew System::NotImplementedException();
}

void CPalette::Palette::setSeg(int index, array<Color>^ c)
{
	throw gcnew System::NotImplementedException();
}

CPalette::Palette::!Palette(void)
{
	throw gcnew System::NotImplementedException();
}
