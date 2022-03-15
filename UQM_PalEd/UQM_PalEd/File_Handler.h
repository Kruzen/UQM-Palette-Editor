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
#define MAX_COLORS_PER_TABLE 256

using namespace System;
using namespace System::IO;

namespace Handler
{
	ref class File_Handler
	{
	private:
		String^ fileName;
		String^ content;
		int tableCount;
		int segCount;
		int currIndex;
		array<int>^ tableLength;
		array<Color>^ currTable;
		bool segMode;
		void provokeMessageBox(String^ s, bool err);
		bool checkFileFormat(BinaryReader^ br);
	public:
		File_Handler(void);
		~File_Handler();
		void setFileName(String^ name);
		void extractContent(void);
		array<Color>^ getCurrentTable();
		void setCurrentTable(int index);
		String^ getFileName(void);
		int getNumTables(void);
		int getCurrIndex(void);
	protected:
		!File_Handler();
	};
}
