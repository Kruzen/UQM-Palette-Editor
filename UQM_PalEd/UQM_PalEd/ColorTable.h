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


 // color table and segmet header
#pragma once

#define MAX_COLORS_PER_TABLE 256
#define BYTES_PER_COLOR 3
#define MAX_BYTES_PER_SEGMENT MAX_COLORS_PER_TABLE*BYTES_PER_COLOR
#define RED 0
#define GREEN 1
#define BLUE 2
#define MAX(a,b) (a > b ? a : b)
#define MIN(a,b) (a < b ? a : b)
#define CC5TO8(c) (((c) << 3) | ((c) >> 2))// from UQM source code

using namespace System;
using namespace System::Drawing;
using namespace System::IO;

namespace CTable
{/*
  * Segment is an atomic part - an array of colors with length of 256 or less
  * Color array can be created from array of bytes with length of multiples of 3
  * Segment length is a number of its colors, not a length of a byte array that created it
  * Segment is what being displayed on a main form
  */
	ref class Segment
	{
	private:
		int length;
		array<Color>^ table;
		array<Color>^ p_table;// in-game colors for planets
	public:
		Segment(void);
		~Segment(void);
		int getSegLength(void);
		void setSegLength(int l);
		void fillTable(array<Byte>^ b);
		array<Color>^ returnTable(void);
		void tableToPTable(void);
		array<Color>^ returnPTable(void);
	protected:
		!Segment(void);
	};
	/*
	 * Color table is a structure that is contained within .ct file
	 * It is a string of bytes in length of multiples of 3 plus 2 bytes for indexes
	 * While most of the time table length is 770 bytes (2 bytes for indexes plus 3 bytes per color as RGB value)
	 * technically it could be any length if it does not contradict described above rule
	 * In that case table is split into several segments
	 * However most of default UQM tables contain 1 segment with 256 colors
	 */
	ref class ColorTable
	{
	private:
		int numSegs;
		int numColors;
		array<Segment^>^ seg;
	public:
		ColorTable(void);
		~ColorTable(void);
		int getNumSegs(void);
		int getNumColors(void);
		int getSegLength(int index);
		void setNumSegs(int num);
		void setNumColors(int num);
		void setSegLength(int index, int l);
		void setSeg(int index, array<Byte>^ b);
		array<Color>^ returnSeg(int index);
	protected:
		!ColorTable(void);
	};
}
