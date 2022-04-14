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


#include <Windows.h>
#include <WinBase.h>
#include "MainForm.h"
#include "resource.h"
#include "constdef.h"
#include "CreateForm.h"
#include "PlanetSide.h"
#include "Plandata.h"
#include "GenPlanet.h"
#include <wchar.h>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace FManager;


[STAThreadAttribute]
void main(array<String^>^ args) {// entry point
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	UQMPalEd::MainForm form;
	Application::Run(% form);
}

UQMPalEd::MainForm::MainForm(void)
{// Constructor	
	InitializeComponent();

	openFileDialog->Filter = ALL_FILTER;
	openFileDialog->FileName = "";
	importFileDialog->Filter = PAL_FILTER;
	importFileDialog->FileName = "";
	saveFileDialog->Filter = ALL_FILTER;
	saveFileDialog->FileName = "";

	if (getImageFromRes(IDB_PNG1))// get background from resources
		background = gcnew Bitmap(getImageFromRes(IDB_PNG1));
	else// if not found - form a white square
		background = gcnew Bitmap(320, 320);
	tableViewer->Image = background;

	mouseOver_index = MAXDWORD;
	selected_index = MAXDWORD;

	colorDialog->ShowHelp = false;
	colorDialog->AllowFullOpen = true;
	colorDialog->FullOpen = true;

	algoChooser->Items->Add("Default");
	algoChooser->Items->Add("Crater");
	algoChooser->Items->Add("Gas Giant");
	algoChooser->SelectedIndex = 0;

	for (int i = 0; i <= NUMBER_OF_PLANET_TYPES; i++)
		presetBox->Items->Add(gcnew String(planet_name_array[i].c_str()));

	for (int i = 0; i <= NUMBERS_OF_XLTS; i++)
		xltPresetBox->Items->Add(gcnew String(xlts_name_array[i].c_str()));
	
	//debug->Text += (158 % 210);
}




// Misc UI methods //
void UQMPalEd::MainForm::invokeMessageBox(String^ s, bool err)
{// Call a message box with error or warning sign
	MessageBox::Show(s, err ? "Error" : "Warning", MessageBoxButtons::OK, err ? MessageBoxIcon::Error : MessageBoxIcon::Warning);
}

void UQMPalEd::MainForm::fillTableView(array<Color>^ table)
{// draws 20x20px squares with colors from table on 320x320 grid
	Bitmap^ bmp = (Bitmap^)background->Clone();;
	Graphics^ g = Graphics::FromImage(bmp);
	int x = 0;
	int y = 0;

	for (int c = 0; c < table->Length; c++)
	{
		g->FillRectangle(gcnew SolidBrush(table[c]), 20 * (x % 16), 20 * (y / 16), 20, 20);
		x++;
		y++;
	}

	tableViewer->Image = bmp;
	currBackground = bmp;
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

void UQMPalEd::MainForm::fillDropDownSegs(int numSegs, int selected)
{// same as previous but select not first segment
	segmentChooser->Items->Clear();
	for (int i = 0; i < numSegs; i++)
	{
		segmentChooser->Items->Add(i + 1);
	}
	segmentChooser->Enabled = true;
	segmentChooser->SelectedIndex = selected;
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

void UQMPalEd::MainForm::writeCurrInfo(String^ fname)
{// write info into control panel
	fillDropDownTables(ct->getPaletteCount());
	fillDropDownSegs(ct->getSegCount(0));
	toggleFilter(ct->getPlanetCond(0));

	tableSuffix->Text = "of " + ct->getPaletteCount();
	segmentSuffix->Text = "of " + ct->getSegCount(t_displayed);
	CiT_value->Text = ct->getPaletteColorCount(t_displayed).ToString();
	CiS_value->Text = ct->getSegmentColorCount(t_displayed, s_displayed).ToString();
	controlPanel->Text = "Control Panel - " + fname;
}

void UQMPalEd::MainForm::toggleFilter(bool toggle)
{// toggle in-game filter for planet.ct
	viewFilter->Checked = false;
	viewFilter->Enabled = toggle;
	viewFilter->Visible = toggle;
	genPlanet->Enabled = toggle;
}

void UQMPalEd::MainForm::clearTableView(void)
{// back to default image	
	tableViewer->Image = background;
}

void UQMPalEd::MainForm::closeCurrent(void)
{// set all UI stuff to default
	this->clearTableView();
	t_displayed = 0;
	s_displayed = 0;
	mouseOver_index = MAXDWORD;
	selected_index = MAXDWORD;
	tableChooser->Items->Clear();
	tableChooser->Enabled = false;
	segmentChooser->Items->Clear();
	segmentChooser->Enabled = false;
	closeCurrent_Button->Enabled = false;
	importButton->Enabled = false;
	saveToolStripMenuItem->Enabled = false;
	saveAsToolStripMenuItem->Enabled = false;
	openFileDialog->FileName = "";
	tableSuffix->Text = "of 0";
	segmentSuffix->Text = "of 0";
	CiT_value->Text = "0";
	CiS_value->Text = "0";
	fileName = "";
	modified = false;
	controlPanel->Text = "Control Panel";
	this->toggleFilter(false);
	this->toggleBrushUI(false);
}




// Brush methods //
void UQMPalEd::MainForm::toggleBrushUI(bool toggle)
{// show/hide brush
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

void UQMPalEd::MainForm::writeBrushInfo(void)
{// write info into brush panel
	Bitmap^ b_bmp = gcnew Bitmap(brushColorView->Size.Width, brushColorView->Size.Height);
	Graphics^ g = Graphics::FromImage(b_bmp);
	Color brush;

	if (mouseOver_index < ct->getSegmentColorCount(t_displayed, s_displayed))
	{
		brush = ct->getColorFromPalette(t_displayed, s_displayed, mouseOver_index);

		g->FillRectangle(gcnew SolidBrush(brush), 0, 0, b_bmp->Width, b_bmp->Height);

		if (!brushColorView->Visible)
			this->toggleBrushUI(true);

		B_CIndex->Text = "Color: " + mouseOver_index.ToString();
		brushColorView->Image = b_bmp;
		hexValue->Text = "#" + brush.R.ToString("X2") + brush.G.ToString("X2") + brush.B.ToString("X2");
		B_RValue->Text = brush.R.ToString();
		B_GValue->Text = brush.G.ToString();
		B_BValue->Text = brush.B.ToString();
	}
	else
		this->toggleBrushUI(false);
}

void UQMPalEd::MainForm::removeSelection(void)
{// clear selection if exist
	if (selected_index != MAXDWORD)
	{
		selected_index = MAXDWORD;
		tableViewer->Image = currBackground;
		this->toggleBrushUI(false);
	}
}




// Non-UI methods //
void UQMPalEd::MainForm::saveFile(String^ fname)
{// save file
	FileManager^ fm;
	
	try
	{
		if (Path::GetExtension(fname) != ".ct")
		{
			fm = gcnew FileManager(fname, 1, gcnew array<int>{(ct->getSegmentColorCount(t_displayed, s_displayed))});
			fm->writeIntupFile(ct->colorsToBytes(ct->getColorPalette(t_displayed, s_displayed)));
		}
		else
		{
			fm = gcnew FileManager(fname, ct->getPaletteCount(), ct->getPaletteLengths());
			fm->writeIntupFile(ct->getEverything());
		}		
	}
	catch (Exception^ e)
	{
		invokeMessageBox(e->ToString(), true);
		return;
	}

	modified = false;

	if (Path::GetExtension(fname) == ".ct" || (ct->getPaletteCount() == 1 && ct->getPaletteColorCount(t_displayed) <= 256))
		fileName = fname;
	else// .ct in spirit	
		fileName = Path::ChangeExtension(fname, ".ct");

		
	controlPanel->Text = "Control Panel - " + Path::GetFileName(fileName);

	fm->~FileManager();
	delete fm;
}

void UQMPalEd::MainForm::createNewTable(int paletteCount, array<int>^ paletteLengths)
{
	if (ct)
	{
		ct->~ColorTable();
		delete ct;
	}

	ct = gcnew ColorTable(paletteCount, paletteLengths);

	t_displayed = 0;
	s_displayed = 0;
	mouseOver_index = 0;
	fillTableView(ct->getColorPalette(t_displayed, s_displayed));

	fileName = "Untitled";
	this->writeCurrInfo(fileName);

	closeCurrent_Button->Enabled = true;// unlock "Close" button
	importButton->Enabled = true;// unlock "Import" button
	saveToolStripMenuItem->Enabled = true;
	saveAsToolStripMenuItem->Enabled = true;
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





// Menu methods
System::Void UQMPalEd::MainForm::newToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{// create New .ct

	CreateForm^ create = gcnew CreateForm(this);
	create->Show();
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
	mouseOver_index = 0;
	fillTableView(ct->getColorPalette(t_displayed, s_displayed));

	writeCurrInfo(Path::GetFileName(fileName));

	closeCurrent_Button->Enabled = true;// unlock "Close" button
	importButton->Enabled = true;
	saveToolStripMenuItem->Enabled = true;
	saveAsToolStripMenuItem->Enabled = true;

	fm->~FileManager();
	delete fm;
}

System::Void UQMPalEd::MainForm::saveToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{// save file
	if (!ct)
		return;

	String^ fname = "";

	if (fileName == "Untitled")
	{// newly created
		saveFileDialog->FileName = "";
		saveFileDialog->ShowDialog();
		fname = saveFileDialog->FileName;
	}
	else if (modified)
		fname = fileName;

	if (fname == "")
		return;

	this->saveFile(fname);

}

System::Void UQMPalEd::MainForm::saveAsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{// save file as
	if (!ct)
		return;

	String^ fname;

	saveFileDialog->FileName = "";
	saveFileDialog->ShowDialog();
	fname = saveFileDialog->FileName;

	if (fname == "")
		return;

	this->saveFile(fname);
}

System::Void UQMPalEd::MainForm::importButton_Click(System::Object^ sender, System::EventArgs^ e)
{// import segment
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

System::Void UQMPalEd::MainForm::closeCurrent_Button_Click(System::Object^ sender, System::EventArgs^ e)
{// clear stuff
	if (ct)
	{
		ct->~ColorTable();
		delete ct;
	}
	closeCurrent();
}

System::Void UQMPalEd::MainForm::exit_Button_Click(System::Object^ sender, System::EventArgs^ e)
{// close program
	this->Close();
}





// Event listeners //
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
{// turn on/off filter
	if (viewFilter->Enabled)
	{
		fillTableView(ct->getColorPalette(t_displayed, s_displayed, viewFilter->Checked));

		this->removeSelection();
	}
}

System::Void UQMPalEd::MainForm::tableViewer_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{// recalculate index mouse is pointing at
	if (mouseOver_index != MAXDWORD)
	{
		int x_index = MIN((Cursor->Position.X - tableViewer->Location.X - this->Location.X - 7) / 20, 15);
		int y_index = MIN((Cursor->Position.Y - tableViewer->Location.Y - this->Location.Y - 30) / 20, 15);
		int n_index = y_index * 16 + x_index;

		if (n_index != mouseOver_index)
		{
			mouseOver_index = n_index;

			if (selected_index == MAXDWORD)
				this->writeBrushInfo();
		}
	}
}

System::Void UQMPalEd::MainForm::tableViewer_MouseEnter(System::Object^ sender, System::EventArgs^ e)
{// turn on tableViewer_MouseMove()
	if (mouseOver_index != MAXDWORD)
		this->toggleBrushUI(true);

}

System::Void UQMPalEd::MainForm::tableViewer_MouseLeave(System::Object^ sender, System::EventArgs^ e)
{// turn off tableViewer_MouseMove()
	if (selected_index == MAXDWORD)
		this->toggleBrushUI(false);
}

System::Void UQMPalEd::MainForm::tableViewer_Click(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{// highlight selected cell
	if (mouseOver_index != MAXDWORD)
	{
		if (mouseOver_index < ct->getSegmentColorCount(t_displayed, s_displayed))
		{
			selected_index = mouseOver_index;
			{
				Bitmap^ b_bmp = (Bitmap^)currBackground->Clone();
				Graphics^ g = Graphics::FromImage(b_bmp);

				Color positive = ct->getColorFromPalette(t_displayed, s_displayed, selected_index);
				Color negative = Color::FromArgb(0xFF - positive.R, 0xFF - positive.G, 0xFF - positive.B);

				g->DrawRectangle(gcnew Pen(negative, 3), INDEX_TO_X(selected_index) * 20, INDEX_TO_Y(selected_index) * 20, 20, 20);

				tableViewer->Image = b_bmp;

				this->writeBrushInfo();
			}
		}
		else if(selected_index != MAXDWORD)
		{
			selected_index = MAXDWORD;
			tableViewer->Image = currBackground;
			this->toggleBrushUI(false);
		}
	}

	return;
}

System::Void UQMPalEd::MainForm::tableViewer_DoubleClick(System::Object^ sender, System::EventArgs^ e)
{
	if (mouseOver_index != MAXDWORD && selected_index != MAXDWORD)
	{
		colorDialog->Color = ct->getColorFromPalette(t_displayed, s_displayed, selected_index);

		if (colorDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			ct->setColorFromPalette(t_displayed, s_displayed, selected_index, colorDialog->Color);
			fillTableView(ct->getColorPalette(t_displayed, s_displayed));
			selected_index = MAXDWORD;
		}
	}
}

System::Void UQMPalEd::MainForm::MainForm_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{// remove highlight from cell
	
	this->removeSelection();
}




/* Planet generation */
System::Void UQMPalEd::MainForm::genButton_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (!xlt || !ct)
		return;

	//char* d = (char*)calloc(840 * 268, sizeof(char));
	char* d = (char*)malloc(840*268);
	GenPlanet* gp;
	TopoFrame desc;
	Bitmap^ tFrame = gcnew Bitmap(840, 268);

	
	try
	{
		if (seedInput->Text != "")
			gp = new GenPlanet(Convert::ToInt32(seedInput->Text));
		else
			gp = new GenPlanet();

		desc.algo = algoChooser->SelectedIndex;
		desc.num_faults = Convert::ToInt32(gpFaults->Text);
		desc.fault_depth = Convert::ToInt32(gpDepth->Text);
		desc.num_blemishes = Convert::ToInt32(gpBlem->Text);
		desc.base_elevation = Convert::ToInt32(gpElev->Text);

		std::memset(d, 0, 840 * 268);
		gp->generatePlanetSurface(d, &desc);
		delete gp;

		
		short c;
		char* pSrc = d;
		for (short i = 0; i < 268; ++i)
		{
			for (short j = 0; j < 840; ++j, ++pSrc)
			{
				c = *pSrc;
				if (desc.algo == GAS_GIANT_ALGO)
				{
					c &= 0xFF;
				}
				else				
				{
					c += desc.base_elevation;//(int)((float)(desc.base_elevation) * 1.3);
					if (c < 0)
						c = 0;
					if (c > 255)
						c = 255;
				}
				tFrame->SetPixel(j, i, ct->getColorFromPPalette(t_displayed, s_displayed, xlt[c] - 128));
			}			
		}
	}
	catch (Exception^ e)
	{
		this->invokeMessageBox(e->Message, true);
	}
	free(d);
	String^ vals = "(" + desc.num_faults + "," + desc.fault_depth + "," + desc.num_blemishes + "," + desc.base_elevation + ")";
	String^ name = ": " + Path::GetFileName(fileName) + " + " + load_xltButton->Text + vals;
	PlanetSide^ ps = gcnew PlanetSide(tFrame, name);
	ps->Show();
//	
}

System::Void UQMPalEd::MainForm::load_xltButton_Click(System::Object^ sender, System::EventArgs^ e)
{
	String^ fname;
	FileManager^ fm;

	importFileDialog->FileName = "";
	importFileDialog->Filter = XLT_FILTER;
	importFileDialog->ShowDialog();
	fname = importFileDialog->FileName;

	if (fname == "")
		return;

	try
	{
		fm = gcnew FileManager();
		fm->checkFileFormat(fname);
		xlt = fm->extractColorBytes();
	}
	catch (Exception^ e)
	{
		invokeMessageBox(e->ToString(), true);
		return;
	}
	importFileDialog->Filter = ALL_FILTER;
	load_xltButton->Text = fm->getFileNameFromPath();
	genButton->Enabled = true;

	fm->~FileManager();
	delete fm;
}

System::Void UQMPalEd::MainForm::presetBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (presetBox->SelectedIndex != 0)
	{
		xltPresetBox->SelectedIndex = planet_array[presetBox->SelectedIndex - 1] + 1;
	}
}

System::Void UQMPalEd::MainForm::gpInput_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
{
	if (!Char::IsDigit(e->KeyChar) && !Char::IsControl(e->KeyChar))
		e->Handled = true;

	if (presetBox->SelectedIndex != 0)
		presetBox->SelectedIndex = 0;

	if (xltPresetBox->SelectedIndex != 0)
		xltPresetBox->SelectedIndex = 0;
}

System::Void UQMPalEd::MainForm::xltPresetBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (xltPresetBox->SelectedIndex != 0)
	{
		gpFaults->Text = xlat_tables[xltPresetBox->SelectedIndex - 1].num_faults.ToString();
		gpDepth->Text = xlat_tables[xltPresetBox->SelectedIndex - 1].fault_depth.ToString();
		gpBlem->Text = xlat_tables[xltPresetBox->SelectedIndex - 1].num_blemishes.ToString();
		gpElev->Text = xlat_tables[xltPresetBox->SelectedIndex - 1].base_elevation.ToString();
		algoChooser->SelectedIndex = xlat_tables[xltPresetBox->SelectedIndex - 1].algo;
	}
}

System::Void UQMPalEd::MainForm::seedInput_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
{
	if (!Char::IsDigit(e->KeyChar) && !Char::IsControl(e->KeyChar))
		e->Handled = true;
}
