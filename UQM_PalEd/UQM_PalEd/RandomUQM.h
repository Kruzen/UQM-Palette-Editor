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

 /****************************************************************************
* FILE: random.c (from UQM source code)
* DESC: a library of random number generators for general purpose use.
*
* References:
* "Random Number Generators: Good ones are hard to find" S.K.Park & K.W.Miller
* Communications of the ACM, Vol31 Number 10, October 1988, Pp 1192-1201
*
* HISTORY: Created 1/23/1989
* LAST CHANGED:
*
* Copyright (c) 1989, Robert Leyland and Fred Ford
****************************************************************************/

/* ----------------------------DEFINES------------------------------------ */
/* constants for licongruential random number generator from CACM article
   referenced above */
#define A 16807 /* a relatively prime number -- also M div Q */
#define M 2147483647L /* 0xFFFFFFFF / 2 */
#define Q 127773L /* M div A */
#define R 2836 /* M mod A */

#pragma once
class RandomUQM
{
private:
	int seed;
public:
	RandomUQM(void);
	RandomUQM(int value);
	~RandomUQM(void);

	int getUQMRandomValue(void);
};

