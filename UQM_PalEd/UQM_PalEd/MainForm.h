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

#pragma once
#include "ColorTable.h"
#include "FileManager.h"

namespace UQMPalEd {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace CTable;

	/// <summary>
	/// —водка дл¤ MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void);
	private:
		int t_displayed;
		int s_displayed;
		static int mouseOver_index;
	private: System::Windows::Forms::GroupBox^ brushBox;
	public:
	private: System::Windows::Forms::PictureBox^ brushColorView;
	private: System::Windows::Forms::Label^ hexValue;
	private: System::Windows::Forms::Label^ B_BTitle;
	private: System::Windows::Forms::Label^ B_GTitle;
	private: System::Windows::Forms::Label^ B_RTitle;
	private: System::Windows::Forms::Label^ B_BValue;
	private: System::Windows::Forms::Label^ B_GValue;
	private: System::Windows::Forms::Label^ B_RValue;
	private: System::Windows::Forms::Label^ B_CIndex;

	public:
		ColorTable^ ct;
		String^ fileName;
		bool modified;
	private: System::Windows::Forms::OpenFileDialog^ importFileDialog;
	public:
		Bitmap^ background;
		void invokeMessageBox(String^ s, bool err);
		void fillTableView(array<Color>^ table);
		void fillDropDownSegs(int numSegs, int selected);
		void fillDropDownSegs(int numSegs);
		void fillDropDownTables(int numTables);
		void clearTableView(void);
		void closeCurrent(void);
		void toggleFilter(bool toggle);
		void toggleBrushUI(bool toggle);
		void writeCurrInfo(String^ fname);
		Image^ getImageFromRes(long resource_ID);
	private: System::Windows::Forms::Label^ S_Title;
	private: System::Windows::Forms::ComboBox^ segmentChooser;
	private: System::Windows::Forms::GroupBox^ controlPanel;
	private: System::Windows::Forms::Label^ tableSuffix;
	private: System::Windows::Forms::Label^ segmentSuffix;
	private: System::Windows::Forms::Label^ CiT_value;
	private: System::Windows::Forms::Label^ CiT_title;
	private: System::Windows::Forms::Label^ CiS_value;
	private: System::Windows::Forms::Label^ CiS_title;
	private: System::Windows::Forms::CheckBox^ viewFilter;		   
	private: System::Windows::Forms::RichTextBox^ debug;
	private: System::Windows::Forms::Label^ debug_title;
	private: System::Windows::Forms::ComboBox^ tableChooser;
	private: System::Windows::Forms::Label^ T_Title;
	private: System::Windows::Forms::ToolStripMenuItem^ exit_Button;
	private: System::Windows::Forms::PictureBox^ tableViewer;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog;
	private: System::Windows::Forms::MenuStrip^ menuStrip;
	private: System::Windows::Forms::ToolStripMenuItem^ fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ newToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ openFile_Button;
	private: System::Windows::Forms::ToolStripMenuItem^ saveAsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ saveToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ importButton;

	private: System::Windows::Forms::ToolStripMenuItem^ abourToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^ closeCurrent_Button;


	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}


	private:
		/// <summary>
		/// ќб¤зательна¤ переменна¤ конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл¤ поддержки конструктора Ч не измен¤йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->menuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->newToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openFile_Button = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveAsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->importButton = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->closeCurrent_Button = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exit_Button = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->abourToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->debug = (gcnew System::Windows::Forms::RichTextBox());
			this->debug_title = (gcnew System::Windows::Forms::Label());
			this->tableChooser = (gcnew System::Windows::Forms::ComboBox());
			this->T_Title = (gcnew System::Windows::Forms::Label());
			this->tableViewer = (gcnew System::Windows::Forms::PictureBox());
			this->S_Title = (gcnew System::Windows::Forms::Label());
			this->segmentChooser = (gcnew System::Windows::Forms::ComboBox());
			this->controlPanel = (gcnew System::Windows::Forms::GroupBox());
			this->viewFilter = (gcnew System::Windows::Forms::CheckBox());
			this->CiS_value = (gcnew System::Windows::Forms::Label());
			this->CiS_title = (gcnew System::Windows::Forms::Label());
			this->CiT_value = (gcnew System::Windows::Forms::Label());
			this->CiT_title = (gcnew System::Windows::Forms::Label());
			this->segmentSuffix = (gcnew System::Windows::Forms::Label());
			this->tableSuffix = (gcnew System::Windows::Forms::Label());
			this->brushBox = (gcnew System::Windows::Forms::GroupBox());
			this->B_CIndex = (gcnew System::Windows::Forms::Label());
			this->B_BValue = (gcnew System::Windows::Forms::Label());
			this->B_GValue = (gcnew System::Windows::Forms::Label());
			this->B_RValue = (gcnew System::Windows::Forms::Label());
			this->B_BTitle = (gcnew System::Windows::Forms::Label());
			this->B_GTitle = (gcnew System::Windows::Forms::Label());
			this->B_RTitle = (gcnew System::Windows::Forms::Label());
			this->hexValue = (gcnew System::Windows::Forms::Label());
			this->brushColorView = (gcnew System::Windows::Forms::PictureBox());
			this->importFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->menuStrip->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tableViewer))->BeginInit();
			this->controlPanel->SuspendLayout();
			this->brushBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->brushColorView))->BeginInit();
			this->SuspendLayout();
			this->openFileDialog->FileName = L"openFileDialog1";
			this->menuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->fileToolStripMenuItem,
					this->abourToolStripMenuItem
			});
			this->menuStrip->Location = System::Drawing::Point(0, 0);
			this->menuStrip->Name = L"menuStrip";
			this->menuStrip->Size = System::Drawing::Size(624, 24);
			this->menuStrip->TabIndex = 0;
			this->menuStrip->Text = L"menuStrip1";
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {
				this->newToolStripMenuItem,
					this->openFile_Button, this->saveAsToolStripMenuItem, this->saveToolStripMenuItem, this->importButton, this->closeCurrent_Button,
					this->exit_Button
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			this->newToolStripMenuItem->Name = L"newToolStripMenuItem";
			this->newToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->newToolStripMenuItem->Text = L"New";
			this->newToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::newToolStripMenuItem_Click);
			this->openFile_Button->Name = L"openFile_Button";
			this->openFile_Button->Size = System::Drawing::Size(180, 22);
			this->openFile_Button->Text = L"Open";
			this->openFile_Button->Click += gcnew System::EventHandler(this, &MainForm::openFile_Button_Click);
			this->saveAsToolStripMenuItem->Enabled = false;
			this->saveAsToolStripMenuItem->Name = L"saveAsToolStripMenuItem";
			this->saveAsToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->saveAsToolStripMenuItem->Text = L"Save As";
			this->saveToolStripMenuItem->Enabled = false;
			this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
			this->saveToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->saveToolStripMenuItem->Text = L"Save";
			this->importButton->Enabled = false;
			this->importButton->Name = L"importButton";
			this->importButton->Size = System::Drawing::Size(180, 22);
			this->importButton->Text = L"Import Segment";
			this->importButton->Click += gcnew System::EventHandler(this, &MainForm::importButton_Click);
			this->closeCurrent_Button->Enabled = false;
			this->closeCurrent_Button->Name = L"closeCurrent_Button";
			this->closeCurrent_Button->Size = System::Drawing::Size(180, 22);
			this->closeCurrent_Button->Text = L"Close";
			this->closeCurrent_Button->Click += gcnew System::EventHandler(this, &MainForm::closeCurrent_Button_Click);
			this->exit_Button->Name = L"exit_Button";
			this->exit_Button->Size = System::Drawing::Size(180, 22);
			this->exit_Button->Text = L"Exit";
			this->exit_Button->Click += gcnew System::EventHandler(this, &MainForm::exit_Button_Click);
			this->abourToolStripMenuItem->Enabled = false;
			this->abourToolStripMenuItem->Name = L"abourToolStripMenuItem";
			this->abourToolStripMenuItem->Size = System::Drawing::Size(52, 20);
			this->abourToolStripMenuItem->Text = L"About";
			this->debug->Enabled = false;
			this->debug->Location = System::Drawing::Point(559, 234);
			this->debug->Name = L"debug";
			this->debug->Size = System::Drawing::Size(53, 88);
			this->debug->TabIndex = 2;
			this->debug->Text = L"";
			this->debug->Visible = false;
			this->debug_title->AutoSize = true;
			this->debug_title->Location = System::Drawing::Point(556, 218);
			this->debug_title->Name = L"debug_title";
			this->debug_title->Size = System::Drawing::Size(39, 13);
			this->debug_title->TabIndex = 3;
			this->debug_title->Text = L"Debug";
			this->debug_title->Visible = false;
			this->tableChooser->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->tableChooser->Enabled = false;
			this->tableChooser->Location = System::Drawing::Point(55, 22);
			this->tableChooser->Name = L"tableChooser";
			this->tableChooser->Size = System::Drawing::Size(50, 21);
			this->tableChooser->TabIndex = 4;
			this->tableChooser->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::tableChooser_SelectedIndexChanged);
			this->T_Title->AutoSize = true;
			this->T_Title->Location = System::Drawing::Point(6, 25);
			this->T_Title->Name = L"T_Title";
			this->T_Title->Size = System::Drawing::Size(43, 13);
			this->T_Title->TabIndex = 5;
			this->T_Title->Text = L"Palette:";
			this->tableViewer->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->tableViewer->Cursor = System::Windows::Forms::Cursors::Cross;
			this->tableViewer->Location = System::Drawing::Point(12, 129);
			this->tableViewer->Name = L"tableViewer";
			this->tableViewer->Size = System::Drawing::Size(320, 320);
			this->tableViewer->TabIndex = 6;
			this->tableViewer->TabStop = false;
			this->tableViewer->MouseEnter += gcnew System::EventHandler(this, &MainForm::tableViewer_MouseEnter);
			this->tableViewer->MouseLeave += gcnew System::EventHandler(this, &MainForm::tableViewer_MouseLeave);
			this->tableViewer->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::tableViewer_MouseMove);
			this->S_Title->AutoSize = true;
			this->S_Title->Location = System::Drawing::Point(159, 25);
			this->S_Title->Name = L"S_Title";
			this->S_Title->Size = System::Drawing::Size(52, 13);
			this->S_Title->TabIndex = 7;
			this->S_Title->Text = L"Segment:";
			this->segmentChooser->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->segmentChooser->Enabled = false;
			this->segmentChooser->FormattingEnabled = true;
			this->segmentChooser->Location = System::Drawing::Point(217, 22);
			this->segmentChooser->Name = L"segmentChooser";
			this->segmentChooser->Size = System::Drawing::Size(50, 21);
			this->segmentChooser->TabIndex = 8;
			this->segmentChooser->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::segmentChooser_SelectedIndexChanged);
			this->controlPanel->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->controlPanel->Controls->Add(this->viewFilter);
			this->controlPanel->Controls->Add(this->CiS_value);
			this->controlPanel->Controls->Add(this->CiS_title);
			this->controlPanel->Controls->Add(this->CiT_value);
			this->controlPanel->Controls->Add(this->CiT_title);
			this->controlPanel->Controls->Add(this->segmentSuffix);
			this->controlPanel->Controls->Add(this->tableSuffix);
			this->controlPanel->Controls->Add(this->T_Title);
			this->controlPanel->Controls->Add(this->segmentChooser);
			this->controlPanel->Controls->Add(this->tableChooser);
			this->controlPanel->Controls->Add(this->S_Title);
			this->controlPanel->Location = System::Drawing::Point(12, 27);
			this->controlPanel->Name = L"controlPanel";
			this->controlPanel->Size = System::Drawing::Size(320, 96);
			this->controlPanel->TabIndex = 9;
			this->controlPanel->TabStop = false;
			this->controlPanel->Text = L"Control Panel";
			this->viewFilter->AutoSize = true;
			this->viewFilter->Enabled = false;
			this->viewFilter->Location = System::Drawing::Point(162, 72);
			this->viewFilter->Name = L"viewFilter";
			this->viewFilter->Size = System::Drawing::Size(156, 17);
			this->viewFilter->TabIndex = 10;
			this->viewFilter->Text = L"Planet surface in-game filter";
			this->viewFilter->UseVisualStyleBackColor = false;
			this->viewFilter->Visible = false;
			this->viewFilter->CheckedChanged += gcnew System::EventHandler(this, &MainForm::viewFilter_CheckedChanged);
			this->CiS_value->AutoSize = true;
			this->CiS_value->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->CiS_value->Location = System::Drawing::Point(263, 56);
			this->CiS_value->Name = L"CiS_value";
			this->CiS_value->Size = System::Drawing::Size(14, 13);
			this->CiS_value->TabIndex = 14;
			this->CiS_value->Text = L"0";
			this->CiS_title->AutoSize = true;
			this->CiS_title->Location = System::Drawing::Point(159, 56);
			this->CiS_title->Name = L"CiS_title";
			this->CiS_title->Size = System::Drawing::Size(108, 13);
			this->CiS_title->TabIndex = 13;
			this->CiS_title->Text = L"Total segment colors:";
			this->CiT_value->AutoSize = true;
			this->CiT_value->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->CiT_value->Location = System::Drawing::Point(102, 56);
			this->CiT_value->Name = L"CiT_value";
			this->CiT_value->Size = System::Drawing::Size(14, 13);
			this->CiT_value->TabIndex = 12;
			this->CiT_value->Text = L"0";
			this->CiT_title->AutoSize = true;
			this->CiT_title->Location = System::Drawing::Point(6, 56);
			this->CiT_title->Name = L"CiT_title";
			this->CiT_title->Size = System::Drawing::Size(100, 13);
			this->CiT_title->TabIndex = 11;
			this->CiT_title->Text = L"Total palette colors:";
			this->segmentSuffix->AutoSize = true;
			this->segmentSuffix->Location = System::Drawing::Point(272, 25);
			this->segmentSuffix->Name = L"segmentSuffix";
			this->segmentSuffix->Size = System::Drawing::Size(25, 13);
			this->segmentSuffix->TabIndex = 10;
			this->segmentSuffix->Text = L"of 0";
			this->tableSuffix->AutoSize = true;
			this->tableSuffix->Location = System::Drawing::Point(111, 25);
			this->tableSuffix->Name = L"tableSuffix";
			this->tableSuffix->Size = System::Drawing::Size(25, 13);
			this->tableSuffix->TabIndex = 9;
			this->tableSuffix->Text = L"of 0";
			this->brushBox->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->brushBox->Controls->Add(this->B_CIndex);
			this->brushBox->Controls->Add(this->B_BValue);
			this->brushBox->Controls->Add(this->B_GValue);
			this->brushBox->Controls->Add(this->B_RValue);
			this->brushBox->Controls->Add(this->B_BTitle);
			this->brushBox->Controls->Add(this->B_GTitle);
			this->brushBox->Controls->Add(this->B_RTitle);
			this->brushBox->Controls->Add(this->hexValue);
			this->brushBox->Controls->Add(this->brushColorView);
			this->brushBox->Location = System::Drawing::Point(339, 295);
			this->brushBox->Name = L"brushBox";
			this->brushBox->Size = System::Drawing::Size(86, 153);
			this->brushBox->TabIndex = 10;
			this->brushBox->TabStop = false;
			this->brushBox->Text = L"Brush";
			this->B_CIndex->AutoSize = true;
			this->B_CIndex->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->B_CIndex->Location = System::Drawing::Point(10, 20);
			this->B_CIndex->Name = L"B_CIndex";
			this->B_CIndex->Size = System::Drawing::Size(65, 13);
			this->B_CIndex->TabIndex = 8;
			this->B_CIndex->Text = L"Color: 255";
			this->B_CIndex->Visible = false;
			this->B_BValue->AutoSize = true;
			this->B_BValue->ForeColor = System::Drawing::Color::Blue;
			this->B_BValue->Location = System::Drawing::Point(53, 137);
			this->B_BValue->Name = L"B_BValue";
			this->B_BValue->Size = System::Drawing::Size(13, 13);
			this->B_BValue->TabIndex = 7;
			this->B_BValue->Text = L"0";
			this->B_BValue->Visible = false;
			this->B_GValue->AutoSize = true;
			this->B_GValue->ForeColor = System::Drawing::Color::Lime;
			this->B_GValue->Location = System::Drawing::Point(53, 117);
			this->B_GValue->Name = L"B_GValue";
			this->B_GValue->Size = System::Drawing::Size(13, 13);
			this->B_GValue->TabIndex = 6;
			this->B_GValue->Text = L"0";
			this->B_GValue->Visible = false;
			this->B_RValue->AutoSize = true;
			this->B_RValue->ForeColor = System::Drawing::Color::Red;
			this->B_RValue->Location = System::Drawing::Point(53, 97);
			this->B_RValue->Name = L"B_RValue";
			this->B_RValue->Size = System::Drawing::Size(13, 13);
			this->B_RValue->TabIndex = 5;
			this->B_RValue->Text = L"0";
			this->B_RValue->Visible = false;
			this->B_BTitle->AutoSize = true;
			this->B_BTitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->B_BTitle->Location = System::Drawing::Point(16, 137);
			this->B_BTitle->Name = L"B_BTitle";
			this->B_BTitle->Size = System::Drawing::Size(36, 13);
			this->B_BTitle->TabIndex = 4;
			this->B_BTitle->Text = L"Blue:";
			this->B_BTitle->Visible = false;
			this->B_GTitle->AutoSize = true;
			this->B_GTitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->B_GTitle->Location = System::Drawing::Point(8, 117);
			this->B_GTitle->Name = L"B_GTitle";
			this->B_GTitle->Size = System::Drawing::Size(45, 13);
			this->B_GTitle->TabIndex = 3;
			this->B_GTitle->Text = L"Green:";
			this->B_GTitle->Visible = false;
			this->B_RTitle->AutoSize = true;
			this->B_RTitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->B_RTitle->Location = System::Drawing::Point(18, 97);
			this->B_RTitle->Name = L"B_RTitle";
			this->B_RTitle->Size = System::Drawing::Size(34, 13);
			this->B_RTitle->TabIndex = 2;
			this->B_RTitle->Text = L"Red:";
			this->B_RTitle->Visible = false;
			this->hexValue->AutoSize = true;
			this->hexValue->Location = System::Drawing::Point(18, 73);
			this->hexValue->Name = L"hexValue";
			this->hexValue->Size = System::Drawing::Size(50, 13);
			this->hexValue->TabIndex = 1;
			this->hexValue->Text = L"#000000";
			this->hexValue->Visible = false;
			this->brushColorView->Location = System::Drawing::Point(19, 36);
			this->brushColorView->Name = L"brushColorView";
			this->brushColorView->Size = System::Drawing::Size(49, 34);
			this->brushColorView->TabIndex = 0;
			this->brushColorView->TabStop = false;
			this->importFileDialog->FileName = L"openFileDialog1";
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->ClientSize = System::Drawing::Size(624, 461);
			this->Controls->Add(this->brushBox);
			this->Controls->Add(this->controlPanel);
			this->Controls->Add(this->tableViewer);
			this->Controls->Add(this->debug_title);
			this->Controls->Add(this->debug);
			this->Controls->Add(this->menuStrip);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip;
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(640, 500);
			this->MinimizeBox = false;
			this->MinimumSize = System::Drawing::Size(640, 500);
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Ur-Quan Masters Palette Editor v0.0.9";
			this->menuStrip->ResumeLayout(false);
			this->menuStrip->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tableViewer))->EndInit();
			this->controlPanel->ResumeLayout(false);
			this->controlPanel->PerformLayout();
			this->brushBox->ResumeLayout(false);
			this->brushBox->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->brushColorView))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void openFile_Button_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void closeCurrent_Button_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void tableChooser_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void exit_Button_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void segmentChooser_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void viewFilter_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void tableViewer_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void tableViewer_MouseEnter(System::Object^ sender, System::EventArgs^ e);
	private: System::Void tableViewer_MouseLeave(System::Object^ sender, System::EventArgs^ e);
	private: System::Void importButton_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void newToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
};
}
