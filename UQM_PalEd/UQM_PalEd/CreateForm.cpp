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

#include "CreateForm.h"
#include "constdef.h"


UQMPalEd::CreateForm::CreateForm(void)
{
	{
		InitializeComponent();
	}
}

UQMPalEd::CreateForm::CreateForm(UQMPalEd::MainForm^ father)
{
	InitializeComponent();
	this->father = father;
	this->father->Enabled = false;
}

System::Void UQMPalEd::CreateForm::Cancel_Button_Click(System::Object^ sender, System::EventArgs^ e)
{
	father->Enabled = true;
    this->Close();
}

System::Void UQMPalEd::CreateForm::OK_Button_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (numPalettes->Text == "")
		return;
	try
	{
		int nPals = Convert::ToInt32(numPalettes->Text);
		array<int>^ lengths = gcnew array<int>(nPals);

		{// big-ass ugly split-parse farce
			if (palLengths->Text->Trim() == "")
			{// not specified - all palettes will have default length
				for (int i = 0; i < nPals; i++)
					lengths[i] = MAX_COLORS_PER_TABLE;
			}
			else
			{
				array<String^>^ lengthsInput = (palLengths->Text->Trim())->Split(gcnew array<String^>{" "}, StringSplitOptions::RemoveEmptyEntries);

				int iter = MIN(nPals, lengthsInput->Length);// to avoid IndexOutOfRange

				for (int i = 0; i < iter; i++)
					lengths[i] = Convert::ToInt32(lengthsInput[i]);

				if (iter < nPals)
				{// if user entered less vales than specified palettes - fill the rest with the last value
					for (int i = iter; i < nPals; i++)
						lengths[i] = lengths[iter-1];
				}
			}
		}

		father->createNewTable(nPals, lengths);
		father->Enabled = true;

		delete lengths;
		this->Close();
	}
	catch (Exception^ e)
	{
		MessageBox::Show(e->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}
}

System::Void UQMPalEd::CreateForm::numPalettes_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
{
	if (!Char::IsDigit(e->KeyChar) && !Char::IsControl(e->KeyChar))
		e->Handled = true;
}

System::Void UQMPalEd::CreateForm::palLengths_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
{
	if (!Char::IsDigit(e->KeyChar) && !Char::IsControl(e->KeyChar) && e->KeyChar != ' ')
		e->Handled = true;
}
