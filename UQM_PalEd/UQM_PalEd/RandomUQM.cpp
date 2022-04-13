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
 *
 * FUNC: getUQMRandomValue()
 *
 * DESC: random number generator
 *
 * NOTES: based on UQM code
 *
 * HISTORY: Created By Robert leyland
 *
 *****************************************************************************/

#include "RandomUQM.h"
#include <cstdlib>
#include <time.h>

RandomUQM::RandomUQM(void)
{
	srand(time(NULL));
	this->seed = std::rand();
}

RandomUQM::RandomUQM(int value)
{
	this->seed = value;
}

RandomUQM::~RandomUQM(void)
{
	seed = 0;
}

int RandomUQM::getUQMRandomValue(void)
{
	if ((seed = A * (seed % Q) - D * (seed / Q)) > M)
		return (seed -= M);
	else if (seed)
		return (seed);
	else
		return (seed = 1L);
}
