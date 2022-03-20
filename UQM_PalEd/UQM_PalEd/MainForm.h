// Ur-Quan Masters Palette Editor v0.0.5

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


#include "File_Handler.h"
#include "resource.h"

#pragma once

#define TITLE "Ur-Quan Masters Palette Editor v0.0.5"

using namespace Handler;

namespace UQMPalEd {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void);
		File_Handler^ h;
		int displayed;
	private: System::Windows::Forms::Label^ S_Title;
	private: System::Windows::Forms::ComboBox^ segmentChooser;
	private: System::Windows::Forms::GroupBox^ controlPanel;
	public:

	public:


	private: System::Windows::Forms::Label^ tableSuffix;
	private: System::Windows::Forms::Label^ segmentSuffix;
	private: System::Windows::Forms::Label^ CiT_value;



	private: System::Windows::Forms::Label^ CiT_title;
	private: System::Windows::Forms::Label^ CiS_value;


	private: System::Windows::Forms::Label^ CiS_title;

		   Bitmap^ background;
		void invokeMessageBox(String^ s, bool err);
		void fillTableView(array<Color>^ table);
		void fillDropDownSegs(int numSegs);
		void fillDropDownTables(int numTables);
		void clearTableView(void);
		void closeCurrent(void);
		Image^ getImageFromRes(long resource_ID);
	private: System::Windows::Forms::RichTextBox^ debug;
	private: System::Windows::Forms::Label^ debug_title;



	private: System::Windows::Forms::ComboBox^ tableChooser;

	private: System::Windows::Forms::Label^ T_Title;
	private: System::Windows::Forms::ToolStripMenuItem^ exit_Button;


	private: System::Windows::Forms::PictureBox^ tableViewer;

		
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
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog;
	private: System::Windows::Forms::MenuStrip^ menuStrip;
	protected:


	private: System::Windows::Forms::ToolStripMenuItem^ fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ newToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ openFile_Button;

	private: System::Windows::Forms::ToolStripMenuItem^ saveAsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ saveToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ exitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ abourToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ pSToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ closeCurrent_Button;


	protected:

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
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
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pSToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
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
			this->CiS_value = (gcnew System::Windows::Forms::Label());
			this->CiS_title = (gcnew System::Windows::Forms::Label());
			this->CiT_value = (gcnew System::Windows::Forms::Label());
			this->CiT_title = (gcnew System::Windows::Forms::Label());
			this->segmentSuffix = (gcnew System::Windows::Forms::Label());
			this->tableSuffix = (gcnew System::Windows::Forms::Label());
			this->menuStrip->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tableViewer))->BeginInit();
			this->controlPanel->SuspendLayout();
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
					this->openFile_Button, this->saveAsToolStripMenuItem, this->saveToolStripMenuItem, this->exitToolStripMenuItem, this->closeCurrent_Button,
					this->exit_Button
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// newToolStripMenuItem
			// 
			this->newToolStripMenuItem->Enabled = false;
			this->newToolStripMenuItem->Name = L"newToolStripMenuItem";
			this->newToolStripMenuItem->Size = System::Drawing::Size(139, 22);
			this->newToolStripMenuItem->Text = L"New";
			// 
			// openFile_Button
			// 
			this->openFile_Button->Name = L"openFile_Button";
			this->openFile_Button->Size = System::Drawing::Size(139, 22);
			this->openFile_Button->Text = L"Open";
			this->openFile_Button->Click += gcnew System::EventHandler(this, &MainForm::openFile_Button_Click);
			// 
			// saveAsToolStripMenuItem
			// 
			this->saveAsToolStripMenuItem->Enabled = false;
			this->saveAsToolStripMenuItem->Name = L"saveAsToolStripMenuItem";
			this->saveAsToolStripMenuItem->Size = System::Drawing::Size(139, 22);
			this->saveAsToolStripMenuItem->Text = L"Save As";
			// 
			// saveToolStripMenuItem
			// 
			this->saveToolStripMenuItem->Enabled = false;
			this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
			this->saveToolStripMenuItem->Size = System::Drawing::Size(139, 22);
			this->saveToolStripMenuItem->Text = L"Save";
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->pSToolStripMenuItem });
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(139, 22);
			this->exitToolStripMenuItem->Text = L"Import from";
			// 
			// pSToolStripMenuItem
			// 
			this->pSToolStripMenuItem->Enabled = false;
			this->pSToolStripMenuItem->Name = L"pSToolStripMenuItem";
			this->pSToolStripMenuItem->Size = System::Drawing::Size(87, 22);
			this->pSToolStripMenuItem->Text = L"PS";
			// 
			// closeCurrent_Button
			// 
			this->closeCurrent_Button->Enabled = false;
			this->closeCurrent_Button->Name = L"closeCurrent_Button";
			this->closeCurrent_Button->Size = System::Drawing::Size(139, 22);
			this->closeCurrent_Button->Text = L"Close";
			this->closeCurrent_Button->Click += gcnew System::EventHandler(this, &MainForm::closeCurrent_Button_Click);
			// 
			// exit_Button
			// 
			this->exit_Button->Name = L"exit_Button";
			this->exit_Button->Size = System::Drawing::Size(139, 22);
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
			this->debug->Location = System::Drawing::Point(559, 234);
			this->debug->Name = L"debug";
			this->debug->Size = System::Drawing::Size(53, 88);
			this->debug->TabIndex = 2;
			this->debug->Text = L"";
			this->debug->Visible = false;
			// 
			// debug_title
			// 
			this->debug_title->AutoSize = true;
			this->debug_title->Location = System::Drawing::Point(556, 218);
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
			this->tableChooser->Location = System::Drawing::Point(49, 22);
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
			this->T_Title->Size = System::Drawing::Size(37, 13);
			this->T_Title->TabIndex = 5;
			this->T_Title->Text = L"Table:";
			// 
			// tableViewer
			// 
			this->tableViewer->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->tableViewer->Location = System::Drawing::Point(12, 109);
			this->tableViewer->Name = L"tableViewer";
			this->tableViewer->Size = System::Drawing::Size(320, 320);
			this->tableViewer->TabIndex = 6;
			this->tableViewer->TabStop = false;
			// 
			// S_Title
			// 
			this->S_Title->AutoSize = true;
			this->S_Title->Location = System::Drawing::Point(171, 25);
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
			this->segmentChooser->Location = System::Drawing::Point(229, 22);
			this->segmentChooser->Name = L"segmentChooser";
			this->segmentChooser->Size = System::Drawing::Size(50, 21);
			this->segmentChooser->TabIndex = 8;
			this->segmentChooser->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::segmentChooser_SelectedIndexChanged);
			// 
			// controlPanel
			// 
			this->controlPanel->BackColor = System::Drawing::SystemColors::InactiveCaption;
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
			this->controlPanel->Size = System::Drawing::Size(340, 75);
			this->controlPanel->TabIndex = 9;
			this->controlPanel->TabStop = false;
			this->controlPanel->Text = L"Control Panel";
			// 
			// CiS_value
			// 
			this->CiS_value->AutoSize = true;
			this->CiS_value->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->CiS_value->Location = System::Drawing::Point(295, 56);
			this->CiS_value->Name = L"CiS_value";
			this->CiS_value->Size = System::Drawing::Size(14, 13);
			this->CiS_value->TabIndex = 14;
			this->CiS_value->Text = L"0";
			// 
			// CiS_title
			// 
			this->CiS_title->AutoSize = true;
			this->CiS_title->Location = System::Drawing::Point(171, 56);
			this->CiS_title->Name = L"CiS_title";
			this->CiS_title->Size = System::Drawing::Size(129, 13);
			this->CiS_title->TabIndex = 13;
			this->CiS_title->Text = L"Colors in current segment:";
			// 
			// CiT_value
			// 
			this->CiT_value->AutoSize = true;
			this->CiT_value->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->CiT_value->Location = System::Drawing::Point(116, 56);
			this->CiT_value->Name = L"CiT_value";
			this->CiT_value->Size = System::Drawing::Size(14, 13);
			this->CiT_value->TabIndex = 12;
			this->CiT_value->Text = L"0";
			// 
			// CiT_title
			// 
			this->CiT_title->AutoSize = true;
			this->CiT_title->Location = System::Drawing::Point(9, 56);
			this->CiT_title->Name = L"CiT_title";
			this->CiT_title->Size = System::Drawing::Size(112, 13);
			this->CiT_title->TabIndex = 11;
			this->CiT_title->Text = L"Colors in current table:";
			// 
			// segmentSuffix
			// 
			this->segmentSuffix->AutoSize = true;
			this->segmentSuffix->Location = System::Drawing::Point(285, 25);
			this->segmentSuffix->Name = L"segmentSuffix";
			this->segmentSuffix->Size = System::Drawing::Size(25, 13);
			this->segmentSuffix->TabIndex = 10;
			this->segmentSuffix->Text = L"of 0";
			// 
			// tableSuffix
			// 
			this->tableSuffix->AutoSize = true;
			this->tableSuffix->Location = System::Drawing::Point(105, 25);
			this->tableSuffix->Name = L"tableSuffix";
			this->tableSuffix->Size = System::Drawing::Size(25, 13);
			this->tableSuffix->TabIndex = 9;
			this->tableSuffix->Text = L"of 0";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->ClientSize = System::Drawing::Size(624, 441);
			this->Controls->Add(this->controlPanel);
			this->Controls->Add(this->tableViewer);
			this->Controls->Add(this->debug_title);
			this->Controls->Add(this->debug);
			this->Controls->Add(this->menuStrip);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Ur-Quan Masters Palette Editor v0.0.5";
			this->menuStrip->ResumeLayout(false);
			this->menuStrip->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tableViewer))->EndInit();
			this->controlPanel->ResumeLayout(false);
			this->controlPanel->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void openFile_Button_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void closeCurrent_Button_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void tableChooser_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void exit_Button_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void segmentChooser_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
};
}
