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

namespace UQMPalEd {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ PlanetSide
	/// </summary>
	public ref class PlanetSide : public System::Windows::Forms::Form
	{
	public:
		PlanetSide(void);
		PlanetSide(System::Drawing::Bitmap^ bmp);

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~PlanetSide()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ planetSurface;
	protected:

	protected:
	private: System::Windows::Forms::Button^ ok_button;

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(PlanetSide::typeid));
			this->planetSurface = (gcnew System::Windows::Forms::PictureBox());
			this->ok_button = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->planetSurface))->BeginInit();
			this->SuspendLayout();
			// 
			// planetSurface
			// 
			this->planetSurface->BackColor = System::Drawing::SystemColors::Control;
			this->planetSurface->Location = System::Drawing::Point(13, 13);
			this->planetSurface->Name = L"planetSurface";
			this->planetSurface->Size = System::Drawing::Size(840, 268);
			this->planetSurface->TabIndex = 0;
			this->planetSurface->TabStop = false;
			// 
			// ok_button
			// 
			this->ok_button->Location = System::Drawing::Point(397, 287);
			this->ok_button->Name = L"ok_button";
			this->ok_button->Size = System::Drawing::Size(75, 23);
			this->ok_button->TabIndex = 1;
			this->ok_button->Text = L"OK";
			this->ok_button->UseVisualStyleBackColor = true;
			this->ok_button->Click += gcnew System::EventHandler(this, &PlanetSide::ok_button_Click);
			// 
			// PlanetSide
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->ClientSize = System::Drawing::Size(866, 318);
			this->ControlBox = false;
			this->Controls->Add(this->ok_button);
			this->Controls->Add(this->planetSurface);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximumSize = System::Drawing::Size(882, 357);
			this->MinimumSize = System::Drawing::Size(882, 357);
			this->Name = L"PlanetSide";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Planet Side";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->planetSurface))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void ok_button_Click(System::Object^ sender, System::EventArgs^ e);
	};
}
