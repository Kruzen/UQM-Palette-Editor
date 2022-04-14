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
		static unsigned int mouseOver_index;
		static unsigned int selected_index;
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
		array<Byte>^ xlt;
	private: System::Windows::Forms::OpenFileDialog^ importFileDialog;
	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog;
	public:
		Bitmap^ background;
	private: System::Windows::Forms::ColorDialog^ colorDialog;
	private: System::Windows::Forms::GroupBox^ genPlanet;
	private: System::Windows::Forms::Label^ genLabel1;
	private: System::Windows::Forms::TextBox^ gpFaults;




	private: System::Windows::Forms::Label^ genLabel4;
	private: System::Windows::Forms::TextBox^ gpElev;


	private: System::Windows::Forms::Label^ genLabel3;
	private: System::Windows::Forms::TextBox^ gpBlem;


	private: System::Windows::Forms::Label^ genLabel2;
	private: System::Windows::Forms::TextBox^ gpDepth;

	private: System::Windows::Forms::Button^ genButton;
	private: System::Windows::Forms::Button^ load_xltButton;
	private: System::Windows::Forms::ComboBox^ algoChooser;
	private: System::Windows::Forms::Label^ algoLabel;
	private: System::Windows::Forms::Label^ seedLabel;
	private: System::Windows::Forms::TextBox^ seedInput;
	private: System::Windows::Forms::Label^ presetLabel;
	private: System::Windows::Forms::ComboBox^ presetBox;
	private: System::Windows::Forms::Label^ xltPresetLabel;
	private: System::Windows::Forms::ComboBox^ xltPresetBox;

	public:

	public:
		Bitmap^ currBackground;
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
		void writeBrushInfo(void);
		void saveFile(String^ fname);
		void removeSelection(void);
		void createNewTable(int paletteCount, array<int>^ paletteLengths);
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
	private: System::Windows::Forms::ToolStripMenuItem^ saveToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ saveAsToolStripMenuItem;



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
			this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveAsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
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
			this->saveFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->colorDialog = (gcnew System::Windows::Forms::ColorDialog());
			this->genPlanet = (gcnew System::Windows::Forms::GroupBox());
			this->xltPresetLabel = (gcnew System::Windows::Forms::Label());
			this->xltPresetBox = (gcnew System::Windows::Forms::ComboBox());
			this->presetLabel = (gcnew System::Windows::Forms::Label());
			this->presetBox = (gcnew System::Windows::Forms::ComboBox());
			this->algoLabel = (gcnew System::Windows::Forms::Label());
			this->seedLabel = (gcnew System::Windows::Forms::Label());
			this->seedInput = (gcnew System::Windows::Forms::TextBox());
			this->algoChooser = (gcnew System::Windows::Forms::ComboBox());
			this->load_xltButton = (gcnew System::Windows::Forms::Button());
			this->genButton = (gcnew System::Windows::Forms::Button());
			this->genLabel4 = (gcnew System::Windows::Forms::Label());
			this->gpElev = (gcnew System::Windows::Forms::TextBox());
			this->genLabel3 = (gcnew System::Windows::Forms::Label());
			this->gpBlem = (gcnew System::Windows::Forms::TextBox());
			this->genLabel2 = (gcnew System::Windows::Forms::Label());
			this->gpDepth = (gcnew System::Windows::Forms::TextBox());
			this->genLabel1 = (gcnew System::Windows::Forms::Label());
			this->gpFaults = (gcnew System::Windows::Forms::TextBox());
			this->menuStrip->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tableViewer))->BeginInit();
			this->controlPanel->SuspendLayout();
			this->brushBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->brushColorView))->BeginInit();
			this->genPlanet->SuspendLayout();
			this->SuspendLayout();
			// 
			// openFileDialog
			// 
			this->openFileDialog->FileName = L"openFileDialog1";
			// 
			// menuStrip
			// 
			this->menuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->fileToolStripMenuItem,
					this->abourToolStripMenuItem
			});
			this->menuStrip->Location = System::Drawing::Point(0, 0);
			this->menuStrip->Name = L"menuStrip";
			this->menuStrip->Size = System::Drawing::Size(624, 24);
			this->menuStrip->TabIndex = 0;
			this->menuStrip->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {
				this->newToolStripMenuItem,
					this->openFile_Button, this->saveToolStripMenuItem, this->saveAsToolStripMenuItem, this->importButton, this->closeCurrent_Button,
					this->exit_Button
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// newToolStripMenuItem
			// 
			this->newToolStripMenuItem->Name = L"newToolStripMenuItem";
			this->newToolStripMenuItem->Size = System::Drawing::Size(159, 22);
			this->newToolStripMenuItem->Text = L"New";
			this->newToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::newToolStripMenuItem_Click);
			// 
			// openFile_Button
			// 
			this->openFile_Button->Name = L"openFile_Button";
			this->openFile_Button->Size = System::Drawing::Size(159, 22);
			this->openFile_Button->Text = L"Open";
			this->openFile_Button->Click += gcnew System::EventHandler(this, &MainForm::openFile_Button_Click);
			// 
			// saveToolStripMenuItem
			// 
			this->saveToolStripMenuItem->Enabled = false;
			this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
			this->saveToolStripMenuItem->Size = System::Drawing::Size(159, 22);
			this->saveToolStripMenuItem->Text = L"Save";
			this->saveToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::saveToolStripMenuItem_Click);
			// 
			// saveAsToolStripMenuItem
			// 
			this->saveAsToolStripMenuItem->Enabled = false;
			this->saveAsToolStripMenuItem->Name = L"saveAsToolStripMenuItem";
			this->saveAsToolStripMenuItem->Size = System::Drawing::Size(159, 22);
			this->saveAsToolStripMenuItem->Text = L"Save As";
			this->saveAsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::saveAsToolStripMenuItem_Click);
			// 
			// importButton
			// 
			this->importButton->Enabled = false;
			this->importButton->Name = L"importButton";
			this->importButton->Size = System::Drawing::Size(159, 22);
			this->importButton->Text = L"Import segment";
			this->importButton->Click += gcnew System::EventHandler(this, &MainForm::importButton_Click);
			// 
			// closeCurrent_Button
			// 
			this->closeCurrent_Button->Enabled = false;
			this->closeCurrent_Button->Name = L"closeCurrent_Button";
			this->closeCurrent_Button->Size = System::Drawing::Size(159, 22);
			this->closeCurrent_Button->Text = L"Close";
			this->closeCurrent_Button->Click += gcnew System::EventHandler(this, &MainForm::closeCurrent_Button_Click);
			// 
			// exit_Button
			// 
			this->exit_Button->Name = L"exit_Button";
			this->exit_Button->Size = System::Drawing::Size(159, 22);
			this->exit_Button->Text = L"Exit";
			this->exit_Button->Click += gcnew System::EventHandler(this, &MainForm::exit_Button_Click);
			// 
			// abourToolStripMenuItem
			// 
			this->abourToolStripMenuItem->Enabled = false;
			this->abourToolStripMenuItem->Name = L"abourToolStripMenuItem";
			this->abourToolStripMenuItem->Size = System::Drawing::Size(52, 20);
			this->abourToolStripMenuItem->Text = L"About";
			// 
			// debug
			// 
			this->debug->Enabled = false;
			this->debug->Location = System::Drawing::Point(559, 331);
			this->debug->Name = L"debug";
			this->debug->Size = System::Drawing::Size(53, 88);
			this->debug->TabIndex = 2;
			this->debug->Text = L"";
			this->debug->Visible = false;
			// 
			// debug_title
			// 
			this->debug_title->AutoSize = true;
			this->debug_title->Location = System::Drawing::Point(556, 315);
			this->debug_title->Name = L"debug_title";
			this->debug_title->Size = System::Drawing::Size(39, 13);
			this->debug_title->TabIndex = 3;
			this->debug_title->Text = L"Debug";
			this->debug_title->Visible = false;
			// 
			// tableChooser
			// 
			this->tableChooser->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->tableChooser->Enabled = false;
			this->tableChooser->Location = System::Drawing::Point(55, 22);
			this->tableChooser->Name = L"tableChooser";
			this->tableChooser->Size = System::Drawing::Size(50, 21);
			this->tableChooser->TabIndex = 4;
			this->tableChooser->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::tableChooser_SelectedIndexChanged);
			// 
			// T_Title
			// 
			this->T_Title->AutoSize = true;
			this->T_Title->Location = System::Drawing::Point(6, 25);
			this->T_Title->Name = L"T_Title";
			this->T_Title->Size = System::Drawing::Size(43, 13);
			this->T_Title->TabIndex = 5;
			this->T_Title->Text = L"Palette:";
			// 
			// tableViewer
			// 
			this->tableViewer->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->tableViewer->Cursor = System::Windows::Forms::Cursors::Cross;
			this->tableViewer->Location = System::Drawing::Point(12, 129);
			this->tableViewer->Name = L"tableViewer";
			this->tableViewer->Size = System::Drawing::Size(320, 320);
			this->tableViewer->TabIndex = 6;
			this->tableViewer->TabStop = false;
			this->tableViewer->DoubleClick += gcnew System::EventHandler(this, &MainForm::tableViewer_DoubleClick);
			this->tableViewer->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::tableViewer_Click);
			this->tableViewer->MouseEnter += gcnew System::EventHandler(this, &MainForm::tableViewer_MouseEnter);
			this->tableViewer->MouseLeave += gcnew System::EventHandler(this, &MainForm::tableViewer_MouseLeave);
			this->tableViewer->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::tableViewer_MouseMove);
			// 
			// S_Title
			// 
			this->S_Title->AutoSize = true;
			this->S_Title->Location = System::Drawing::Point(159, 25);
			this->S_Title->Name = L"S_Title";
			this->S_Title->Size = System::Drawing::Size(52, 13);
			this->S_Title->TabIndex = 7;
			this->S_Title->Text = L"Segment:";
			// 
			// segmentChooser
			// 
			this->segmentChooser->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->segmentChooser->Enabled = false;
			this->segmentChooser->FormattingEnabled = true;
			this->segmentChooser->Location = System::Drawing::Point(217, 22);
			this->segmentChooser->Name = L"segmentChooser";
			this->segmentChooser->Size = System::Drawing::Size(50, 21);
			this->segmentChooser->TabIndex = 8;
			this->segmentChooser->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::segmentChooser_SelectedIndexChanged);
			// 
			// controlPanel
			// 
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
			// 
			// viewFilter
			// 
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
			// 
			// CiS_value
			// 
			this->CiS_value->AutoSize = true;
			this->CiS_value->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->CiS_value->Location = System::Drawing::Point(263, 56);
			this->CiS_value->Name = L"CiS_value";
			this->CiS_value->Size = System::Drawing::Size(14, 13);
			this->CiS_value->TabIndex = 14;
			this->CiS_value->Text = L"0";
			// 
			// CiS_title
			// 
			this->CiS_title->AutoSize = true;
			this->CiS_title->Location = System::Drawing::Point(159, 56);
			this->CiS_title->Name = L"CiS_title";
			this->CiS_title->Size = System::Drawing::Size(108, 13);
			this->CiS_title->TabIndex = 13;
			this->CiS_title->Text = L"Total segment colors:";
			// 
			// CiT_value
			// 
			this->CiT_value->AutoSize = true;
			this->CiT_value->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->CiT_value->Location = System::Drawing::Point(102, 56);
			this->CiT_value->Name = L"CiT_value";
			this->CiT_value->Size = System::Drawing::Size(14, 13);
			this->CiT_value->TabIndex = 12;
			this->CiT_value->Text = L"0";
			// 
			// CiT_title
			// 
			this->CiT_title->AutoSize = true;
			this->CiT_title->Location = System::Drawing::Point(6, 56);
			this->CiT_title->Name = L"CiT_title";
			this->CiT_title->Size = System::Drawing::Size(100, 13);
			this->CiT_title->TabIndex = 11;
			this->CiT_title->Text = L"Total palette colors:";
			// 
			// segmentSuffix
			// 
			this->segmentSuffix->AutoSize = true;
			this->segmentSuffix->Location = System::Drawing::Point(272, 25);
			this->segmentSuffix->Name = L"segmentSuffix";
			this->segmentSuffix->Size = System::Drawing::Size(25, 13);
			this->segmentSuffix->TabIndex = 10;
			this->segmentSuffix->Text = L"of 0";
			// 
			// tableSuffix
			// 
			this->tableSuffix->AutoSize = true;
			this->tableSuffix->Location = System::Drawing::Point(111, 25);
			this->tableSuffix->Name = L"tableSuffix";
			this->tableSuffix->Size = System::Drawing::Size(25, 13);
			this->tableSuffix->TabIndex = 9;
			this->tableSuffix->Text = L"of 0";
			// 
			// brushBox
			// 
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
			// 
			// B_CIndex
			// 
			this->B_CIndex->AutoSize = true;
			this->B_CIndex->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->B_CIndex->Location = System::Drawing::Point(10, 20);
			this->B_CIndex->Name = L"B_CIndex";
			this->B_CIndex->Size = System::Drawing::Size(65, 13);
			this->B_CIndex->TabIndex = 8;
			this->B_CIndex->Text = L"Color: 255";
			this->B_CIndex->Visible = false;
			// 
			// B_BValue
			// 
			this->B_BValue->AutoSize = true;
			this->B_BValue->ForeColor = System::Drawing::Color::Blue;
			this->B_BValue->Location = System::Drawing::Point(53, 137);
			this->B_BValue->Name = L"B_BValue";
			this->B_BValue->Size = System::Drawing::Size(13, 13);
			this->B_BValue->TabIndex = 7;
			this->B_BValue->Text = L"0";
			this->B_BValue->Visible = false;
			// 
			// B_GValue
			// 
			this->B_GValue->AutoSize = true;
			this->B_GValue->ForeColor = System::Drawing::Color::Lime;
			this->B_GValue->Location = System::Drawing::Point(53, 117);
			this->B_GValue->Name = L"B_GValue";
			this->B_GValue->Size = System::Drawing::Size(13, 13);
			this->B_GValue->TabIndex = 6;
			this->B_GValue->Text = L"0";
			this->B_GValue->Visible = false;
			// 
			// B_RValue
			// 
			this->B_RValue->AutoSize = true;
			this->B_RValue->ForeColor = System::Drawing::Color::Red;
			this->B_RValue->Location = System::Drawing::Point(53, 97);
			this->B_RValue->Name = L"B_RValue";
			this->B_RValue->Size = System::Drawing::Size(13, 13);
			this->B_RValue->TabIndex = 5;
			this->B_RValue->Text = L"0";
			this->B_RValue->Visible = false;
			// 
			// B_BTitle
			// 
			this->B_BTitle->AutoSize = true;
			this->B_BTitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->B_BTitle->Location = System::Drawing::Point(16, 137);
			this->B_BTitle->Name = L"B_BTitle";
			this->B_BTitle->Size = System::Drawing::Size(36, 13);
			this->B_BTitle->TabIndex = 4;
			this->B_BTitle->Text = L"Blue:";
			this->B_BTitle->Visible = false;
			// 
			// B_GTitle
			// 
			this->B_GTitle->AutoSize = true;
			this->B_GTitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->B_GTitle->Location = System::Drawing::Point(8, 117);
			this->B_GTitle->Name = L"B_GTitle";
			this->B_GTitle->Size = System::Drawing::Size(45, 13);
			this->B_GTitle->TabIndex = 3;
			this->B_GTitle->Text = L"Green:";
			this->B_GTitle->Visible = false;
			// 
			// B_RTitle
			// 
			this->B_RTitle->AutoSize = true;
			this->B_RTitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->B_RTitle->Location = System::Drawing::Point(18, 97);
			this->B_RTitle->Name = L"B_RTitle";
			this->B_RTitle->Size = System::Drawing::Size(34, 13);
			this->B_RTitle->TabIndex = 2;
			this->B_RTitle->Text = L"Red:";
			this->B_RTitle->Visible = false;
			// 
			// hexValue
			// 
			this->hexValue->AutoSize = true;
			this->hexValue->Location = System::Drawing::Point(18, 73);
			this->hexValue->Name = L"hexValue";
			this->hexValue->Size = System::Drawing::Size(50, 13);
			this->hexValue->TabIndex = 1;
			this->hexValue->Text = L"#000000";
			this->hexValue->Visible = false;
			// 
			// brushColorView
			// 
			this->brushColorView->Location = System::Drawing::Point(19, 36);
			this->brushColorView->Name = L"brushColorView";
			this->brushColorView->Size = System::Drawing::Size(49, 34);
			this->brushColorView->TabIndex = 0;
			this->brushColorView->TabStop = false;
			// 
			// importFileDialog
			// 
			this->importFileDialog->FileName = L"openFileDialog1";
			// 
			// genPlanet
			// 
			this->genPlanet->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->genPlanet->Controls->Add(this->xltPresetLabel);
			this->genPlanet->Controls->Add(this->xltPresetBox);
			this->genPlanet->Controls->Add(this->presetLabel);
			this->genPlanet->Controls->Add(this->presetBox);
			this->genPlanet->Controls->Add(this->algoLabel);
			this->genPlanet->Controls->Add(this->seedLabel);
			this->genPlanet->Controls->Add(this->seedInput);
			this->genPlanet->Controls->Add(this->algoChooser);
			this->genPlanet->Controls->Add(this->load_xltButton);
			this->genPlanet->Controls->Add(this->genButton);
			this->genPlanet->Controls->Add(this->genLabel4);
			this->genPlanet->Controls->Add(this->gpElev);
			this->genPlanet->Controls->Add(this->genLabel3);
			this->genPlanet->Controls->Add(this->gpBlem);
			this->genPlanet->Controls->Add(this->genLabel2);
			this->genPlanet->Controls->Add(this->gpDepth);
			this->genPlanet->Controls->Add(this->genLabel1);
			this->genPlanet->Controls->Add(this->gpFaults);
			this->genPlanet->Enabled = false;
			this->genPlanet->Location = System::Drawing::Point(339, 28);
			this->genPlanet->Name = L"genPlanet";
			this->genPlanet->Size = System::Drawing::Size(273, 212);
			this->genPlanet->TabIndex = 11;
			this->genPlanet->TabStop = false;
			this->genPlanet->Text = L"Generate planet side";
			// 
			// xltPresetLabel
			// 
			this->xltPresetLabel->AutoSize = true;
			this->xltPresetLabel->Location = System::Drawing::Point(25, 158);
			this->xltPresetLabel->Name = L"xltPresetLabel";
			this->xltPresetLabel->Size = System::Drawing::Size(51, 13);
			this->xltPresetLabel->TabIndex = 17;
			this->xltPresetLabel->Text = L"Xlt preset";
			// 
			// xltPresetBox
			// 
			this->xltPresetBox->FormattingEnabled = true;
			this->xltPresetBox->Location = System::Drawing::Point(83, 155);
			this->xltPresetBox->Name = L"xltPresetBox";
			this->xltPresetBox->Size = System::Drawing::Size(142, 21);
			this->xltPresetBox->TabIndex = 16;
			this->xltPresetBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::xltPresetBox_SelectedIndexChanged);
			// 
			// presetLabel
			// 
			this->presetLabel->AutoSize = true;
			this->presetLabel->Location = System::Drawing::Point(8, 131);
			this->presetLabel->Name = L"presetLabel";
			this->presetLabel->Size = System::Drawing::Size(69, 13);
			this->presetLabel->TabIndex = 15;
			this->presetLabel->Text = L"Planet preset";
			// 
			// presetBox
			// 
			this->presetBox->FormattingEnabled = true;
			this->presetBox->Location = System::Drawing::Point(83, 128);
			this->presetBox->Name = L"presetBox";
			this->presetBox->Size = System::Drawing::Size(142, 21);
			this->presetBox->TabIndex = 7;
			this->presetBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::presetBox_SelectedIndexChanged);
			// 
			// algoLabel
			// 
			this->algoLabel->AutoSize = true;
			this->algoLabel->Location = System::Drawing::Point(129, 55);
			this->algoLabel->Name = L"algoLabel";
			this->algoLabel->Size = System::Drawing::Size(50, 13);
			this->algoLabel->TabIndex = 13;
			this->algoLabel->Text = L"Algorithm";
			// 
			// seedLabel
			// 
			this->seedLabel->AutoSize = true;
			this->seedLabel->Location = System::Drawing::Point(129, 27);
			this->seedLabel->Name = L"seedLabel";
			this->seedLabel->Size = System::Drawing::Size(32, 13);
			this->seedLabel->TabIndex = 12;
			this->seedLabel->Text = L"Seed";
			// 
			// seedInput
			// 
			this->seedInput->Location = System::Drawing::Point(167, 24);
			this->seedInput->MaxLength = 10;
			this->seedInput->Name = L"seedInput";
			this->seedInput->Size = System::Drawing::Size(100, 20);
			this->seedInput->TabIndex = 4;
			this->seedInput->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::seedInput_KeyPress);
			// 
			// algoChooser
			// 
			this->algoChooser->FormattingEnabled = true;
			this->algoChooser->Location = System::Drawing::Point(188, 52);
			this->algoChooser->Name = L"algoChooser";
			this->algoChooser->Size = System::Drawing::Size(79, 21);
			this->algoChooser->TabIndex = 5;
			// 
			// load_xltButton
			// 
			this->load_xltButton->Location = System::Drawing::Point(132, 99);
			this->load_xltButton->Name = L"load_xltButton";
			this->load_xltButton->Size = System::Drawing::Size(135, 23);
			this->load_xltButton->TabIndex = 6;
			this->load_xltButton->Text = L"Load translate table";
			this->load_xltButton->UseVisualStyleBackColor = true;
			this->load_xltButton->Click += gcnew System::EventHandler(this, &MainForm::load_xltButton_Click);
			// 
			// genButton
			// 
			this->genButton->Enabled = false;
			this->genButton->Location = System::Drawing::Point(95, 182);
			this->genButton->Name = L"genButton";
			this->genButton->Size = System::Drawing::Size(84, 23);
			this->genButton->TabIndex = 8;
			this->genButton->Text = L"Generate";
			this->genButton->UseVisualStyleBackColor = true;
			this->genButton->Click += gcnew System::EventHandler(this, &MainForm::genButton_Click);
			// 
			// genLabel4
			// 
			this->genLabel4->AutoSize = true;
			this->genLabel4->Location = System::Drawing::Point(6, 104);
			this->genLabel4->Name = L"genLabel4";
			this->genLabel4->Size = System::Drawing::Size(54, 13);
			this->genLabel4->TabIndex = 7;
			this->genLabel4->Text = L"Base elev";
			// 
			// gpElev
			// 
			this->gpElev->Location = System::Drawing::Point(66, 101);
			this->gpElev->MaxLength = 3;
			this->gpElev->Name = L"gpElev";
			this->gpElev->Size = System::Drawing::Size(34, 20);
			this->gpElev->TabIndex = 3;
			this->gpElev->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::gpInput_KeyPress);
			// 
			// genLabel3
			// 
			this->genLabel3->AutoSize = true;
			this->genLabel3->Location = System::Drawing::Point(6, 78);
			this->genLabel3->Name = L"genLabel3";
			this->genLabel3->Size = System::Drawing::Size(54, 13);
			this->genLabel3->TabIndex = 5;
			this->genLabel3->Text = L"Blemishes";
			// 
			// gpBlem
			// 
			this->gpBlem->Location = System::Drawing::Point(66, 75);
			this->gpBlem->MaxLength = 3;
			this->gpBlem->Name = L"gpBlem";
			this->gpBlem->Size = System::Drawing::Size(34, 20);
			this->gpBlem->TabIndex = 2;
			this->gpBlem->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::gpInput_KeyPress);
			// 
			// genLabel2
			// 
			this->genLabel2->AutoSize = true;
			this->genLabel2->Location = System::Drawing::Point(19, 52);
			this->genLabel2->Name = L"genLabel2";
			this->genLabel2->Size = System::Drawing::Size(41, 13);
			this->genLabel2->TabIndex = 3;
			this->genLabel2->Text = L"Depths";
			// 
			// gpDepth
			// 
			this->gpDepth->Location = System::Drawing::Point(66, 49);
			this->gpDepth->MaxLength = 3;
			this->gpDepth->Name = L"gpDepth";
			this->gpDepth->Size = System::Drawing::Size(34, 20);
			this->gpDepth->TabIndex = 1;
			this->gpDepth->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::gpInput_KeyPress);
			// 
			// genLabel1
			// 
			this->genLabel1->AutoSize = true;
			this->genLabel1->Location = System::Drawing::Point(25, 27);
			this->genLabel1->Name = L"genLabel1";
			this->genLabel1->Size = System::Drawing::Size(35, 13);
			this->genLabel1->TabIndex = 1;
			this->genLabel1->Text = L"Faults";
			// 
			// gpFaults
			// 
			this->gpFaults->Location = System::Drawing::Point(66, 24);
			this->gpFaults->MaxLength = 3;
			this->gpFaults->Name = L"gpFaults";
			this->gpFaults->Size = System::Drawing::Size(34, 20);
			this->gpFaults->TabIndex = 0;
			this->gpFaults->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::gpInput_KeyPress);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->ClientSize = System::Drawing::Size(624, 461);
			this->Controls->Add(this->genPlanet);
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
			this->Text = L"Ur-Quan Masters Palette Editor v0.1.7";
			this->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::MainForm_MouseClick);
			this->menuStrip->ResumeLayout(false);
			this->menuStrip->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tableViewer))->EndInit();
			this->controlPanel->ResumeLayout(false);
			this->controlPanel->PerformLayout();
			this->brushBox->ResumeLayout(false);
			this->brushBox->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->brushColorView))->EndInit();
			this->genPlanet->ResumeLayout(false);
			this->genPlanet->PerformLayout();
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
	private: System::Void saveToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void tableViewer_Click(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void MainForm_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void saveAsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void tableViewer_DoubleClick(System::Object^ sender, System::EventArgs^ e);
	private: System::Void genButton_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void load_xltButton_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void presetBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void gpInput_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e);
	private: System::Void xltPresetBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void seedInput_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e);
};
}
