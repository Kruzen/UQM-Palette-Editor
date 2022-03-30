// Ur-Quan Masters Palette Editor v0.0.9

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


#include <Windows.h>
#include <WinBase.h>
#include "MainForm.h"
#include "resource.h"
#include "constdef.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace FManager;


[STAThreadAttribute]
void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	UQMPalEd::MainForm form;
	Application::Run(% form);
}

UQMPalEd::MainForm::MainForm(void)
{// Constructor	
	InitializeComponent();

	openFileDialog->Filter = "UQM color table (*.ct)|*.ct|Microsoft© palette(*.pal)|*.pal|Adobe© color table (*.act)|*.act";
	openFileDialog->FileName = "";
	importFileDialog->Filter = "Adobe© color table (*.act)|*.act|Microsoft© palette(*.pal)|*.pal";
	importFileDialog->FileName = "";

	if (getImageFromRes(IDB_PNG1))// get background from resources
		background = gcnew Bitmap(getImageFromRes(IDB_PNG1));
	else// if not found - form a white square
		background = gcnew Bitmap(320, 320);
	tableViewer->Image = background;
}

void UQMPalEd::MainForm::invokeMessageBox(String^ s, bool err)
{// Call a message box with error or warning sign
	MessageBox::Show(s, err ? "Error" : "Warning", MessageBoxButtons::OK, err ? MessageBoxIcon::Error : MessageBoxIcon::Warning);
}

void UQMPalEd::MainForm::fillTableView(array<Color>^ table)
{// draws 20x20px squares with colors from table on 320x320 grid
	Bitmap^ bmp;
	Graphics^ g;
	int x = 0;
	int y = 0;

	if (!viewFilter->Checked)
	{// if we are drawing p_table (planet filter is on) - keep true colors
		currView = gcnew array<Color>(table->Length);
		currView = table;
	}

	if (getImageFromRes(IDB_PNG1))
		bmp = gcnew Bitmap(getImageFromRes(IDB_PNG1));
	else
		bmp = gcnew Bitmap(320, 320);

	g = Graphics::FromImage(bmp);

	for (int c = 0; c < table->Length; c++)
	{
		g->FillRectangle(gcnew SolidBrush(table[c]), 20 * (x % 16), 20 * (y / 16), 20, 20);
		x++;
		y++;
	}

	tableViewer->Image = bmp;
}

void UQMPalEd::MainForm::fillDropDownSegs(int numSegs, int selected)
{
	segmentChooser->Items->Clear();
	for (int i = 0; i < numSegs; i++)
	{
		segmentChooser->Items->Add(i + 1);
	}
	segmentChooser->Enabled = true;
	segmentChooser->SelectedIndex = selected;
}

void UQMPalEd::MainForm::fillDropDownSegs(int numSegs)
{// fill dropdown list with segments of current table
	segmentChooser->Items->Clear();
	for (int i = 0; i < numSegs; i++)
	{
		segmentChooser->Items->Add(i + 1);
	}
	segmentChooser->Enabled = true;
	segmentChooser->SelectedIndex = 0;
}

void UQMPalEd::MainForm::fillDropDownTables(int numTables)
{// fill dropdown list with tables of current file
	tableChooser->Items->Clear();
	for (int i = 0; i < numTables; i++)
	{
		tableChooser->Items->Add(i + 1);
	}
	tableChooser->Enabled = true;
	tableChooser->SelectedIndex = 0;
}

void UQMPalEd::MainForm::clearTableView(void)
{// back to default image	
	tableViewer->Image = background;
	if (currView)
	{
		Array::Clear(currView, 0, currView->Length);
		delete currView;
	}
}

void UQMPalEd::MainForm::closeCurrent(void)
{// set all UI stuff to default
	this->clearTableView();
	t_displayed = 0;
	s_displayed = 0;
	mouseOver_index = MAXDWORD;
	tableChooser->Items->Clear();
	tableChooser->Enabled = false;
	segmentChooser->Items->Clear();
	segmentChooser->Enabled = false;
	closeCurrent_Button->Enabled = false;
	importButton->Enabled = false;
	openFileDialog->FileName = "";
	tableSuffix->Text = "of 0";
	segmentSuffix->Text = "of 0";
	CiT_value->Text = "0";
	CiS_value->Text = "0";
	fileName = "";
	modified = false;
	controlPanel->Text = "Control Panel";	
	viewFilter->Enabled = false;
	viewFilter->Visible = false;
	viewFilter->Checked = false;
	this->toggleBrushUI(false);
	if (ct)
	{
		ct->~ColorTable();
		delete ct;
	}
}

void UQMPalEd::MainForm::toggleFilter(bool toggle)
{
	viewFilter->Checked = false;
	viewFilter->Enabled = toggle;
	viewFilter->Visible = toggle;
}

void UQMPalEd::MainForm::toggleBrushUI(bool toggle)
{
	brushColorView->Visible = toggle;
	hexValue->Visible = toggle;
	B_RTitle->Visible = toggle;
	B_RValue->Visible = toggle;
	B_GTitle->Visible = toggle;
	B_GValue->Visible = toggle;
	B_BTitle->Visible = toggle;
	B_BValue->Visible = toggle;
	B_CIndex->Visible = toggle;
}

void UQMPalEd::MainForm::writeCurrInfo(String^ fname)
{
	fillDropDownTables(ct->getPaletteCount());
	fillDropDownSegs(ct->getSegCount(0));
	toggleFilter(ct->getPlanetCond(0));

	tableSuffix->Text = "of " + ct->getPaletteCount();
	segmentSuffix->Text = "of " + ct->getSegCount(t_displayed);
	CiT_value->Text = ct->getPaletteColorCount(t_displayed).ToString();
	CiS_value->Text = ct->getSegmentColorCount(t_displayed, s_displayed).ToString();
	controlPanel->Text = "Control Panel - " + fname;
}

Image^ UQMPalEd::MainForm::getImageFromRes(long resource_ID)
{
	// Function getImageFromRes
	// A function for loading PNG images from resources in C++ CLR/CLI
	// Copyright (C) Giuseppe Pischedda 2007 for most code
	// and a little part of this code by Bordon and adapted by me for PNG images in C++ CLR/CLI.

	HMODULE hInst = NULL;
	HRSRC hResource = ::FindResource(hInst, MAKEINTRESOURCE(resource_ID), L"PNG");
	if (!hResource)
		return nullptr;

	DWORD Size = SizeofResource(hInst, hResource);
	HGLOBAL MemoryHandle = LoadResource(hInst, hResource);
	if (MemoryHandle == NULL)
		return nullptr;

	cli::array<BYTE>^ MemPtr = gcnew array<BYTE>(Size + 2);
	char* lkr = (char*)(LockResource(MemoryHandle));
	System::Runtime::InteropServices::Marshal::Copy((IntPtr)lkr, MemPtr, 0, Size);
	System::IO::MemoryStream^ stream = gcnew System::IO::MemoryStream(MemPtr);
	stream->Write(MemPtr, 0, Size);
	stream->Position = 0;
	FreeLibrary(hInst);

	System::Drawing::Image^ ptrPNG;
	ptrPNG = System::Drawing::Image::FromStream(stream);
	return ptrPNG;
}

System::Void UQMPalEd::MainForm::openFile_Button_Click(System::Object^ sender, System::EventArgs^ e)
{// file opening routine
	String^ fname;
	FileManager^ fm;

	openFileDialog->FileName = "";
	openFileDialog->ShowDialog();
	fname = openFileDialog->FileName;

	if (fname == "")
		return;

	try
	{
		fm = gcnew FileManager();
		fm->checkFileFormat(fname);
		ct = gcnew ColorTable(fm->getPaletteCount());
		ct->distrubutePalettes(fm->extractColorBytes(), fm->getPaletteLengths());
		fileName = fm->getFileName();
	}
	catch (Exception^ e)
	{
		invokeMessageBox(e->ToString(), true);
		return;
	}

	// at this point no exceptions should occur
	t_displayed = 0;
	s_displayed = 0;
	mouseOver_index = MAXDWORD;
	fillTableView(ct->getColorPalette(t_displayed, s_displayed));

	this->writeCurrInfo(Path::GetFileName(fileName));

	closeCurrent_Button->Enabled = true;// unlock "Close" button
	importButton->Enabled = true;

	fm->~FileManager();
	delete fm;
}

System::Void UQMPalEd::MainForm::closeCurrent_Button_Click(System::Object^ sender, System::EventArgs^ e)
{// clear stuff
	closeCurrent();
}

System::Void UQMPalEd::MainForm::tableChooser_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{// switch viewer to a 0-index segment of a new table
	if (tableChooser->SelectedIndex != t_displayed)
	{
		t_displayed = tableChooser->SelectedIndex;
		fillDropDownSegs(ct->getSegCount(t_displayed));
		fillTableView(ct->getColorPalette(t_displayed, 0, viewFilter->Checked));
		segmentSuffix->Text = "of " + ct->getSegCount(t_displayed);
		CiT_value->Text = ct->getPaletteColorCount(t_displayed).ToString();
		CiS_value->Text = ct->getSegmentColorCount(t_displayed, 0).ToString();
	}
}

System::Void UQMPalEd::MainForm::exit_Button_Click(System::Object^ sender, System::EventArgs^ e)
{// close program
	this->Close();
}

System::Void UQMPalEd::MainForm::segmentChooser_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{// switch viewver to a new segment of a current table
	if (segmentChooser->SelectedIndex != s_displayed)
	{
		s_displayed = segmentChooser->SelectedIndex;
		//no need to pass viewFilter check here, planet.ct(s) always have 1 segment per table
		fillTableView(ct->getColorPalette(t_displayed, s_displayed));
		CiS_value->Text = ct->getSegmentColorCount(t_displayed, s_displayed).ToString();
	}
}

System::Void UQMPalEd::MainForm::viewFilter_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (viewFilter->Enabled)
		fillTableView(ct->getColorPalette(t_displayed, s_displayed, viewFilter->Checked));
}

System::Void UQMPalEd::MainForm::tableViewer_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	int x_index = MIN((Cursor->Position.X - tableViewer->Location.X - this->Location.X - 7) / 20, 15);
	int y_index = MIN((Cursor->Position.Y - tableViewer->Location.Y - this->Location.Y - 30) / 20, 15);
	int n_index = y_index * 16 + x_index;

	if (currView && n_index != mouseOver_index)
	{
		mouseOver_index = n_index;

		Bitmap^ b_bmp = gcnew Bitmap(brushColorView->Size.Width, brushColorView->Size.Height);
		Graphics^ g = Graphics::FromImage(b_bmp);
		Color br;		

		if (mouseOver_index < currView->Length)
		{
			br = currView[mouseOver_index];

			g->FillRectangle(gcnew SolidBrush(br), 0, 0, b_bmp->Width, b_bmp->Height);

			if (!brushColorView->Visible)
				this->toggleBrushUI(true);

			B_CIndex->Text = "Color: " + mouseOver_index.ToString();
			brushColorView->Image = b_bmp;
			hexValue->Text = "#" + br.R.ToString("X2") + br.G.ToString("X2") + br.B.ToString("X2");
			B_RValue->Text = br.R.ToString();
			B_GValue->Text = br.G.ToString();
			B_BValue->Text = br.B.ToString();
		}
		else
			this->toggleBrushUI(false);
	}
}

System::Void UQMPalEd::MainForm::tableViewer_MouseEnter(System::Object^ sender, System::EventArgs^ e)
{
	if (currView)
		this->toggleBrushUI(true);

}

System::Void UQMPalEd::MainForm::tableViewer_MouseLeave(System::Object^ sender, System::EventArgs^ e)
{
	this->toggleBrushUI(false);
}

System::Void UQMPalEd::MainForm::importButton_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (!ct)
		return;

	String^ fname;
	FileManager^ fm;

	importFileDialog->FileName = "";
	importFileDialog->ShowDialog();
	fname = importFileDialog->FileName;

	if (fname == "")
		return;

	try
	{
		fm = gcnew FileManager();
		fm->checkFileFormat(fname);
		fillTableView(ct->setPaletteSegment(t_displayed, s_displayed, ct->bytesToColors(fm->extractColorBytes())));

		// update misc sruff
		CiT_value->Text = ct->getPaletteColorCount(t_displayed).ToString();
		CiS_value->Text = ct->getSegmentColorCount(t_displayed, s_displayed).ToString();
		segmentSuffix->Text = "of " + ct->getSegCount(t_displayed);
		toggleFilter(ct->getPlanetCond(0));
		fillDropDownSegs(ct->getSegCount(t_displayed), s_displayed);
	}
	catch (Exception^ e)
	{
		invokeMessageBox(e->ToString(), true);
		return;
	}
	if (!modified)
	{
		modified = true;
		controlPanel->Text += "*";
	}

	fm->~FileManager();
	delete fm;
}

System::Void UQMPalEd::MainForm::newToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (ct)
	{
		ct->~ColorTable();
		delete ct;
	}

	ct = gcnew ColorTable(2, gcnew array<int>{ 259, 256 });

	fillTableView(ct->getColorPalette(0, 0));

	this->writeCurrInfo("Untitled.ct");

	closeCurrent_Button->Enabled = true;// unlock "Close" button
	importButton->Enabled = true;// unlock "Import" button
}
