// color table object UNUSED!
#include <fstream>

#pragma once

#define MAX_CLUTS_PER_TABLE 256
#define BYTES_PER_COLOR 3

using namespace System;
using namespace System::Drawing;
using namespace System::IO;

namespace CTable
{
	ref class ColorTable
	{
	private:
		int numCluts;
		int index;
		array<Color>^ table;
	public:		
		ColorTable(void);
		ColorTable(int index);
		void setNumCluts(int num);
		void fillTable(BinaryReader^ br);
		array<Color>^ returnTable(void);
		String^ debug(void);
	};
}

