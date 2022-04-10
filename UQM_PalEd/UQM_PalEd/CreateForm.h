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

#include "MainForm.h"

namespace UQMPalEd {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ CreateForm
	/// </summary>
	public ref class CreateForm : public System::Windows::Forms::Form
	{
	private:
		MainForm^ father;
	public:
		CreateForm(void);
		CreateForm(MainForm^ father);


	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~CreateForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ OK_Button;
	protected:
	private: System::Windows::Forms::Button^ Cancel_Button;
	private: System::Windows::Forms::TextBox^ numPalettes;
	private: System::Windows::Forms::Label^ numPalettesLabel;
	private: System::Windows::Forms::TextBox^ palLengths;
	private: System::Windows::Forms::Label^ palLengthsLabel;


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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(CreateForm::typeid));
			this->OK_Button = (gcnew System::Windows::Forms::Button());
			this->Cancel_Button = (gcnew System::Windows::Forms::Button());
			this->numPalettes = (gcnew System::Windows::Forms::TextBox());
			this->numPalettesLabel = (gcnew System::Windows::Forms::Label());
			this->palLengths = (gcnew System::Windows::Forms::TextBox());
			this->palLengthsLabel = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// OK_Button
			// 
			this->OK_Button->Location = System::Drawing::Point(90, 95);
			this->OK_Button->Name = L"OK_Button";
			this->OK_Button->Size = System::Drawing::Size(75, 23);
			this->OK_Button->TabIndex = 0;
			this->OK_Button->Text = L"OK";
			this->OK_Button->UseVisualStyleBackColor = true;
			this->OK_Button->Click += gcnew System::EventHandler(this, &CreateForm::OK_Button_Click);
			// 
			// Cancel_Button
			// 
			this->Cancel_Button->Location = System::Drawing::Point(190, 95);
			this->Cancel_Button->Name = L"Cancel_Button";
			this->Cancel_Button->Size = System::Drawing::Size(75, 23);
			this->Cancel_Button->TabIndex = 1;
			this->Cancel_Button->Text = L"Cancel";
			this->Cancel_Button->UseVisualStyleBackColor = true;
			this->Cancel_Button->Click += gcnew System::EventHandler(this, &CreateForm::Cancel_Button_Click);
			// 
			// numPalettes
			// 
			this->numPalettes->Location = System::Drawing::Point(75, 51);
			this->numPalettes->MaxLength = 3;
			this->numPalettes->Name = L"numPalettes";
			this->numPalettes->Size = System::Drawing::Size(30, 20);
			this->numPalettes->TabIndex = 2;
			this->numPalettes->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &CreateForm::numPalettes_KeyPress);
			// 
			// numPalettesLabel
			// 
			this->numPalettesLabel->AutoSize = true;
			this->numPalettesLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->numPalettesLabel->Location = System::Drawing::Point(12, 32);
			this->numPalettesLabel->Name = L"numPalettesLabel";
			this->numPalettesLabel->Size = System::Drawing::Size(151, 16);
			this->numPalettesLabel->TabIndex = 3;
			this->numPalettesLabel->Text = L"Enter number of palettes";
			// 
			// palLengths
			// 
			this->palLengths->Location = System::Drawing::Point(218, 51);
			this->palLengths->Name = L"palLengths";
			this->palLengths->Size = System::Drawing::Size(125, 20);
			this->palLengths->TabIndex = 4;
			this->palLengths->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &CreateForm::palLengths_KeyPress);
			// 
			// palLengthsLabel
			// 
			this->palLengthsLabel->AutoSize = true;
			this->palLengthsLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->palLengthsLabel->Location = System::Drawing::Point(215, 32);
			this->palLengthsLabel->Name = L"palLengthsLabel";
			this->palLengthsLabel->Size = System::Drawing::Size(128, 16);
			this->palLengthsLabel->TabIndex = 5;
			this->palLengthsLabel->Text = L"Enter palette lengths";
			// 
			// CreateForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->ClientSize = System::Drawing::Size(355, 135);
			this->ControlBox = false;
			this->Controls->Add(this->palLengthsLabel);
			this->Controls->Add(this->palLengths);
			this->Controls->Add(this->numPalettesLabel);
			this->Controls->Add(this->numPalettes);
			this->Controls->Add(this->Cancel_Button);
			this->Controls->Add(this->OK_Button);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximumSize = System::Drawing::Size(371, 174);
			this->MinimumSize = System::Drawing::Size(371, 174);
			this->Name = L"CreateForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"New Color Table";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Cancel_Button_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void OK_Button_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void numPalettes_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e);
	private: System::Void palLengths_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e);
};
}
