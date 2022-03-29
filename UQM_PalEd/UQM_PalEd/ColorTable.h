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


// color table header
#include "Palette.h"

using namespace System;
using namespace System::Drawing;
using namespace CPalette;

#pragma once
namespace CTable 
{
	ref class ColorTable
	{
	private:
		int paletteCount;				// number of palettes in current table;
		array<int>^ paletteLengths;		// array of lengths of every palette
		array<Palette^>^ palettes;		// array of palettes
	public:
		ColorTable(void);
		ColorTable(int paletteCount, array<int>^ paletteLengths);
		ColorTable(int paletteCount, array<int>^ paletteLengths, Color c);
		~ColorTable(void);
	public:
		array<Byte>^ getsubArray(unsigned int start_index, unsigned int end_index, array<Byte>^ bytes);
		array<Color>^ bytesToColors(array<Byte>^ bytes, int format);
		array<Byte>^ colorsToBytes(array<Color>^ colors, int format);
		void distrubutePalettes(array<Byte>^ bytes, int format);
		array<Color>^ getColorPalette(int p_index, int s_index);
		array<Color>^ getColorPalette(int p_index, int s_index, bool isPlanet);
		int getPaletteCount(void);
		int getSegCount(int p_index);
		bool getPlanetCond(int p_index);
		int getPaletteColorCount(int p_index);
		int getSegmentColorCount(int p_index, int s_index);
		array<Color>^ setPaletteSegment(int p_index, int s_index, array<Color>^ c);
	protected:
		!ColorTable(void);
	};
}