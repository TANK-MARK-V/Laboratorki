#pragma once

#include <msclr/marshal.h>
#include <locale.h>
#include <windows.h>
#include <stdlib.h>

#include "structure.h"
#include "file_funcs.h"

namespace MarkflightsUI {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для EditFlights
	/// </summary>
	public ref class EditFlights : public System::Windows::Forms::Form
	{
	public:
		EditFlights(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~EditFlights()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ editing_label;
	private: System::Windows::Forms::Label^ fnum_label;
	private: System::Windows::Forms::Label^ name_label;
	private: System::Windows::Forms::Label^ dest_label;
	private: System::Windows::Forms::Label^ days_label;
	private: System::Windows::Forms::CheckBox^ checkbox_1;
	private: System::Windows::Forms::CheckBox^ checkbox_2;
	private: System::Windows::Forms::CheckBox^ checkbox_3;
	private: System::Windows::Forms::CheckBox^ checkbox_4;
	private: System::Windows::Forms::CheckBox^ checkbox_5;
	private: System::Windows::Forms::CheckBox^ checkbox_6;
	private: System::Windows::Forms::CheckBox^ checkbox_7;
	private: System::Windows::Forms::MaskedTextBox^ dep_time_textbox;
	private: System::Windows::Forms::Label^ dep_time_label;
	private: System::Windows::Forms::MaskedTextBox^ arr_time_textbox;
	private: System::Windows::Forms::Label^ arr_time_label;
	private: System::Windows::Forms::Label^ price_label;
	private: System::Windows::Forms::Button^ edit_button;
	private: System::Windows::Forms::TextBox^ fnum_textbox;
	private: System::Windows::Forms::TextBox^ name_textbox;
	private: System::Windows::Forms::TextBox^ dest_textbox;
	private: System::Windows::Forms::TextBox^ price_textbox;
	private: System::Windows::Forms::Label^ error_label;
	private: System::Windows::Forms::CheckBox^ fnum_checkbox;
	private: System::Windows::Forms::CheckBox^ name_checkbox;
	private: System::Windows::Forms::CheckBox^ dest_checkbox;
	private: System::Windows::Forms::CheckBox^ days_checkbox;
	private: System::Windows::Forms::CheckBox^ dep_time_checkbox;
	private: System::Windows::Forms::CheckBox^ arr_time_checkbox;
	private: System::Windows::Forms::CheckBox^ price_checkbox;
	private: System::Windows::Forms::Label^ check_label;
	private: System::Windows::Forms::RadioButton^ from_array_radio;
	private: System::Windows::Forms::RadioButton^ filtered_radio;
	private: System::Windows::Forms::Label^ apply_label;
	private: System::Windows::Forms::TextBox^ to_edit_textbox;

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
			this->editing_label = (gcnew System::Windows::Forms::Label());
			this->fnum_label = (gcnew System::Windows::Forms::Label());
			this->name_label = (gcnew System::Windows::Forms::Label());
			this->dest_label = (gcnew System::Windows::Forms::Label());
			this->days_label = (gcnew System::Windows::Forms::Label());
			this->checkbox_1 = (gcnew System::Windows::Forms::CheckBox());
			this->checkbox_2 = (gcnew System::Windows::Forms::CheckBox());
			this->checkbox_3 = (gcnew System::Windows::Forms::CheckBox());
			this->checkbox_4 = (gcnew System::Windows::Forms::CheckBox());
			this->checkbox_5 = (gcnew System::Windows::Forms::CheckBox());
			this->checkbox_6 = (gcnew System::Windows::Forms::CheckBox());
			this->checkbox_7 = (gcnew System::Windows::Forms::CheckBox());
			this->dep_time_textbox = (gcnew System::Windows::Forms::MaskedTextBox());
			this->dep_time_label = (gcnew System::Windows::Forms::Label());
			this->arr_time_textbox = (gcnew System::Windows::Forms::MaskedTextBox());
			this->arr_time_label = (gcnew System::Windows::Forms::Label());
			this->price_label = (gcnew System::Windows::Forms::Label());
			this->edit_button = (gcnew System::Windows::Forms::Button());
			this->fnum_textbox = (gcnew System::Windows::Forms::TextBox());
			this->name_textbox = (gcnew System::Windows::Forms::TextBox());
			this->dest_textbox = (gcnew System::Windows::Forms::TextBox());
			this->price_textbox = (gcnew System::Windows::Forms::TextBox());
			this->error_label = (gcnew System::Windows::Forms::Label());
			this->fnum_checkbox = (gcnew System::Windows::Forms::CheckBox());
			this->name_checkbox = (gcnew System::Windows::Forms::CheckBox());
			this->dest_checkbox = (gcnew System::Windows::Forms::CheckBox());
			this->days_checkbox = (gcnew System::Windows::Forms::CheckBox());
			this->dep_time_checkbox = (gcnew System::Windows::Forms::CheckBox());
			this->arr_time_checkbox = (gcnew System::Windows::Forms::CheckBox());
			this->price_checkbox = (gcnew System::Windows::Forms::CheckBox());
			this->check_label = (gcnew System::Windows::Forms::Label());
			this->from_array_radio = (gcnew System::Windows::Forms::RadioButton());
			this->filtered_radio = (gcnew System::Windows::Forms::RadioButton());
			this->apply_label = (gcnew System::Windows::Forms::Label());
			this->to_edit_textbox = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// editing_label
			// 
			this->editing_label->AutoSize = true;
			this->editing_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->editing_label->Location = System::Drawing::Point(101, 9);
			this->editing_label->Name = L"editing_label";
			this->editing_label->Size = System::Drawing::Size(133, 20);
			this->editing_label->TabIndex = 0;
			this->editing_label->Text = L"Новые данные";
			// 
			// fnum_label
			// 
			this->fnum_label->AutoSize = true;
			this->fnum_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->fnum_label->Location = System::Drawing::Point(32, 68);
			this->fnum_label->Name = L"fnum_label";
			this->fnum_label->Size = System::Drawing::Size(94, 17);
			this->fnum_label->TabIndex = 1;
			this->fnum_label->Text = L"Номер рейса";
			// 
			// name_label
			// 
			this->name_label->AutoSize = true;
			this->name_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->name_label->Location = System::Drawing::Point(32, 94);
			this->name_label->Name = L"name_label";
			this->name_label->Size = System::Drawing::Size(100, 17);
			this->name_label->TabIndex = 3;
			this->name_label->Text = L"Тип самолёта";
			// 
			// dest_label
			// 
			this->dest_label->AutoSize = true;
			this->dest_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->dest_label->Location = System::Drawing::Point(32, 120);
			this->dest_label->Name = L"dest_label";
			this->dest_label->Size = System::Drawing::Size(130, 17);
			this->dest_label->TabIndex = 5;
			this->dest_label->Text = L"Пункт назначения";
			// 
			// days_label
			// 
			this->days_label->AutoSize = true;
			this->days_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->days_label->Location = System::Drawing::Point(32, 151);
			this->days_label->Name = L"days_label";
			this->days_label->Size = System::Drawing::Size(125, 17);
			this->days_label->TabIndex = 7;
			this->days_label->Text = L"Дни отправления";
			// 
			// checkbox_1
			// 
			this->checkbox_1->AutoSize = true;
			this->checkbox_1->Location = System::Drawing::Point(35, 181);
			this->checkbox_1->Name = L"checkbox_1";
			this->checkbox_1->Size = System::Drawing::Size(113, 17);
			this->checkbox_1->TabIndex = 8;
			this->checkbox_1->Text = L"- 1 (понедельник)";
			this->checkbox_1->UseVisualStyleBackColor = true;
			// 
			// checkbox_2
			// 
			this->checkbox_2->AutoSize = true;
			this->checkbox_2->Location = System::Drawing::Point(35, 204);
			this->checkbox_2->Name = L"checkbox_2";
			this->checkbox_2->Size = System::Drawing::Size(88, 17);
			this->checkbox_2->TabIndex = 9;
			this->checkbox_2->Text = L"- 2 (вторник)";
			this->checkbox_2->UseVisualStyleBackColor = true;
			// 
			// checkbox_3
			// 
			this->checkbox_3->AutoSize = true;
			this->checkbox_3->Location = System::Drawing::Point(35, 227);
			this->checkbox_3->Name = L"checkbox_3";
			this->checkbox_3->Size = System::Drawing::Size(77, 17);
			this->checkbox_3->TabIndex = 10;
			this->checkbox_3->Text = L"- 3 (среда)";
			this->checkbox_3->UseVisualStyleBackColor = true;
			// 
			// checkbox_4
			// 
			this->checkbox_4->AutoSize = true;
			this->checkbox_4->Location = System::Drawing::Point(35, 250);
			this->checkbox_4->Name = L"checkbox_4";
			this->checkbox_4->Size = System::Drawing::Size(86, 17);
			this->checkbox_4->TabIndex = 11;
			this->checkbox_4->Text = L"- 4 (четверг)";
			this->checkbox_4->UseVisualStyleBackColor = true;
			// 
			// checkbox_5
			// 
			this->checkbox_5->AutoSize = true;
			this->checkbox_5->Location = System::Drawing::Point(35, 273);
			this->checkbox_5->Name = L"checkbox_5";
			this->checkbox_5->Size = System::Drawing::Size(88, 17);
			this->checkbox_5->TabIndex = 12;
			this->checkbox_5->Text = L"- 5 (пятница)";
			this->checkbox_5->UseVisualStyleBackColor = true;
			// 
			// checkbox_6
			// 
			this->checkbox_6->AutoSize = true;
			this->checkbox_6->Location = System::Drawing::Point(35, 296);
			this->checkbox_6->Name = L"checkbox_6";
			this->checkbox_6->Size = System::Drawing::Size(87, 17);
			this->checkbox_6->TabIndex = 13;
			this->checkbox_6->Text = L"- 6 (суббота)";
			this->checkbox_6->UseVisualStyleBackColor = true;
			// 
			// checkbox_7
			// 
			this->checkbox_7->AutoSize = true;
			this->checkbox_7->Location = System::Drawing::Point(35, 319);
			this->checkbox_7->Name = L"checkbox_7";
			this->checkbox_7->Size = System::Drawing::Size(113, 17);
			this->checkbox_7->TabIndex = 14;
			this->checkbox_7->Text = L"- 7 (воскресенье)";
			this->checkbox_7->UseVisualStyleBackColor = true;
			// 
			// dep_time_textbox
			// 
			this->dep_time_textbox->Location = System::Drawing::Point(203, 348);
			this->dep_time_textbox->Mask = L"00:00";
			this->dep_time_textbox->Name = L"dep_time_textbox";
			this->dep_time_textbox->PromptChar = '0';
			this->dep_time_textbox->Size = System::Drawing::Size(100, 20);
			this->dep_time_textbox->TabIndex = 16;
			this->dep_time_textbox->ValidatingType = System::DateTime::typeid;
			// 
			// dep_time_label
			// 
			this->dep_time_label->AutoSize = true;
			this->dep_time_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->dep_time_label->Location = System::Drawing::Point(32, 348);
			this->dep_time_label->Name = L"dep_time_label";
			this->dep_time_label->Size = System::Drawing::Size(102, 17);
			this->dep_time_label->TabIndex = 15;
			this->dep_time_label->Text = L"Время вылета";
			// 
			// arr_time_textbox
			// 
			this->arr_time_textbox->Location = System::Drawing::Point(203, 374);
			this->arr_time_textbox->Mask = L"00:00";
			this->arr_time_textbox->Name = L"arr_time_textbox";
			this->arr_time_textbox->PromptChar = '0';
			this->arr_time_textbox->Size = System::Drawing::Size(100, 20);
			this->arr_time_textbox->TabIndex = 18;
			this->arr_time_textbox->ValidatingType = System::DateTime::typeid;
			// 
			// arr_time_label
			// 
			this->arr_time_label->AutoSize = true;
			this->arr_time_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->arr_time_label->Location = System::Drawing::Point(32, 374);
			this->arr_time_label->Name = L"arr_time_label";
			this->arr_time_label->Size = System::Drawing::Size(109, 17);
			this->arr_time_label->TabIndex = 17;
			this->arr_time_label->Text = L"Время прилёта";
			// 
			// price_label
			// 
			this->price_label->AutoSize = true;
			this->price_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->price_label->Location = System::Drawing::Point(32, 400);
			this->price_label->Name = L"price_label";
			this->price_label->Size = System::Drawing::Size(94, 17);
			this->price_label->TabIndex = 19;
			this->price_label->Text = L"Цена билета";
			// 
			// edit_button
			// 
			this->edit_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->edit_button->Location = System::Drawing::Point(105, 584);
			this->edit_button->Name = L"edit_button";
			this->edit_button->Size = System::Drawing::Size(118, 44);
			this->edit_button->TabIndex = 21;
			this->edit_button->Text = L"Применить";
			this->edit_button->UseVisualStyleBackColor = true;
			this->edit_button->Click += gcnew System::EventHandler(this, &EditFlights::edit_button_Click);
			// 
			// fnum_textbox
			// 
			this->fnum_textbox->Location = System::Drawing::Point(203, 68);
			this->fnum_textbox->Name = L"fnum_textbox";
			this->fnum_textbox->Size = System::Drawing::Size(100, 20);
			this->fnum_textbox->TabIndex = 22;
			// 
			// name_textbox
			// 
			this->name_textbox->Location = System::Drawing::Point(203, 94);
			this->name_textbox->Name = L"name_textbox";
			this->name_textbox->Size = System::Drawing::Size(100, 20);
			this->name_textbox->TabIndex = 23;
			// 
			// dest_textbox
			// 
			this->dest_textbox->Location = System::Drawing::Point(203, 120);
			this->dest_textbox->Name = L"dest_textbox";
			this->dest_textbox->Size = System::Drawing::Size(100, 20);
			this->dest_textbox->TabIndex = 24;
			// 
			// price_textbox
			// 
			this->price_textbox->Location = System::Drawing::Point(203, 400);
			this->price_textbox->Name = L"price_textbox";
			this->price_textbox->Size = System::Drawing::Size(100, 20);
			this->price_textbox->TabIndex = 25;
			// 
			// error_label
			// 
			this->error_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->error_label->ForeColor = System::Drawing::Color::Red;
			this->error_label->Location = System::Drawing::Point(17, 432);
			this->error_label->Name = L"error_label";
			this->error_label->Size = System::Drawing::Size(286, 37);
			this->error_label->TabIndex = 26;
			this->error_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// fnum_checkbox
			// 
			this->fnum_checkbox->AutoSize = true;
			this->fnum_checkbox->Location = System::Drawing::Point(11, 71);
			this->fnum_checkbox->Name = L"fnum_checkbox";
			this->fnum_checkbox->Size = System::Drawing::Size(15, 14);
			this->fnum_checkbox->TabIndex = 27;
			this->fnum_checkbox->UseVisualStyleBackColor = true;
			// 
			// name_checkbox
			// 
			this->name_checkbox->AutoSize = true;
			this->name_checkbox->Location = System::Drawing::Point(11, 97);
			this->name_checkbox->Name = L"name_checkbox";
			this->name_checkbox->Size = System::Drawing::Size(15, 14);
			this->name_checkbox->TabIndex = 28;
			this->name_checkbox->UseVisualStyleBackColor = true;
			// 
			// dest_checkbox
			// 
			this->dest_checkbox->AutoSize = true;
			this->dest_checkbox->Location = System::Drawing::Point(11, 123);
			this->dest_checkbox->Name = L"dest_checkbox";
			this->dest_checkbox->Size = System::Drawing::Size(15, 14);
			this->dest_checkbox->TabIndex = 29;
			this->dest_checkbox->UseVisualStyleBackColor = true;
			// 
			// days_checkbox
			// 
			this->days_checkbox->AutoSize = true;
			this->days_checkbox->Location = System::Drawing::Point(11, 154);
			this->days_checkbox->Name = L"days_checkbox";
			this->days_checkbox->Size = System::Drawing::Size(15, 14);
			this->days_checkbox->TabIndex = 30;
			this->days_checkbox->UseVisualStyleBackColor = true;
			// 
			// dep_time_checkbox
			// 
			this->dep_time_checkbox->AutoSize = true;
			this->dep_time_checkbox->Location = System::Drawing::Point(11, 350);
			this->dep_time_checkbox->Name = L"dep_time_checkbox";
			this->dep_time_checkbox->Size = System::Drawing::Size(15, 14);
			this->dep_time_checkbox->TabIndex = 31;
			this->dep_time_checkbox->UseVisualStyleBackColor = true;
			// 
			// arr_time_checkbox
			// 
			this->arr_time_checkbox->AutoSize = true;
			this->arr_time_checkbox->Location = System::Drawing::Point(11, 377);
			this->arr_time_checkbox->Name = L"arr_time_checkbox";
			this->arr_time_checkbox->Size = System::Drawing::Size(15, 14);
			this->arr_time_checkbox->TabIndex = 32;
			this->arr_time_checkbox->UseVisualStyleBackColor = true;
			// 
			// price_checkbox
			// 
			this->price_checkbox->AutoSize = true;
			this->price_checkbox->Location = System::Drawing::Point(11, 403);
			this->price_checkbox->Name = L"price_checkbox";
			this->price_checkbox->Size = System::Drawing::Size(15, 14);
			this->price_checkbox->TabIndex = 33;
			this->price_checkbox->UseVisualStyleBackColor = true;
			// 
			// check_label
			// 
			this->check_label->AutoSize = true;
			this->check_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->check_label->Location = System::Drawing::Point(8, 41);
			this->check_label->Name = L"check_label";
			this->check_label->Size = System::Drawing::Size(184, 17);
			this->check_label->TabIndex = 34;
			this->check_label->Text = L"Выберите нужные поля";
			// 
			// from_array_radio
			// 
			this->from_array_radio->AutoSize = true;
			this->from_array_radio->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->from_array_radio->Location = System::Drawing::Point(11, 533);
			this->from_array_radio->Name = L"from_array_radio";
			this->from_array_radio->Size = System::Drawing::Size(169, 19);
			this->from_array_radio->TabIndex = 35;
			this->from_array_radio->Text = L"По выбранным номерам";
			this->from_array_radio->UseVisualStyleBackColor = true;
			// 
			// filtered_radio
			// 
			this->filtered_radio->AutoSize = true;
			this->filtered_radio->Checked = true;
			this->filtered_radio->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->filtered_radio->Location = System::Drawing::Point(11, 508);
			this->filtered_radio->Name = L"filtered_radio";
			this->filtered_radio->Size = System::Drawing::Size(193, 19);
			this->filtered_radio->TabIndex = 36;
			this->filtered_radio->TabStop = true;
			this->filtered_radio->Text = L"Все подходящие под фильтр";
			this->filtered_radio->UseVisualStyleBackColor = true;
			// 
			// apply_label
			// 
			this->apply_label->AutoSize = true;
			this->apply_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->apply_label->Location = System::Drawing::Point(12, 479);
			this->apply_label->Name = L"apply_label";
			this->apply_label->Size = System::Drawing::Size(235, 17);
			this->apply_label->TabIndex = 37;
			this->apply_label->Text = L"Какие записи нужно изменить";
			// 
			// to_edit_textbox
			// 
			this->to_edit_textbox->Location = System::Drawing::Point(8, 558);
			this->to_edit_textbox->Name = L"to_edit_textbox";
			this->to_edit_textbox->Size = System::Drawing::Size(308, 20);
			this->to_edit_textbox->TabIndex = 38;
			// 
			// EditFlights
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->ClientSize = System::Drawing::Size(323, 640);
			this->Controls->Add(this->to_edit_textbox);
			this->Controls->Add(this->apply_label);
			this->Controls->Add(this->filtered_radio);
			this->Controls->Add(this->from_array_radio);
			this->Controls->Add(this->check_label);
			this->Controls->Add(this->price_checkbox);
			this->Controls->Add(this->arr_time_checkbox);
			this->Controls->Add(this->dep_time_checkbox);
			this->Controls->Add(this->days_checkbox);
			this->Controls->Add(this->dest_checkbox);
			this->Controls->Add(this->name_checkbox);
			this->Controls->Add(this->fnum_checkbox);
			this->Controls->Add(this->error_label);
			this->Controls->Add(this->price_textbox);
			this->Controls->Add(this->dest_textbox);
			this->Controls->Add(this->name_textbox);
			this->Controls->Add(this->fnum_textbox);
			this->Controls->Add(this->edit_button);
			this->Controls->Add(this->price_label);
			this->Controls->Add(this->arr_time_textbox);
			this->Controls->Add(this->arr_time_label);
			this->Controls->Add(this->dep_time_textbox);
			this->Controls->Add(this->dep_time_label);
			this->Controls->Add(this->checkbox_7);
			this->Controls->Add(this->checkbox_6);
			this->Controls->Add(this->checkbox_5);
			this->Controls->Add(this->checkbox_4);
			this->Controls->Add(this->checkbox_3);
			this->Controls->Add(this->checkbox_2);
			this->Controls->Add(this->checkbox_1);
			this->Controls->Add(this->days_label);
			this->Controls->Add(this->dest_label);
			this->Controls->Add(this->name_label);
			this->Controls->Add(this->fnum_label);
			this->Controls->Add(this->editing_label);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"EditFlights";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Изменение рейсов";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void edit_button_Click(System::Object^ sender, System::EventArgs^ e) {
		Flight_filter flight_exapmle;	// Структура для хранения информации
		// Запишем все поля, на которые нужно применить изменение
		for (int i = 0; i < FIELDS_NUM; i++)	flight_exapmle.apply[i] = 0;
		if (this->fnum_checkbox->Checked)		flight_exapmle.apply[0] = 1;
		if (this->name_checkbox->Checked)		flight_exapmle.apply[1] = 1;
		if (this->dest_checkbox->Checked)		flight_exapmle.apply[2] = 1;
		if (this->days_checkbox->Checked)		flight_exapmle.apply[3] = 1;
		if (this->dep_time_checkbox->Checked)	flight_exapmle.apply[4] = 1;
		if (this->arr_time_checkbox->Checked)	flight_exapmle.apply[5] = 1;
		if (this->price_checkbox->Checked)		flight_exapmle.apply[6] = 1;
		if (flight_exapmle.apply[0] + flight_exapmle.apply[1] + flight_exapmle.apply[2]
			+ flight_exapmle.apply[3] + flight_exapmle.apply[4]
			+ flight_exapmle.apply[5] + flight_exapmle.apply[6] == 0) {
			this->error_label->Text = "Нужно выбрать хотя бы одно поле";
			return;
		}
		// Получаем и проверяем fnum
		if (flight_exapmle.apply[0]) {
			try {
				flight_exapmle.fnum = Convert::ToInt32(this->fnum_textbox->Text);
			}
			catch (...) {
				this->error_label->Text = L"Некорректный номер рейса";
				return;
			}
			if (flight_exapmle.fnum <= 0) {
				this->error_label->Text = L"Некорректный номер рейса";
				return;
			}
		}
		
		// Получаем и проверяем name
		if (flight_exapmle.apply[1]) {
			copy_char_from_string(flight_exapmle.name, TEXT_LEN, this->name_textbox->Text);
			if (!flight_exapmle.name[0]) {
				this->error_label->Text = L"Некорректный тип самолёта";
				return;
			}
		}
		// Получаем и проверяем dest
		if (flight_exapmle.apply[2]) {
			copy_char_from_string(flight_exapmle.dest, TEXT_LEN, this->dest_textbox->Text);
			if (!flight_exapmle.dest[0]) {
				this->error_label->Text = L"Некорректный пункт назначения";
				return;
			}
		}
		// Получаем и проверяем days
		if (flight_exapmle.apply[3]) {
			int day = 0;
			if (this->checkbox_1->Checked) flight_exapmle.days[day++] = 1;
			if (this->checkbox_2->Checked) flight_exapmle.days[day++] = 2;
			if (this->checkbox_3->Checked) flight_exapmle.days[day++] = 3;
			if (this->checkbox_4->Checked) flight_exapmle.days[day++] = 4;
			if (this->checkbox_5->Checked) flight_exapmle.days[day++] = 5;
			if (this->checkbox_6->Checked) flight_exapmle.days[day++] = 6;
			if (this->checkbox_7->Checked) flight_exapmle.days[day++] = 7;
			if (day == 0) {
				this->error_label->Text = L"Нужно выбрать хотя бы один день отправления";
				return;
			}
			for (int i = day; i < 7; i++)  flight_exapmle.days[i] = 0;
		}
		// Получаем и проверяем dep_time
		if (flight_exapmle.apply[4]) {
			int dep_time_try = convert_string_time(this->dep_time_textbox->Text);
			if (dep_time_try == -1){
				this->error_label->Text = L"Некорректное время вылета";
				return;
			}
			flight_exapmle.dep_time = dep_time_try;
		}

		// Получаем и проверяем arr_time
		if (flight_exapmle.apply[5]) {
			int arr_time_try = convert_string_time(this->arr_time_textbox->Text);
			if (arr_time_try == -1) {
				this->error_label->Text = L"Некорректное время прилёта";
				return;
			}
			flight_exapmle.arr_time = arr_time_try;
		}
		// Получаем и проверяем price
		if (flight_exapmle.apply[6]) {
			try {
				flight_exapmle.price = Convert::ToDouble(this->price_textbox->Text->Replace(".", ","));
			}
			catch (...) {
				this->error_label->Text = L"Некорректная цена билета";
				return;
			}
			if (flight_exapmle.price <= 0) {
				this->error_label->Text = L"Некорректная цена билета";
				return;
			}
		}
		int* to_edit;		// Указатель на массив с номерами записей, которые нужно поменять
		int last_ind = 0;	// Индекс последнего эл-та массива
		// Получим номера для изменения
		if (this->from_array_radio->Checked) {
			String^ numbers = this->to_edit_textbox->Text;
			// Разделители: пробел, запятая, точка с запятой, табуляция
			array<wchar_t>^ delimiters = { L' ', L',', L';', L'\t' };
			array<String^>^ parts = numbers->Split(delimiters, StringSplitOptions::RemoveEmptyEntries);
			if (numbers->Length == 0 || parts->Length == 0) {
				this->error_label->Text = "Некорректно указаны номера";
				return;
			}
			// Выделяем память
			to_edit = (int*)calloc(parts->Length + 1, sizeof(int));
			// Конвертируем все part в int
			for each (String ^ part in parts) {
				try {
					int num = Convert::ToInt32(part);
					to_edit[last_ind++] = num;
				}
				catch (...) {
					free(to_edit);
					this->error_label->Text = "Некорректно указаны номера";
					return;
				}
			}
			// Сортируем пузырьком полученный массив
			for (int k = 1; k < last_ind; k++)
				for (int i = 0; i < last_ind - k; i++)
					if (to_edit[i] > to_edit[i + 1]) {
						int buffer = to_edit[i];
						to_edit[i] = to_edit[i + 1];
						to_edit[i + 1] = buffer;
					}
			to_edit[last_ind] = 0;
		}
		this->error_label->Text = "";
		edit_with_example(flight_exapmle, this->filtered_radio->Checked, to_edit, last_ind);
		if (this->from_array_radio->Checked) free(to_edit);
		this->Close();
	}
};
}
