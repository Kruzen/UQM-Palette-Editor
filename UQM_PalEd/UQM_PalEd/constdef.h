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

#pragma once

#define CT_TECH_BYTE_LENGTH 12			// non-color bytes in .ct
#define RIFF_TECH_BYTE_LENGTH 24		// non-color bytes in .pal
#define NUM_BYTES_PER_TABLE_LENGTH 4	// bytes of table length in .ct
#define CT_SIGNATURE 0xFFFFFFFF			// First 4 bytes of any .ct
#define RIFF_SIGNATURE 0x52494646		// RIFF
#define PAL_SIGNATURE 0x50414C20		// PAL
#define TEST 0x0204

static enum
{
	NON,
	CT_FILE,
	RIFF_FILE,
	LAST_FILE_TYPE = RIFF_FILE
};
