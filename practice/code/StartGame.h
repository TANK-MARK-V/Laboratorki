#pragma once

#include "TheZondbie.h"

namespace MarkflightsUI {
	using namespace System;
	using namespace System::IO;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для StartGame
	/// </summary>
	public ref class StartGame : public System::Windows::Forms::Form
	{
	public:
		StartGame(void)
		{
			InitializeComponent();
			try {
				if (File::Exists("game_data/score.txt")) {
					StreamReader^ reader = gcnew StreamReader("game_data/score.txt");
					String^ line = reader->ReadLine();
					reader->Close();
					this->best_time_label->Text = "Лучшее время: " + line;
					this->best_time_label->Visible = 1;
				}

			}
			catch (...) {}
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~StartGame()
		{
			if (components)
			{
				delete components;
			}
			// Показываем главную форму
			for each (Form ^ form in Application::OpenForms) {
				if (form->GetType()->Name == "FlightMenu") {
					form->Show();
					break;
				}
			}
		}
	private: System::Windows::Forms::Label^ lore_label;
	private: System::Windows::Forms::Button^ start_button;
	private: System::Windows::Forms::Label^ goal_label;
	private: System::Windows::Forms::Label^ best_time_label;
	private: System::Windows::Forms::Button^ exit_button;
	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(StartGame::typeid));
			this->lore_label = (gcnew System::Windows::Forms::Label());
			this->start_button = (gcnew System::Windows::Forms::Button());
			this->goal_label = (gcnew System::Windows::Forms::Label());
			this->best_time_label = (gcnew System::Windows::Forms::Label());
			this->exit_button = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// lore_label
			// 
			this->lore_label->AutoSize = true;
			this->lore_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->lore_label->Location = System::Drawing::Point(12, 9);
			this->lore_label->Name = L"lore_label";
			this->lore_label->Size = System::Drawing::Size(711, 160);
			this->lore_label->TabIndex = 0;
			this->lore_label->Text = resources->GetString(L"lore_label.Text");
			// 
			// start_button
			// 
			this->start_button->Location = System::Drawing::Point(16, 192);
			this->start_button->Name = L"start_button";
			this->start_button->Size = System::Drawing::Size(183, 46);
			this->start_button->TabIndex = 1;
			this->start_button->Text = L"Начать защиту";
			this->start_button->UseVisualStyleBackColor = true;
			this->start_button->Click += gcnew System::EventHandler(this, &StartGame::start_button_Click);
			// 
			// goal_label
			// 
			this->goal_label->AutoSize = true;
			this->goal_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->goal_label->Location = System::Drawing::Point(12, 169);
			this->goal_label->Name = L"goal_label";
			this->goal_label->Size = System::Drawing::Size(386, 20);
			this->goal_label->TabIndex = 2;
			this->goal_label->Text = L"Постарайтесь прожить как можно дольше...";
			// 
			// best_time_label
			// 
			this->best_time_label->AutoSize = true;
			this->best_time_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->best_time_label->Location = System::Drawing::Point(446, 169);
			this->best_time_label->Name = L"best_time_label";
			this->best_time_label->Size = System::Drawing::Size(127, 20);
			this->best_time_label->TabIndex = 3;
			this->best_time_label->Text = L"Лучшее время: ";
			this->best_time_label->Visible = false;
			// 
			// exit_button
			// 
			this->exit_button->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->exit_button->Location = System::Drawing::Point(16, 245);
			this->exit_button->Name = L"exit_button";
			this->exit_button->Size = System::Drawing::Size(183, 46);
			this->exit_button->TabIndex = 4;
			this->exit_button->Text = L"Вернуться в меню";
			this->exit_button->UseVisualStyleBackColor = false;
			this->exit_button->Click += gcnew System::EventHandler(this, &StartGame::exit_button_Click);
			// 
			// StartGame
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->ClientSize = System::Drawing::Size(729, 299);
			this->Controls->Add(this->exit_button);
			this->Controls->Add(this->best_time_label);
			this->Controls->Add(this->goal_label);
			this->Controls->Add(this->start_button);
			this->Controls->Add(this->lore_label);
			this->MaximizeBox = false;
			this->Name = L"StartGame";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"The Zondbie";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void start_button_Click(System::Object^ sender, System::EventArgs^ e) {
	TheZondbie^ p = gcnew TheZondbie();
	p->Show();
	this->Hide();
}
private: System::Void exit_button_Click(System::Object^ sender, System::EventArgs^ e) {
	for each (Form ^ form in Application::OpenForms) {
		if (form->GetType()->Name == "FlightMenu") {
			form->Show();
			break;
		}
	}
	this->Close();
}
};
}
