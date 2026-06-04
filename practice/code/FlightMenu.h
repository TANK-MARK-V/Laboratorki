#pragma once

#include "AdminCheck.h"
#include "UserSite.h"
#include "StartGame.h"


namespace MarkflightsUI {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для FlightMenu
	/// </summary>
	public ref class FlightMenu : public System::Windows::Forms::Form
	{

	public:
		FlightMenu(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~FlightMenu()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ name_label;
	private: System::Windows::Forms::Label^ news_label;
	private: System::Windows::Forms::Label^ mode_label;
	private: System::Windows::Forms::Button^ as_admin_button;
	private: System::Windows::Forms::Button^ as_player_button;
	private: System::Windows::Forms::Button^ as_user_button;
	private: System::Windows::Forms::PictureBox^ pictureBox1;

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(FlightMenu::typeid));
			this->name_label = (gcnew System::Windows::Forms::Label());
			this->news_label = (gcnew System::Windows::Forms::Label());
			this->mode_label = (gcnew System::Windows::Forms::Label());
			this->as_admin_button = (gcnew System::Windows::Forms::Button());
			this->as_player_button = (gcnew System::Windows::Forms::Button());
			this->as_user_button = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// name_label
			// 
			this->name_label->AutoSize = true;
			this->name_label->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->name_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->name_label->Location = System::Drawing::Point(155, 9);
			this->name_label->Margin = System::Windows::Forms::Padding(0);
			this->name_label->Name = L"name_label";
			this->name_label->Size = System::Drawing::Size(185, 26);
			this->name_label->TabIndex = 0;
			this->name_label->Text = L"MARK FLIGHTS";
			// 
			// news_label
			// 
			this->news_label->AutoSize = true;
			this->news_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->news_label->Location = System::Drawing::Point(12, 48);
			this->news_label->Name = L"news_label";
			this->news_label->Size = System::Drawing::Size(183, 20);
			this->news_label->TabIndex = 1;
			this->news_label->Text = L"Последние новости:";
			// 
			// mode_label
			// 
			this->mode_label->AutoSize = true;
			this->mode_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->mode_label->Location = System::Drawing::Point(259, 48);
			this->mode_label->Name = L"mode_label";
			this->mode_label->Size = System::Drawing::Size(204, 20);
			this->mode_label->TabIndex = 2;
			this->mode_label->Text = L"Выбор режима работы:";
			// 
			// as_admin_button
			// 
			this->as_admin_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->as_admin_button->Location = System::Drawing::Point(263, 84);
			this->as_admin_button->Name = L"as_admin_button";
			this->as_admin_button->Size = System::Drawing::Size(200, 35);
			this->as_admin_button->TabIndex = 3;
			this->as_admin_button->Text = L"Администратор";
			this->as_admin_button->UseVisualStyleBackColor = true;
			this->as_admin_button->Click += gcnew System::EventHandler(this, &FlightMenu::as_admin_button_Click);
			// 
			// as_player_button
			// 
			this->as_player_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->as_player_button->Location = System::Drawing::Point(263, 166);
			this->as_player_button->Name = L"as_player_button";
			this->as_player_button->Size = System::Drawing::Size(200, 35);
			this->as_player_button->TabIndex = 5;
			this->as_player_button->Text = L"Запустить игру";
			this->as_player_button->UseVisualStyleBackColor = true;
			this->as_player_button->Click += gcnew System::EventHandler(this, &FlightMenu::as_player_button_Click);
			// 
			// as_user_button
			// 
			this->as_user_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->as_user_button->Location = System::Drawing::Point(264, 125);
			this->as_user_button->Name = L"as_user_button";
			this->as_user_button->Size = System::Drawing::Size(200, 35);
			this->as_user_button->TabIndex = 7;
			this->as_user_button->Text = L"Пользователь";
			this->as_user_button->UseVisualStyleBackColor = true;
			this->as_user_button->Click += gcnew System::EventHandler(this, &FlightMenu::as_user_button_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(16, 84);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(179, 117);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 8;
			this->pictureBox1->TabStop = false;
			// 
			// FlightMenu
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->ClientSize = System::Drawing::Size(476, 218);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->as_user_button);
			this->Controls->Add(this->as_player_button);
			this->Controls->Add(this->as_admin_button);
			this->Controls->Add(this->mode_label);
			this->Controls->Add(this->news_label);
			this->Controls->Add(this->name_label);
			this->MaximizeBox = false;
			this->MinimumSize = System::Drawing::Size(492, 257);
			this->Name = L"FlightMenu";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Mark_flights";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void as_admin_button_Click(System::Object^ sender, System::EventArgs^ e) {
		AdminCheck^ p = gcnew AdminCheck();
		p->ShowDialog();
	}
	private: System::Void as_user_button_Click(System::Object^ sender, System::EventArgs^ e) {
		UserSite^ p = gcnew UserSite();
		p->Show();
		this->Hide();
	}
	private: System::Void as_player_button_Click(System::Object^ sender, System::EventArgs^ e) {
		StartGame^ p = gcnew StartGame();
		p->Show();
		this->Hide();
	}
};
}
