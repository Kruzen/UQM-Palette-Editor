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

// file manager header for .ct, .pal, .act(TODO)
#include <fstream>

using namespace System;
using namespace System::IO;

#pragma once
namespace FManager
{
	ref class FileManager
	{
	private:
		String^ fileName;				// name of current file
		int fileType;					// file ID (see enum in constdef.h)
		int paletteCount;				// number of palettes in opened file;
		array<int>^ paletteLengths;		// array of lengths of every palette
	private:
		void reInitValues(String^ fName, int p_count, array<int>^ p_lengths);
		unsigned int getFileExtensionCode(String^ fName);
		array<Byte>^ decryptOldCT(BinaryReader^ br);
		void checkCT(String^ fName);
		void checkRIFF(String^ fName);
		void checkACT(String^ fName);
		void checkXLT(String^ fName);
		void writeCT(BinaryWriter^ bw, array<Byte>^ bytes);
		void writeRIFF(BinaryWriter^ bw, array<Byte>^ bytes);
		void writeACT(BinaryWriter^ bw, array<Byte>^ bytes);
	public:
		FileManager(void);
		FileManager(String^ filename, int paletteCount, array<int>^ paletteLengths);
		~FileManager(void);
		void checkFileFormat(String^ fname);
		array<Byte>^ extractColorBytes(void);
		String^ getFileNameFromPath(void);
		void writeIntupFile(array<Byte>^ bytes);
	public:
		String^ getFileName(void);
		int getFileType(void);
		int getPaletteCount(void);
		array<int>^ getPaletteLengths(void);
	public:
		void setFileName(String^ fileName);
		void setFileType(int type);
		void setPaletteCount(int paletteCount);
		void setPaletteLengths(array<int>^ paletteLengths);
	protected:
		!FileManager(void);
	};
}

