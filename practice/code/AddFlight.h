#pragma once

#include <msclr/marshal.h>	// Создание char* из String^

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
	/// Сводка для AddFlight
	/// </summary>
	public ref class AddFlight : public System::Windows::Forms::Form
	{
	public:
		AddFlight(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~AddFlight()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Label^ adding_label;
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
	private: System::Windows::Forms::Button^ add_button;
	private: System::Windows::Forms::TextBox^ fnum_textbox;
	private: System::Windows::Forms::TextBox^ name_textbox;
	private: System::Windows::Forms::TextBox^ dest_textbox;
	private: System::Windows::Forms::TextBox^ price_textbox;
	private: System::Windows::Forms::Label^ error_label;
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
			this->adding_label = (gcnew System::Windows::Forms::Label());
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
			this->add_button = (gcnew System::Windows::Forms::Button());
			this->fnum_textbox = (gcnew System::Windows::Forms::TextBox());
			this->name_textbox = (gcnew System::Windows::Forms::TextBox());
			this->dest_textbox = (gcnew System::Windows::Forms::TextBox());
			this->price_textbox = (gcnew System::Windows::Forms::TextBox());
			this->error_label = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// adding_label
			// 
			this->adding_label->AutoSize = true;
			this->adding_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->adding_label->Location = System::Drawing::Point(70, 9);
			this->adding_label->Name = L"adding_label";
			this->adding_label->Size = System::Drawing::Size(167, 20);
			this->adding_label->TabIndex = 0;
			this->adding_label->Text = L"Добавление рейса";
			// 
			// fnum_label
			// 
			this->fnum_label->AutoSize = true;
			this->fnum_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->fnum_label->Location = System::Drawing::Point(12, 50);
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
			this->name_label->Location = System::Drawing::Point(12, 76);
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
			this->dest_label->Location = System::Drawing::Point(12, 102);
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
			this->days_label->Location = System::Drawing::Point(12, 133);
			this->days_label->Name = L"days_label";
			this->days_label->Size = System::Drawing::Size(125, 17);
			this->days_label->TabIndex = 7;
			this->days_label->Text = L"Дни отправления";
			// 
			// checkbox_1
			// 
			this->checkbox_1->AutoSize = true;
			this->checkbox_1->Location = System::Drawing::Point(15, 163);
			this->checkbox_1->Name = L"checkbox_1";
			this->checkbox_1->Size = System::Drawing::Size(113, 17);
			this->checkbox_1->TabIndex = 8;
			this->checkbox_1->Text = L"- 1 (понедельник)";
			this->checkbox_1->UseVisualStyleBackColor = true;
			// 
			// checkbox_2
			// 
			this->checkbox_2->AutoSize = true;
			this->checkbox_2->Location = System::Drawing::Point(15, 186);
			this->checkbox_2->Name = L"checkbox_2";
			this->checkbox_2->Size = System::Drawing::Size(88, 17);
			this->checkbox_2->TabIndex = 9;
			this->checkbox_2->Text = L"- 2 (вторник)";
			this->checkbox_2->UseVisualStyleBackColor = true;
			// 
			// checkbox_3
			// 
			this->checkbox_3->AutoSize = true;
			this->checkbox_3->Location = System::Drawing::Point(15, 209);
			this->checkbox_3->Name = L"checkbox_3";
			this->checkbox_3->Size = System::Drawing::Size(77, 17);
			this->checkbox_3->TabIndex = 10;
			this->checkbox_3->Text = L"- 3 (среда)";
			this->checkbox_3->UseVisualStyleBackColor = true;
			// 
			// checkbox_4
			// 
			this->checkbox_4->AutoSize = true;
			this->checkbox_4->Location = System::Drawing::Point(15, 232);
			this->checkbox_4->Name = L"checkbox_4";
			this->checkbox_4->Size = System::Drawing::Size(86, 17);
			this->checkbox_4->TabIndex = 11;
			this->checkbox_4->Text = L"- 4 (четверг)";
			this->checkbox_4->UseVisualStyleBackColor = true;
			// 
			// checkbox_5
			// 
			this->checkbox_5->AutoSize = true;
			this->checkbox_5->Location = System::Drawing::Point(15, 255);
			this->checkbox_5->Name = L"checkbox_5";
			this->checkbox_5->Size = System::Drawing::Size(88, 17);
			this->checkbox_5->TabIndex = 12;
			this->checkbox_5->Text = L"- 5 (пятница)";
			this->checkbox_5->UseVisualStyleBackColor = true;
			// 
			// checkbox_6
			// 
			this->checkbox_6->AutoSize = true;
			this->checkbox_6->Location = System::Drawing::Point(15, 278);
			this->checkbox_6->Name = L"checkbox_6";
			this->checkbox_6->Size = System::Drawing::Size(87, 17);
			this->checkbox_6->TabIndex = 13;
			this->checkbox_6->Text = L"- 6 (суббота)";
			this->checkbox_6->UseVisualStyleBackColor = true;
			// 
			// checkbox_7
			// 
			this->checkbox_7->AutoSize = true;
			this->checkbox_7->Location = System::Drawing::Point(15, 301);
			this->checkbox_7->Name = L"checkbox_7";
			this->checkbox_7->Size = System::Drawing::Size(113, 17);
			this->checkbox_7->TabIndex = 14;
			this->checkbox_7->Text = L"- 7 (воскресенье)";
			this->checkbox_7->UseVisualStyleBackColor = true;
			// 
			// dep_time_textbox
			// 
			this->dep_time_textbox->Location = System::Drawing::Point(183, 330);
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
			this->dep_time_label->Location = System::Drawing::Point(12, 330);
			this->dep_time_label->Name = L"dep_time_label";
			this->dep_time_label->Size = System::Drawing::Size(102, 17);
			this->dep_time_label->TabIndex = 15;
			this->dep_time_label->Text = L"Время вылета";
			// 
			// arr_time_textbox
			// 
			this->arr_time_textbox->Location = System::Drawing::Point(183, 356);
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
			this->arr_time_label->Location = System::Drawing::Point(12, 356);
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
			this->price_label->Location = System::Drawing::Point(12, 382);
			this->price_label->Name = L"price_label";
			this->price_label->Size = System::Drawing::Size(94, 17);
			this->price_label->TabIndex = 19;
			this->price_label->Text = L"Цена билета";
			// 
			// add_button
			// 
			this->add_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->add_button->Location = System::Drawing::Point(88, 458);
			this->add_button->Name = L"add_button";
			this->add_button->Size = System::Drawing::Size(118, 44);
			this->add_button->TabIndex = 21;
			this->add_button->Text = L"Добавить";
			this->add_button->UseVisualStyleBackColor = true;
			this->add_button->Click += gcnew System::EventHandler(this, &AddFlight::add_button_Click);
			// 
			// fnum_textbox
			// 
			this->fnum_textbox->Location = System::Drawing::Point(183, 50);
			this->fnum_textbox->Name = L"fnum_textbox";
			this->fnum_textbox->Size = System::Drawing::Size(100, 20);
			this->fnum_textbox->TabIndex = 22;
			// 
			// name_textbox
			// 
			this->name_textbox->Location = System::Drawing::Point(183, 76);
			this->name_textbox->Name = L"name_textbox";
			this->name_textbox->Size = System::Drawing::Size(100, 20);
			this->name_textbox->TabIndex = 23;
			// 
			// dest_textbox
			// 
			this->dest_textbox->Location = System::Drawing::Point(183, 102);
			this->dest_textbox->Name = L"dest_textbox";
			this->dest_textbox->Size = System::Drawing::Size(100, 20);
			this->dest_textbox->TabIndex = 24;
			// 
			// price_textbox
			// 
			this->price_textbox->Location = System::Drawing::Point(183, 382);
			this->price_textbox->Name = L"price_textbox";
			this->price_textbox->Size = System::Drawing::Size(100, 20);
			this->price_textbox->TabIndex = 25;
			// 
			// error_label
			// 
			this->error_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->error_label->ForeColor = System::Drawing::Color::Red;
			this->error_label->Location = System::Drawing::Point(12, 418);
			this->error_label->Name = L"error_label";
			this->error_label->Size = System::Drawing::Size(275, 37);
			this->error_label->TabIndex = 26;
			this->error_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// AddFlight
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->ClientSize = System::Drawing::Size(304, 516);
			this->Controls->Add(this->error_label);
			this->Controls->Add(this->price_textbox);
			this->Controls->Add(this->dest_textbox);
			this->Controls->Add(this->name_textbox);
			this->Controls->Add(this->fnum_textbox);
			this->Controls->Add(this->add_button);
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
			this->Controls->Add(this->adding_label);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"AddFlight";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Добавление рейса";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void add_button_Click(System::Object^ sender, System::EventArgs^ e) {
	Flight flight_buffer;	// Структура для хранения информации
	// Получаем и проверяем fnum
	try {
		flight_buffer.fnum = Convert::ToInt32(this->fnum_textbox->Text);
	}
	catch (...) {
		this->error_label->Text = L"Некорректный номер рейса";
		return;
	}
	if (flight_buffer.fnum <= 0) {
		this->error_label->Text = L"Некорректный номер рейса";
		return;
	}
	// Получаем и проверяем name
	copy_char_from_string(flight_buffer.name, TEXT_LEN, this->name_textbox->Text);
	if (!flight_buffer.name[0]) {
		this->error_label->Text = L"Некорректный тип самолёта";
		return;
	}
	// Получаем и проверяем dest
	copy_char_from_string(flight_buffer.dest, TEXT_LEN, this->dest_textbox->Text);
	if (!flight_buffer.dest[0]) {
		this->error_label->Text = L"Некорректный пункт назначения";
		return;
	}
	// Получаем и проверяем days
	int day = 0;
	if (this->checkbox_1->Checked) flight_buffer.days[day++] = 1;
	if (this->checkbox_2->Checked) flight_buffer.days[day++] = 2;
	if (this->checkbox_3->Checked) flight_buffer.days[day++] = 3;
	if (this->checkbox_4->Checked) flight_buffer.days[day++] = 4;
	if (this->checkbox_5->Checked) flight_buffer.days[day++] = 5;
	if (this->checkbox_6->Checked) flight_buffer.days[day++] = 6;
	if (this->checkbox_7->Checked) flight_buffer.days[day++] = 7;
	if (day == 0) {
		this->error_label->Text = L"Нужно выбрать хотя бы один день отправления";
		return;
	}
	for (int i = day; i < 7; i++)  flight_buffer.days[i] = 0;
	// Получаем и проверяем dep_time
	int dep_time_try = convert_string_time(this->dep_time_textbox->Text);
	if (dep_time_try == -1) {
		this->error_label->Text = L"Некорректное время вылета";
		return;
	}
	flight_buffer.dep_time = dep_time_try;
	// Получаем и проверяем arr_time
	int arr_time_try = convert_string_time(this->arr_time_textbox->Text);
	if (arr_time_try == -1) {
		this->error_label->Text = L"Некорректное время прилёта";
		return;
	}
	flight_buffer.arr_time = arr_time_try;
	// Получаем и проверяем price
	try {
		flight_buffer.price = Convert::ToDouble(this->price_textbox->Text->Replace(".", ","));
	}
	catch (...) {
		this->error_label->Text = L"Некорректная цена билета";
		return;
	}
	if (flight_buffer.price <= 0) {
		this->error_label->Text = L"Некорректная цена билета";
		return;
	}
	this->error_label->Text = "";
	// Записываем в БД
	char file_path[FILE_NAME_LEN];	// Название файла БД
	if (get_file(file_path) == -1) {
		MessageBox::Show("Ошибка открытия файла для записи: недостаточно прав для получения пути");
		return;
	}
	FILE* table = fopen(file_path, "a");
	if (table == NULL) {
		MessageBox::Show("Недостаточно прав для редактирования файла. Добавление отменено");
		return;
	}
	write_line(table, flight_buffer);
	fclose(table);
	this->Close();
}
};
}