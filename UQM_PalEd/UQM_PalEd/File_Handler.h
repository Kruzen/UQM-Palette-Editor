// Ur-Quan Masters Palette Editor v0.0.5

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


 // .ct file handler header
#include <fstream>
#include "ColorTable.h"

#pragma once

#define MAX_TABLES 16
#define MAX_SEGMENTS 408 /*uqm.ct length*/

// Bytes offsets
#define ENCRYPTION_LENGTH 4
#define WHITE_SPOT_LENGTH ENCRYPTION_LENGTH + 2
#define NUM_OF_TABLES WHITE_SPOT_LENGTH + 2
#define UNUSED NUM_OF_TABLES + 4
#define LENGTH_OF_TECH_BYTES UNUSED
#define NUM_BYTES_PER_TABLE_LENGTH 4

using namespace CTable;

namespace Handler
{
	ref class File_Handler
	{
	private:
		String^ fileName;
		String^ content;// for debug
		int tableCount;
		array<ColorTable^>^ table;
		array<int>^ tableLength;
		void reInitValues(String^ fileName, int tableCount, array<int>^ tableLength);
	public:
		File_Handler(void);
		~File_Handler();
		void checkFileFormat(String^ fname);
		void extractContent(void);
		array<Color>^ getTable(int t_index, int s_index);
		array<Color>^ getTable(void);
		int getNumSegs(int t_index);
		int getNumColors(int t_index);
		void setFileName(String^ name);
		String^ getFileName(void);
		int getNumTables(void);
		int getNumSegColors(int t_index, int s_index);
	protected:
		!File_Handler();
	};

	ref class CTException : Exception
	{
	private:
		String^ message;
		bool warning;
	public:
		CTException(void);
		CTException(String^ message, bool warning);
		bool IsWarning(void);
		String^ ToString(void) override;
	};
}
