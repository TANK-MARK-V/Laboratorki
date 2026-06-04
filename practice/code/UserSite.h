#pragma once

#include "AdminSite.h"

namespace MarkflightsUI {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для UserSite
	/// </summary>
	//public ref class UserSite : public System::Windows::Forms::Form
	public ref class UserSite : public AdminSite  // Наследуем от AdminSite
	{
	public:
		UserSite(void)
		{
			// Выполняется код конструктора AdminSite, который автоматически заполняет таблицу
			InitializeComponent();
		} 
	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~UserSite()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridView^ data_base;
	private: System::Windows::Forms::Label^ mode_label;
	private: System::Windows::Forms::Button^ update_button;
	private: System::Windows::Forms::Button^ set_filters_button;
	private: System::Windows::Forms::Button^ exit_button;
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
			this->data_base = (gcnew System::Windows::Forms::DataGridView());
			this->mode_label = (gcnew System::Windows::Forms::Label());
			this->update_button = (gcnew System::Windows::Forms::Button());
			this->set_filters_button = (gcnew System::Windows::Forms::Button());
			this->exit_button = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->data_base))->BeginInit();
			this->SuspendLayout();
			// 
			// data_base
			// 
			this->data_base->AllowUserToAddRows = false;
			this->data_base->AllowUserToDeleteRows = false;
			this->data_base->AllowUserToResizeColumns = false;
			this->data_base->AllowUserToResizeRows = false;
			this->data_base->BackgroundColor = System::Drawing::SystemColors::ButtonHighlight;
			this->data_base->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->data_base->Location = System::Drawing::Point(12, 12);
			this->data_base->Name = L"data_base";
			this->data_base->ReadOnly = true;
			this->data_base->RowHeadersVisible = false;
			this->data_base->Size = System::Drawing::Size(803, 500);
			this->data_base->TabIndex = 1;
			// 
			// mode_label
			// 
			this->mode_label->AutoSize = true;
			this->mode_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->mode_label->Location = System::Drawing::Point(26, 530);
			this->mode_label->Name = L"mode_label";
			this->mode_label->Size = System::Drawing::Size(190, 20);
			this->mode_label->TabIndex = 2;
			this->mode_label->Text = L"Режим пользователя";
			// 
			// update_button
			// 
			this->update_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->update_button->Location = System::Drawing::Point(235, 525);
			this->update_button->Name = L"update_button";
			this->update_button->Size = System::Drawing::Size(186, 33);
			this->update_button->TabIndex = 9;
			this->update_button->Text = L"Обновить таблицу";
			this->update_button->UseVisualStyleBackColor = true;
			this->update_button->Click += gcnew System::EventHandler(this, &UserSite::update_button_Click);
			// 
			// set_filters_button
			// 
			this->set_filters_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->set_filters_button->Location = System::Drawing::Point(427, 525);
			this->set_filters_button->Name = L"set_filters_button";
			this->set_filters_button->Size = System::Drawing::Size(186, 33);
			this->set_filters_button->TabIndex = 10;
			this->set_filters_button->Text = L"Настроить фильтры";
			this->set_filters_button->UseVisualStyleBackColor = true;
			this->set_filters_button->Click += gcnew System::EventHandler(this, &UserSite::set_filters_button_Click);
			// 
			// exit_button
			// 
			this->exit_button->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->exit_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->exit_button->Location = System::Drawing::Point(619, 525);
			this->exit_button->Name = L"exit_button";
			this->exit_button->Size = System::Drawing::Size(186, 33);
			this->exit_button->TabIndex = 11;
			this->exit_button->Text = L"Выйти в главное меню";
			this->exit_button->UseVisualStyleBackColor = false;
			this->exit_button->Click += gcnew System::EventHandler(this, &UserSite::exit_button_Click);
			// 
			// UserSite
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->ClientSize = System::Drawing::Size(831, 586);
			this->Controls->Add(this->exit_button);
			this->Controls->Add(this->set_filters_button);
			this->Controls->Add(this->update_button);
			this->Controls->Add(this->mode_label);
			this->Controls->Add(this->data_base);
			this->MaximizeBox = false;
			this->Name = L"UserSite";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Режим пользователя";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->data_base))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	};
}
