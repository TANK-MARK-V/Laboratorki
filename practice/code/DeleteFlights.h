#pragma once

#include <msclr/marshal.h>
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
	/// Сводка для DeleteFlights
	/// </summary>
	public ref class DeleteFlights : public System::Windows::Forms::Form
	{
	public:
		DeleteFlights(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~DeleteFlights()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ del_button;
	private: System::Windows::Forms::RadioButton^ from_array_radio;
	private: System::Windows::Forms::RadioButton^ filtered_radio;
	private: System::Windows::Forms::Label^ apply_label;
	private: System::Windows::Forms::TextBox^ to_del_textbox;
	private: System::Windows::Forms::Label^ deleting_label;
	private: System::Windows::Forms::Label^ error_label;
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
			this->del_button = (gcnew System::Windows::Forms::Button());
			this->from_array_radio = (gcnew System::Windows::Forms::RadioButton());
			this->filtered_radio = (gcnew System::Windows::Forms::RadioButton());
			this->apply_label = (gcnew System::Windows::Forms::Label());
			this->to_del_textbox = (gcnew System::Windows::Forms::TextBox());
			this->deleting_label = (gcnew System::Windows::Forms::Label());
			this->error_label = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// del_button
			// 
			this->del_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->del_button->Location = System::Drawing::Point(109, 183);
			this->del_button->Name = L"del_button";
			this->del_button->Size = System::Drawing::Size(118, 44);
			this->del_button->TabIndex = 21;
			this->del_button->Text = L"Применить";
			this->del_button->UseVisualStyleBackColor = true;
			this->del_button->Click += gcnew System::EventHandler(this, &DeleteFlights::edit_button_Click);
			// 
			// from_array_radio
			// 
			this->from_array_radio->AutoSize = true;
			this->from_array_radio->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->from_array_radio->Location = System::Drawing::Point(11, 86);
			this->from_array_radio->Name = L"from_array_radio";
			this->from_array_radio->Size = System::Drawing::Size(186, 21);
			this->from_array_radio->TabIndex = 35;
			this->from_array_radio->Text = L"По выбранным номерам";
			this->from_array_radio->UseVisualStyleBackColor = true;
			// 
			// filtered_radio
			// 
			this->filtered_radio->AutoSize = true;
			this->filtered_radio->Checked = true;
			this->filtered_radio->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->filtered_radio->Location = System::Drawing::Point(11, 59);
			this->filtered_radio->Name = L"filtered_radio";
			this->filtered_radio->Size = System::Drawing::Size(216, 21);
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
			this->apply_label->Location = System::Drawing::Point(8, 39);
			this->apply_label->Name = L"apply_label";
			this->apply_label->Size = System::Drawing::Size(225, 17);
			this->apply_label->TabIndex = 37;
			this->apply_label->Text = L"Какие записи нужно удалить";
			// 
			// to_del_textbox
			// 
			this->to_del_textbox->Location = System::Drawing::Point(11, 120);
			this->to_del_textbox->Name = L"to_del_textbox";
			this->to_del_textbox->Size = System::Drawing::Size(308, 20);
			this->to_del_textbox->TabIndex = 38;
			// 
			// deleting_label
			// 
			this->deleting_label->AutoSize = true;
			this->deleting_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->deleting_label->Location = System::Drawing::Point(90, 9);
			this->deleting_label->Name = L"deleting_label";
			this->deleting_label->Size = System::Drawing::Size(157, 20);
			this->deleting_label->TabIndex = 0;
			this->deleting_label->Text = L"Удаление рейсов";
			// 
			// error_label
			// 
			this->error_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->error_label->ForeColor = System::Drawing::Color::Red;
			this->error_label->Location = System::Drawing::Point(12, 143);
			this->error_label->Name = L"error_label";
			this->error_label->Size = System::Drawing::Size(307, 37);
			this->error_label->TabIndex = 39;
			this->error_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// DeleteFlights
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->ClientSize = System::Drawing::Size(323, 238);
			this->Controls->Add(this->error_label);
			this->Controls->Add(this->to_del_textbox);
			this->Controls->Add(this->apply_label);
			this->Controls->Add(this->filtered_radio);
			this->Controls->Add(this->from_array_radio);
			this->Controls->Add(this->del_button);
			this->Controls->Add(this->deleting_label);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"DeleteFlights";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Удаление рейсов";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void edit_button_Click(System::Object^ sender, System::EventArgs^ e) {
		int* to_del;		// Указатель на массив с номерами записей, которые нужно удалить
		int last_ind = 0;	// Индекс последнего эл-та массива

		// Получим номера для изменения
		if (this->from_array_radio->Checked) {
			String^ numbers = this->to_del_textbox->Text;
			// Разделители: пробел, запятая, точка с запятой, табуляция
			array<wchar_t>^ delimiters = { L' ', L',', L';', L'\t' };
			array<String^>^ parts = numbers->Split(delimiters, StringSplitOptions::RemoveEmptyEntries);
			if (numbers->Length == 0 || parts->Length == 0) {
				this->error_label->Text = "Некорректно указаны номера";
				return;
			}
			// Выделяем память под to_del
			to_del = (int*)calloc(parts->Length + 1, sizeof(int));
			// Переводим все part в int
			for each (String ^ part in parts) {
				try {
					int num = Convert::ToInt32(part);
					to_del[last_ind++] = num;
				}
				catch (...) {
					free(to_del);
					this->error_label->Text = "Некорректно указаны номера";
					return;
				}
			}
			// Сортируем пузырьком полученный массив
			for (int k = 1; k < last_ind; k++)
				for (int i = 0; i < last_ind - k; i++)
					if (to_del[i] > to_del[i + 1]) {
						int buffer = to_del[i];
						to_del[i] = to_del[i + 1];
						to_del[i + 1] = buffer;
					}
			to_del[last_ind] = 0;
		}
		this->error_label->Text = "";
		delete_flights(this->filtered_radio->Checked, to_del, last_ind);
		if (this->from_array_radio->Checked) free(to_del);
		this->Close();
	}
};
}
