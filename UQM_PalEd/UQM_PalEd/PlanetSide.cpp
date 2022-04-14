// Ur-Quan Masters Palette Editor

/*
 *	This program is created as a tool to view/modify/create
 *	Ur-Quan Masters .ct (color table) files. No source code from
 *	the original game was used besides a couple of macros to form in-game planet
 *  colors. Program algorithms are based on dev doc	file
 *  (see ..\doc\devel\strtab file in Ur-Quan Masters repository).
 *
 *	"Ur-Quan Masters" was originally created by Fred Ford and Paul Reiche III.
 *	Copyright Paul Reiche, Fred Ford. 1992-2002
 *	All trademarks belong to their respective owners.
 *
 *	This is a FREE software. You are free to edit and distribute it.
 *  DO NOT use it for financial profit.
 *	Created by Kruzen. 2022
 */
#include "PlanetSide.h"

UQMPalEd::PlanetSide::PlanetSide(void)
{
	{
		InitializeComponent();
		//
		//TODO: добавьте код конструктора
		//
	}
}

UQMPalEd::PlanetSide::PlanetSide(System::Drawing::Bitmap^ bmp, String^ name)
{
	InitializeComponent();

	planetSurface->Image = bmp;
	this->Text += name;
}

System::Void UQMPalEd::PlanetSide::ok_button_Click(System::Object^ sender, System::EventArgs^ e)
{
    this->Close();
}
