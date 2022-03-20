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


#include <Windows.h>
#include <WinBase.h>
#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;


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

	openFileDialog->Filter = "UQM color table (*.ct)|*.ct";
	openFileDialog->FileName = "";

	if (getImageFromRes(IDB_PNG1))// get background from resources
		background = gcnew Bitmap(getImageFromRes(IDB_PNG1));
	else// if not found - form a white square
		background = gcnew Bitmap(320, 320);
	tableViewer->Image = background;

	h = gcnew File_Handler();
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
}

void UQMPalEd::MainForm::closeCurrent(void)
{// set all UI stuff to default
	clearTableView();
	tableChooser->Items->Clear();
	tableChooser->Enabled = false;
	segmentChooser->Items->Clear();
	segmentChooser->Enabled = false;
	closeCurrent_Button->Enabled = false;
	openFileDialog->FileName = "";
	tableSuffix->Text = "of 0";
	segmentSuffix->Text = "of 0";
	CiT_value->Text = "0";
	CiS_value->Text = "0";
	controlPanel->Text = "Control Panel";
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

	openFileDialog->ShowDialog();
	fname = openFileDialog->FileName;

	if (fname == "")
		return;

	try
	{
		h->checkFileFormat(fname);
		h->extractContent();
	}
	catch (Exception^ e)
	{
		invokeMessageBox(e->ToString(), true);
		return;
	}
	catch (CTException^ e)
	{
		invokeMessageBox(e->ToString(), e->IsWarning());
		return;
	}
	// at this point no exceptions should occur
	displayed = 0;
	fillTableView(h->getTable());	

	fillDropDownTables(h->getNumTables());
	fillDropDownSegs(h->getNumSegs(0));
	
	tableSuffix->Text = "of " + h->getNumTables();
	segmentSuffix->Text = "of " + h->getNumSegs(0);
	CiT_value->Text = h->getNumColors(0).ToString();
	CiS_value->Text = h->getNumSegColors(0, 0).ToString();
	controlPanel->Text = "Control Panel - " + h->getFileName();

	closeCurrent_Button->Enabled = true;// unlock "Close" button
}

System::Void UQMPalEd::MainForm::closeCurrent_Button_Click(System::Object^ sender, System::EventArgs^ e)
{// clear stuff
	closeCurrent();
}

System::Void UQMPalEd::MainForm::tableChooser_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{// switch viewer to a 0-index segment of a new table
	if (tableChooser->SelectedIndex != displayed)
	{
		fillDropDownSegs(h->getNumSegs(tableChooser->SelectedIndex));
		fillTableView(h->getTable(tableChooser->SelectedIndex, 0));
		displayed = tableChooser->SelectedIndex;
		segmentSuffix->Text = "of " + h->getNumSegs(displayed);
		CiT_value->Text = h->getNumColors(displayed).ToString();
		CiS_value->Text = h->getNumSegColors(displayed, 0).ToString();
	}
}

System::Void UQMPalEd::MainForm::exit_Button_Click(System::Object^ sender, System::EventArgs^ e)
{// close program
	this->Close();
}

System::Void UQMPalEd::MainForm::segmentChooser_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{// switch viewver to a new segment of a current table
	fillTableView(h->getTable(tableChooser->SelectedIndex, segmentChooser->SelectedIndex));
	CiS_value->Text = h->getNumSegColors(tableChooser->SelectedIndex, segmentChooser->SelectedIndex).ToString();
}
