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

// .ct file manager header
#include <fstream>

#pragma once

using namespace System;
using namespace System::IO;

namespace FManager
{
	ref class FileManager
	{
	private:
		String^ fileName;				// name of current file
		int fileType;					// file ID (see enum in constdef.h)
		int paletteCount;				// number of palettes in opened file;
		array<int>^ paletteLengths;		// array of lengths of ebery palette
		array<Byte>^ cBytes;			// colors represented in bytes (extracted from file)
	private:
		void reInitValues(String^ fName, int p_count, array<int>^ p_lengths);
		void checkCT(BinaryReader^ br, String^ fName);
		void checkRIFF(BinaryReader^ br, String^ fName);
	public:
		FileManager(void);
		FileManager(String^ filename, int fileType, int paletteCount, array<int>^ paletteLengths, array<Byte>^ cBytes);
		~FileManager(void);
		void checkFileFormat(String^ fname);
		void extractColorBytes(void);
	public:
		String^ getFileName(void);
		int getFileType(void);
		int getPaletteCount(void);
		array<int>^ getPaletteLengths(void);
		array<Byte>^ getColorBytes(void);
	public:
		void setFileName(String^ fileName);
		void setFileType(int type);
		void setPaletteCount(int paletteCount);
		void setPaletteLengths(array<int>^ paletteLengths);
		void setColorBytes(array<Byte>^ cBytes);
	protected:
		!FileManager(void);
	};
}

