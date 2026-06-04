#pragma once

#include <msclr/marshal.h>

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
	/// Сводка для EditFilterField
	/// </summary>
	public ref class EditFilterField : public System::Windows::Forms::Form
	{
		int filter_num;		// Номер фильтра в списке
		int field_num;		// Номер поля фильтра
	
	public:
		EditFilterField(int f, int n)
		{
			this->filter_num = f;
			this->field_num = n;
			InitializeComponent();
			if (f == 0) {
				this->logic_label->Visible = 0;
				this->and_radio->Visible = 0;
				this->or_radio->Visible = 0;
			}
			if (n < 4)
				this->ClientSize = System::Drawing::Size(280 - 16, 143);
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~EditFilterField()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ compare_label;
	private: System::Windows::Forms::RadioButton^ more_radio;
	private: System::Windows::Forms::RadioButton^ less_radio;
	private: System::Windows::Forms::RadioButton^ more_equals_radio;
	private: System::Windows::Forms::RadioButton^ less_equals_radio;
	private: System::Windows::Forms::RadioButton^ equals_radio;
	private: System::Windows::Forms::Panel^ logic_panel;
	private: System::Windows::Forms::Panel^ apply_panel;
	private: System::Windows::Forms::Button^ save_button;
	private: System::Windows::Forms::Label^ new_data_label;
	private: System::Windows::Forms::TextBox^ new_data_textbox;
	private: System::Windows::Forms::Label^ logic_label;
	private: System::Windows::Forms::RadioButton^ and_radio;
	private: System::Windows::Forms::RadioButton^ or_radio;
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
			this->save_button = (gcnew System::Windows::Forms::Button());
			this->new_data_label = (gcnew System::Windows::Forms::Label());
			this->new_data_textbox = (gcnew System::Windows::Forms::TextBox());
			this->logic_label = (gcnew System::Windows::Forms::Label());
			this->and_radio = (gcnew System::Windows::Forms::RadioButton());
			this->or_radio = (gcnew System::Windows::Forms::RadioButton());
			this->compare_label = (gcnew System::Windows::Forms::Label());
			this->more_radio = (gcnew System::Windows::Forms::RadioButton());
			this->less_radio = (gcnew System::Windows::Forms::RadioButton());
			this->more_equals_radio = (gcnew System::Windows::Forms::RadioButton());
			this->less_equals_radio = (gcnew System::Windows::Forms::RadioButton());
			this->equals_radio = (gcnew System::Windows::Forms::RadioButton());
			this->logic_panel = (gcnew System::Windows::Forms::Panel());
			this->apply_panel = (gcnew System::Windows::Forms::Panel());
			this->logic_panel->SuspendLayout();
			this->apply_panel->SuspendLayout();
			this->SuspendLayout();
			// 
			// save_button
			// 
			this->save_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->save_button->Location = System::Drawing::Point(12, 70);
			this->save_button->Name = L"save_button";
			this->save_button->Size = System::Drawing::Size(109, 31);
			this->save_button->TabIndex = 0;
			this->save_button->Text = L"Сохранить";
			this->save_button->UseVisualStyleBackColor = true;
			this->save_button->Click += gcnew System::EventHandler(this, &EditFilterField::save_button_Click);
			// 
			// new_data_label
			// 
			this->new_data_label->AutoSize = true;
			this->new_data_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->new_data_label->Location = System::Drawing::Point(12, 9);
			this->new_data_label->Name = L"new_data_label";
			this->new_data_label->Size = System::Drawing::Size(130, 17);
			this->new_data_label->TabIndex = 1;
			this->new_data_label->Text = L"Новое значение";
			// 
			// new_data_textbox
			// 
			this->new_data_textbox->ForeColor = System::Drawing::Color::Black;
			this->new_data_textbox->Location = System::Drawing::Point(148, 9);
			this->new_data_textbox->Name = L"new_data_textbox";
			this->new_data_textbox->Size = System::Drawing::Size(100, 20);
			this->new_data_textbox->TabIndex = 2;
			// 
			// logic_label
			// 
			this->logic_label->AutoSize = true;
			this->logic_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->logic_label->Location = System::Drawing::Point(12, 38);
			this->logic_label->Name = L"logic_label";
			this->logic_label->Size = System::Drawing::Size(163, 17);
			this->logic_label->TabIndex = 3;
			this->logic_label->Text = L"Логический операнд";
			// 
			// and_radio
			// 
			this->and_radio->AutoSize = true;
			this->and_radio->Checked = true;
			this->and_radio->Location = System::Drawing::Point(0, 0);
			this->and_radio->Name = L"and_radio";
			this->and_radio->Size = System::Drawing::Size(33, 17);
			this->and_radio->TabIndex = 4;
			this->and_radio->TabStop = true;
			this->and_radio->Text = L"И";
			this->and_radio->UseVisualStyleBackColor = true;
			// 
			// or_radio
			// 
			this->or_radio->AutoSize = true;
			this->or_radio->Location = System::Drawing::Point(0, 23);
			this->or_radio->Name = L"or_radio";
			this->or_radio->Size = System::Drawing::Size(49, 17);
			this->or_radio->TabIndex = 5;
			this->or_radio->Text = L"ИЛИ";
			this->or_radio->UseVisualStyleBackColor = true;
			// 
			// compare_label
			// 
			this->compare_label->AutoSize = true;
			this->compare_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->compare_label->Location = System::Drawing::Point(273, 9);
			this->compare_label->Name = L"compare_label";
			this->compare_label->Size = System::Drawing::Size(89, 17);
			this->compare_label->TabIndex = 6;
			this->compare_label->Text = L"Сравнение";
			// 
			// more_radio
			// 
			this->more_radio->AutoSize = true;
			this->more_radio->Checked = true;
			this->more_radio->Location = System::Drawing::Point(0, 0);
			this->more_radio->Name = L"more_radio";
			this->more_radio->Size = System::Drawing::Size(31, 17);
			this->more_radio->TabIndex = 7;
			this->more_radio->TabStop = true;
			this->more_radio->Text = L">";
			this->more_radio->UseVisualStyleBackColor = true;
			// 
			// less_radio
			// 
			this->less_radio->AutoSize = true;
			this->less_radio->Location = System::Drawing::Point(37, 0);
			this->less_radio->Name = L"less_radio";
			this->less_radio->Size = System::Drawing::Size(31, 17);
			this->less_radio->TabIndex = 8;
			this->less_radio->Text = L"<";
			this->less_radio->UseVisualStyleBackColor = true;
			// 
			// more_equals_radio
			// 
			this->more_equals_radio->AutoSize = true;
			this->more_equals_radio->Location = System::Drawing::Point(0, 46);
			this->more_equals_radio->Name = L"more_equals_radio";
			this->more_equals_radio->Size = System::Drawing::Size(37, 17);
			this->more_equals_radio->TabIndex = 9;
			this->more_equals_radio->Text = L">=";
			this->more_equals_radio->UseVisualStyleBackColor = true;
			// 
			// less_equals_radio
			// 
			this->less_equals_radio->AutoSize = true;
			this->less_equals_radio->Location = System::Drawing::Point(43, 46);
			this->less_equals_radio->Name = L"less_equals_radio";
			this->less_equals_radio->Size = System::Drawing::Size(37, 17);
			this->less_equals_radio->TabIndex = 10;
			this->less_equals_radio->Text = L"<=";
			this->less_equals_radio->UseVisualStyleBackColor = true;
			// 
			// equals_radio
			// 
			this->equals_radio->AutoSize = true;
			this->equals_radio->Location = System::Drawing::Point(0, 23);
			this->equals_radio->Name = L"equals_radio";
			this->equals_radio->Size = System::Drawing::Size(31, 17);
			this->equals_radio->TabIndex = 11;
			this->equals_radio->Text = L"=";
			this->equals_radio->UseVisualStyleBackColor = true;
			// 
			// logic_panel
			// 
			this->logic_panel->Controls->Add(this->or_radio);
			this->logic_panel->Controls->Add(this->and_radio);
			this->logic_panel->Location = System::Drawing::Point(180, 38);
			this->logic_panel->Name = L"logic_panel";
			this->logic_panel->Size = System::Drawing::Size(50, 51);
			this->logic_panel->TabIndex = 13;
			// 
			// apply_panel
			// 
			this->apply_panel->Controls->Add(this->more_radio);
			this->apply_panel->Controls->Add(this->less_radio);
			this->apply_panel->Controls->Add(this->less_equals_radio);
			this->apply_panel->Controls->Add(this->equals_radio);
			this->apply_panel->Controls->Add(this->more_equals_radio);
			this->apply_panel->Location = System::Drawing::Point(276, 38);
			this->apply_panel->Name = L"apply_panel";
			this->apply_panel->Size = System::Drawing::Size(84, 63);
			this->apply_panel->TabIndex = 14;
			// 
			// EditFilterField
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->ClientSize = System::Drawing::Size(372, 143);
			this->Controls->Add(this->apply_panel);
			this->Controls->Add(this->logic_panel);
			this->Controls->Add(this->compare_label);
			this->Controls->Add(this->logic_label);
			this->Controls->Add(this->new_data_textbox);
			this->Controls->Add(this->new_data_label);
			this->Controls->Add(this->save_button);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"EditFilterField";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Новое значение";
			this->logic_panel->ResumeLayout(false);
			this->logic_panel->PerformLayout();
			this->apply_panel->ResumeLayout(false);
			this->apply_panel->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void save_button_Click(System::Object^ sender, System::EventArgs^ e) {
	// Читаем фильтры в массив
	Flight_filter filters[FILTERS_NUM];
	if (read_filters(filters)) {
		MessageBox::Show(L"Не удалось открыть файл для чтения");
		return;
	}

	int f = this->filter_num;  // Номер фильтра
	int n = this->field_num;   // Номер поля

	// Для начала проверим корректность информации
	String^ data = this->new_data_textbox->Text;
	if (n == 0) {
		try {
			filters[f].fnum = Convert::ToInt32(data);
		}
		catch (...) {
			MessageBox::Show(L"Некорректный номер рейса");
			return;
		}
		if (filters[f].fnum <= 0) {
			MessageBox::Show(L"Некорректный номер рейса");
			return;
		}
	}
	else if (n == 1) {
		copy_char_from_string(filters[f].name, TEXT_LEN, data);
		if (!filters[f].name[0]) {
			MessageBox::Show(L"Некорректный тип самолёта");
			return;
		}
	}
	else if (n == 2) {
		copy_char_from_string(filters[f].dest, TEXT_LEN, data);
		if (!filters[f].dest[0]) {
			MessageBox::Show(L"Некорректный пункт назначения");
			return;
		}
	}
	else if (n == 3) {
		char user_input[30];  // Буфер для хранения String в char[]

		if (data->Length == 0) {  // Проверим длину строки
			MessageBox::Show(L"Некорректные дни отправления");
			return;
		}
		copy_char_from_string(user_input, 30, data);

		// Сохраним все допустимые цифры
		char symbols[30];  // Массив всех допустимых цифр
		int last_ind = 0;  // Индекс последнего элемента массива
		for (int i = 1; i <= 7; i++)
			symbols[last_ind++] = '0' + i;
		symbols[last_ind++] = ' '; symbols[last_ind++] = ','; symbols[last_ind++] = '\0';

		// Проверка на лишние символы
		if (strspn(user_input, symbols) != strlen(user_input)) {
			MessageBox::Show(L"Некорректные дни отправления");
			return;
		}

		char* number;  // Указатель на цифру для strtok
		number = strtok(user_input, " ,");
		last_ind = 0;  // Обнуляем счётчик

		if ((number == NULL) || (strlen(number) > 1)) {
			MessageBox::Show(L"Некорректные дни отправления");
			return;
		}
		filters[f].days[last_ind++] = *number - '0';
		while ((number = strtok(NULL, " ,")) != NULL) {
			if (strlen(number) > 1) {
				MessageBox::Show(L"Некорректные дни отправления");
				return;
			}
			int cur_number = *number - '0';
			// Проверим, есть ли эта цифра в списке
			int in_array = 0;
			for (int i = 0; i < last_ind; i++)
				if (filters[f].days[i] == cur_number) in_array = 1;
			if (!in_array) filters[f].days[last_ind++] = cur_number;
		}
		// Сортируем пузырьком
		for (int k = 1; k < last_ind; k++)
			for (int i = 0; i < last_ind - k; i++)
				if (filters[f].days[i] > filters[f].days[i + 1]) {
					int buffer = filters[f].days[i];
					filters[f].days[i] = filters[f].days[i + 1];
					filters[f].days[i + 1] = buffer;
				}
	}
	else if (n == 4) {
		String^ str_dep_time = data->Replace(":", "");
		// Проверим длину
		if (str_dep_time->Length < 3) {  // Длина не менее 3-ух символов, время некорректное
			MessageBox::Show(L"Некорректное время вылета - используйте формат 0:00");
			return;
		}
		else if (str_dep_time->Length == 3)  // Если 3 символа, то добавляем 0 и возвращаем ":"
			str_dep_time = "0" + str_dep_time[0].ToString() +
			":" + str_dep_time[1].ToString() + str_dep_time[2].ToString();
		else if (str_dep_time->Length == 4)  // Если 4 символа, то просто возвращаем ":"
			str_dep_time = str_dep_time[0].ToString() + str_dep_time[1].ToString()
			+ ":" + str_dep_time[2].ToString() + str_dep_time[3].ToString();
		else {  // Длина не более 4-ёх символов, время некорректное
			MessageBox::Show(L"Некорректное время вылета - используйте формат 00:00");
			return;
		}
		// Конвертируем время в int
		int dep_time_try = convert_string_time(str_dep_time);
		if (dep_time_try == -1) {
			MessageBox::Show(L"Некорректное время вылета");
			return;
		}
		filters[f].dep_time = dep_time_try;
	}
	else if (n == 5) {
		String^ str_arr_time = data->Replace(":", "");
		// Проверим длину
		if (str_arr_time->Length < 3) {  // Длина не менее 3-ух символов, время некорректное
			MessageBox::Show(L"Некорректное время прилёта - используйте формат 0:00");
			return;
		}
		else if (str_arr_time->Length == 3)  // Если 3 символа, то добавляем 0 и возвращаем ":"
			str_arr_time = "0" + str_arr_time[0].ToString()
			+ ":" + str_arr_time[1].ToString() + str_arr_time[2].ToString();
		else if (str_arr_time->Length == 4)  // Если 4 символа, то просто возвращаем ":"
			str_arr_time = str_arr_time[0].ToString() + str_arr_time[1].ToString()
			+ ":" + str_arr_time[2].ToString() + str_arr_time[3].ToString();
		else {  // Длина не более 4-ёх символов, время некорректное
			MessageBox::Show(L"Некорректное время прилёта - используйте формат 00:00");
			return;
		}
		// Конвертируем время в int
		int arr_time_try = convert_string_time(str_arr_time);
		if (arr_time_try == -1) {
			MessageBox::Show(L"Некорректное время прилёта");
			return;
		}
		filters[f].arr_time = arr_time_try;
	}
	else if (n == 6) {
		try {
			filters[f].price = Convert::ToDouble(data);
		}
		catch (...) {
			MessageBox::Show(L"Некорректная цена билета");
			return;
		}
		if (filters[f].price <= 0) {
			MessageBox::Show(L"Некорректная цена билета");
			return;
		}
	}
	// Если это не первый по счёту фильтр, то у него можно задать логический оператор
	if (f != 0)
		if (this->or_radio->Checked) filters[f].logic[n] = 1;
		else filters[f].logic[n] = 0;
	else filters[f].logic[n] = 0;
	// Если это время или цена, то можно задать оператор сравнения
	if (4 <= n && n <= 6) {
			 if (this->more_radio->Checked) filters[f].apply[n] = 1;		// >
		else if (this->less_radio->Checked) filters[f].apply[n] = 2;		// <
		else if (this->equals_radio->Checked) filters[f].apply[n] = 3;		// =
		else if (this->more_equals_radio->Checked) filters[f].apply[n] = 4;	// >=
		else if (this->less_equals_radio->Checked) filters[f].apply[n] = 5;	// <=
	}
	else filters[f].apply[n] = 1;
	// Пробуем сохранить фильтры
	int err;
	if (err = write_filters(filters)) {
		MessageBox::Show(L"Не удалось открыть файл для записи - ошибка " + err);
		return;
	}
	this->Close();
}
};
}
