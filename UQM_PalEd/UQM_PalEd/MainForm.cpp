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

void UQMPalEd::MainForm::fillTableView(array<Color>^ table)
{
	Bitmap^ bmp = gcnew Bitmap(320, 320);
	Graphics^ g = Graphics::FromImage(bmp);

	for (int i = 0, c = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++, c++)
		{
			g->FillRectangle(gcnew SolidBrush(table[c]), 20 * j, 20 * i, 20, 20);

			/*richTextBox1->Text += (c);
			richTextBox1->Text += "\n";*/
		}
	}

	pictureBox1->Image = bmp;
}

void UQMPalEd::MainForm::fillDropDownSegs(int numTables)
{
	for (int i = 0; i < numTables; i++)
	{
		comboBox1->Items->Add(i + 1);
	}
	comboBox1->Enabled = true;
	comboBox1->SelectedIndex = 0;
}

void UQMPalEd::MainForm::clearApp(void)
{
	{
		Bitmap^ bmp = gcnew Bitmap(320, 320);
		Graphics^ g = Graphics::FromImage(bmp);
		g->FillRectangle(gcnew SolidBrush(Color::White), 0, 0, 320, 320);
		pictureBox1->Image = bmp;
	}

	Array::Clear(table, 0, table->Length);
}

void UQMPalEd::MainForm::closeCurrent(void)
{
	clearApp();
	comboBox1->Items->Clear();
	comboBox1->Enabled = false;
	exitToolStripMenuItem1->Enabled = false;
	/* TODO: properly dispose File_Handler h */
}

System::Void UQMPalEd::MainForm::openToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	String^ fname;

	if (h)
		closeCurrent();

	h = gcnew File_Handler();

	openFileDialog1->ShowDialog();
	fname = openFileDialog1->FileName;

	if (fname == "openFileDialog1")
		return;

	h->setFileName(fname);
	h->extractContent();

	table = h->getCurrentTable();

	fillTableView(table);

	fillDropDownSegs(h->getNumTables());
	
	this->Text = "UQM PE v0.0.3 - ";
	this->Text += h->getFileName();

	exitToolStripMenuItem1->Enabled = true;
}

System::Void UQMPalEd::MainForm::exitToolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e)
{
	closeCurrent();
	this->Text = TITLE;
}

System::Void UQMPalEd::MainForm::comboBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (comboBox1->SelectedIndex != h->getCurrIndex())
	{
		clearApp();
		h->setCurrentTable(comboBox1->SelectedIndex);
		table = h->getCurrentTable();
		fillTableView(table);
		comboBox1->SelectedIndex = h->getCurrIndex();
	}
}

System::Void UQMPalEd::MainForm::exitToolStripMenuItem2_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->Close();
}
