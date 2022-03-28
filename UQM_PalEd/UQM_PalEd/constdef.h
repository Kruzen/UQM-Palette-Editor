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

// consts
#define CT_TECH_BYTE_LENGTH 12			// non-color bytes in .ct
#define RIFF_TECH_BYTE_LENGTH 24		// non-color bytes in .pal
#define NUM_BYTES_PER_TABLE_LENGTH 4	// bytes of table length in .ct
#define CT 0xFFFFFFFF					// First 4 bytes of any .ct
#define RIFF 0x46464952					// RIFF
#define PAL 0x204C4150					// PAL
#define DATA 0x61746164					// data

#define PAL_SIGNATURE 0x6C61702E
#define ACT_SIGNATURE 0x7463612E
#define CT_SIGNATURE 0x2074632E

#define MAX_COLORS_PER_TABLE 256
#define BYTES_PER_COLOR 3
#define BYTES_PER_COLOR_RIFF 4
#define MAX_BYTES_PER_SEGMENT MAX_COLORS_PER_TABLE*BYTES_PER_COLOR
#define MAX_BYTES_PER_SEGMENT_RIFF MAX_COLORS_PER_TABLE*BYTES_PER_COLOR_RIFF
#define RED 0
#define GREEN 1
#define BLUE 2
#define FLAG 3

// macros
#define MAX(a,b) (a > b ? a : b)
#define MIN(a,b) (a < b ? a : b)
#define CC5TO8(c) (MIN(((c << 3) | (c >> 2)), 0xFF))// based on UQM source code
#define FLIP_INT16(i) (((i & 0xFF00) >> 8) | ((i & 0x00FF) << 8))
#define FLIP_INT32(i) (((i & 0xFF000000) >> 24) | ((i & 0x00FF0000) >> 8) | ((i & 0x0000FF00) << 8) | ((i & 0x000000FF) << 24))

static enum
{
	NON,
	CT_FILE,
	RIFF_FILE,
	ACT_FILE,
	LAST_FILE_TYPE = ACT_FILE
};
