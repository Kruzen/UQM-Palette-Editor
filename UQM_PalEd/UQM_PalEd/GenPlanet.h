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

#pragma once
#include "RandomUQM.h"
#include "Plandata.h"

typedef struct
{
	short x, y;
	short width, height;

}RECT_UQM;

class GenPlanet
{
private:
	RandomUQM* r;
private:
	void deltaTopography(int num_iterations, char* depthArray, RECT_UQM* pRect, int depth_delta);
	//array<char>^ deltaTopography(int num_iterations, array<char>^ depthArray, RECT_UQM* pRect, int depth_delta);
	void ditherMap(char* depthArray, short width, short height);
	//char* ditherMap(char depthArray[], short width, short height);
	void validateMap(char* depthArray, short width, short height);
	void makeCrater(RECT_UQM* pRect, char* depthArray, short rim_delta, short crater_delta, bool SetDepth, unsigned short width);
	void makeStorms(short storm_count, char* depthArray, short width, short height);
	void makeGasGiant(short num_bands, char* depthArray, RECT_UQM* pRect, short depth_delta);
public:
	GenPlanet(void);
	GenPlanet(int r);
	~GenPlanet(void);
public:
	void generatePlanetSurface(char* depthArray, TopoFrame* desc);
};


