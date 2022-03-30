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

 // palette and segmet header
using namespace System::Drawing;

#pragma once
namespace CPalette
{/*
  * Segment is an atomic part - an array of colors with length of 256 or less
  * Color array can be created from array of bytes with length of multiples of 3
  * Segment length is a number of its colors, not a length of a byte array that created it
  * Segment is what being displayed on a main form
  */
	ref class Segment
	{
	private:
		unsigned int length;		// segment length
		array<Color>^ colors;		// segment true colors
		array<Color>^ p_colors;		// in-game colors for planets
	public:
		void tableToPTable(void);
	public:
		Segment(void);
		Segment(unsigned int length, array<Color>^ colors, bool isPlanet);
		Segment(unsigned int length, bool isPlanet);
		~Segment(void);
	public:
		int getSegLength(void);
		array<Color>^ returnArray(void);
		array<Color>^ returnPArray(void);
	public:
		void setSegLength(unsigned int l);
		void fillArray(array<Color>^ c);
		Color getColor(int c_index);
	protected:
		!Segment(void);
	};
	/*
	 * Palette is a structure that is contained within .ct file
	 * It is a string of bytes in length of multiples of 3 plus 2 bytes for indexes
	 * While most of the time table length is 770 bytes (2 bytes for indexes plus 3 bytes per color as RGB value)
	 * technically it could be any length if it does not contradict described above rule
	 * In that case table is split into several segments
	 * However most of default UQM tables contain 1 segment with 256 colors
	 */
	ref class Palette
	{
	private:
		unsigned int numSegs;		// total number of segments in a palette
		unsigned int numColors;		// total number of colors in a palette
		bool isPlanet;				// true - only when number of palettes = 3 and each is 386 bytes in length
		array<Segment^>^ seg;		// Segments per palette
	public:
		Palette(void);
		Palette(unsigned int numSegs, unsigned int numColors, bool isPlanet);
		Palette(unsigned int numSegs, unsigned int numColors, bool isPlanet, bool c);
		~Palette(void);
	public:
		int getSegLength(int index);
		void setSegLength(int index, int l);
	public:
		int getNumSegs(void);
		int getNumColors(void);		
		bool getPlanetCond(void);
		array<Color>^ returnSeg(int index);
		array<Color>^ returnSeg(int index, bool isPlanet);
		Color getColorFromSegment(int s_index, int c_index);
	public:
		void setNumSegs(int numSegs);
		void setNumColors(int numColors);
		void setPlanetCond(bool isPlanet);
		void setSeg(int index, array<Color>^ c);		
	protected:
		!Palette(void);
	};
}

