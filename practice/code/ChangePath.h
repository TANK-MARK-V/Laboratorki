#pragma once

#include <msclr/marshal.h>
#include "file_funcs.h"
#include <windows.h>

namespace MarkflightsUI {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для ChangePath
	/// </summary>
	public ref class ChangePath : public System::Windows::Forms::Form
	{
	public:
		ChangePath(void)
		{
			InitializeComponent();
			// Получаем путь до файла
			char file_path[FILE_NAME_LEN];
			if (get_file(file_path) == 1) {
				MessageBox::Show(L"Слишком длинный путь, запись произойдёт по пути " DIR_NAME "/" FILE_NAME);
				return;
			}
			this->cur_path_textbox->Text = gcnew String(file_path);
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~ChangePath()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ choose_path_button;
	private: System::Windows::Forms::Label^ changing_label;
	private: System::Windows::Forms::RadioButton^ new_file_radio;
	private: System::Windows::Forms::RadioButton^ exist_file_radio;
	private: System::Windows::Forms::Label^ cur_path_label;
	private: System::Windows::Forms::Label^ new_path_label;
	private: System::Windows::Forms::TextBox^ cur_path_textbox;
	private: System::Windows::Forms::TextBox^ new_path_textbox;
	private: System::Windows::Forms::CheckBox^ copy_file_checkbox;
	private: System::Windows::Forms::CheckBox^ delete_file_checkbox;
	private: System::Windows::Forms::Button^ save_button;
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
			this->choose_path_button = (gcnew System::Windows::Forms::Button());
			this->changing_label = (gcnew System::Windows::Forms::Label());
			this->new_file_radio = (gcnew System::Windows::Forms::RadioButton());
			this->exist_file_radio = (gcnew System::Windows::Forms::RadioButton());
			this->cur_path_label = (gcnew System::Windows::Forms::Label());
			this->new_path_label = (gcnew System::Windows::Forms::Label());
			this->cur_path_textbox = (gcnew System::Windows::Forms::TextBox());
			this->new_path_textbox = (gcnew System::Windows::Forms::TextBox());
			this->copy_file_checkbox = (gcnew System::Windows::Forms::CheckBox());
			this->delete_file_checkbox = (gcnew System::Windows::Forms::CheckBox());
			this->save_button = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// choose_path_button
			// 
			this->choose_path_button->Location = System::Drawing::Point(200, 90);
			this->choose_path_button->Name = L"choose_path_button";
			this->choose_path_button->Size = System::Drawing::Size(75, 44);
			this->choose_path_button->TabIndex = 0;
			this->choose_path_button->Text = L"Создать";
			this->choose_path_button->UseVisualStyleBackColor = true;
			this->choose_path_button->Click += gcnew System::EventHandler(this, &ChangePath::choose_path_button_Click);
			// 
			// changing_label
			// 
			this->changing_label->AutoSize = true;
			this->changing_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->changing_label->Location = System::Drawing::Point(30, 9);
			this->changing_label->Name = L"changing_label";
			this->changing_label->Size = System::Drawing::Size(234, 20);
			this->changing_label->TabIndex = 1;
			this->changing_label->Text = L"Изменение пути до файла";
			// 
			// new_file_radio
			// 
			this->new_file_radio->AutoSize = true;
			this->new_file_radio->Checked = true;
			this->new_file_radio->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->new_file_radio->Location = System::Drawing::Point(19, 90);
			this->new_file_radio->Name = L"new_file_radio";
			this->new_file_radio->Size = System::Drawing::Size(149, 19);
			this->new_file_radio->TabIndex = 2;
			this->new_file_radio->TabStop = true;
			this->new_file_radio->Text = L"Создать новый файл";
			this->new_file_radio->UseVisualStyleBackColor = true;
			this->new_file_radio->Click += gcnew System::EventHandler(this, &ChangePath::radio_button_Click);
			// 
			// exist_file_radio
			// 
			this->exist_file_radio->AutoSize = true;
			this->exist_file_radio->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->exist_file_radio->Location = System::Drawing::Point(19, 115);
			this->exist_file_radio->Name = L"exist_file_radio";
			this->exist_file_radio->Size = System::Drawing::Size(164, 19);
			this->exist_file_radio->TabIndex = 3;
			this->exist_file_radio->Text = L"Выбрать существующий";
			this->exist_file_radio->UseVisualStyleBackColor = true;
			this->exist_file_radio->Click += gcnew System::EventHandler(this, &ChangePath::radio_button_Click);
			// 
			// cur_path_label
			// 
			this->cur_path_label->AutoSize = true;
			this->cur_path_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->cur_path_label->Location = System::Drawing::Point(12, 39);
			this->cur_path_label->Name = L"cur_path_label";
			this->cur_path_label->Size = System::Drawing::Size(146, 15);
			this->cur_path_label->TabIndex = 4;
			this->cur_path_label->Text = L"Текущий путь до файла:";
			// 
			// new_path_label
			// 
			this->new_path_label->AutoSize = true;
			this->new_path_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->new_path_label->Location = System::Drawing::Point(12, 146);
			this->new_path_label->Name = L"new_path_label";
			this->new_path_label->Size = System::Drawing::Size(169, 15);
			this->new_path_label->TabIndex = 5;
			this->new_path_label->Text = L"Полученный путь до файла:";
			// 
			// cur_path_textbox
			// 
			this->cur_path_textbox->Location = System::Drawing::Point(12, 59);
			this->cur_path_textbox->Name = L"cur_path_textbox";
			this->cur_path_textbox->ReadOnly = true;
			this->cur_path_textbox->Size = System::Drawing::Size(276, 20);
			this->cur_path_textbox->TabIndex = 6;
			// 
			// new_path_textbox
			// 
			this->new_path_textbox->Location = System::Drawing::Point(12, 164);
			this->new_path_textbox->Name = L"new_path_textbox";
			this->new_path_textbox->ReadOnly = true;
			this->new_path_textbox->Size = System::Drawing::Size(276, 20);
			this->new_path_textbox->TabIndex = 7;
			// 
			// copy_file_checkbox
			// 
			this->copy_file_checkbox->AutoSize = true;
			this->copy_file_checkbox->Location = System::Drawing::Point(12, 200);
			this->copy_file_checkbox->Name = L"copy_file_checkbox";
			this->copy_file_checkbox->Size = System::Drawing::Size(278, 17);
			this->copy_file_checkbox->TabIndex = 8;
			this->copy_file_checkbox->Text = L"Скопировать данные из текущего файла в новый";
			this->copy_file_checkbox->UseVisualStyleBackColor = true;
			// 
			// delete_file_checkbox
			// 
			this->delete_file_checkbox->AutoSize = true;
			this->delete_file_checkbox->Location = System::Drawing::Point(12, 223);
			this->delete_file_checkbox->Name = L"delete_file_checkbox";
			this->delete_file_checkbox->Size = System::Drawing::Size(144, 17);
			this->delete_file_checkbox->TabIndex = 9;
			this->delete_file_checkbox->Text = L"Удалить текущий файл";
			this->delete_file_checkbox->UseVisualStyleBackColor = true;
			// 
			// save_button
			// 
			this->save_button->Location = System::Drawing::Point(107, 246);
			this->save_button->Name = L"save_button";
			this->save_button->Size = System::Drawing::Size(92, 39);
			this->save_button->TabIndex = 10;
			this->save_button->Text = L"Сохранить";
			this->save_button->UseVisualStyleBackColor = true;
			this->save_button->Click += gcnew System::EventHandler(this, &ChangePath::save_button_Click);
			// 
			// ChangePath
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->ClientSize = System::Drawing::Size(300, 295);
			this->Controls->Add(this->save_button);
			this->Controls->Add(this->delete_file_checkbox);
			this->Controls->Add(this->copy_file_checkbox);
			this->Controls->Add(this->new_path_textbox);
			this->Controls->Add(this->cur_path_textbox);
			this->Controls->Add(this->new_path_label);
			this->Controls->Add(this->cur_path_label);
			this->Controls->Add(this->exist_file_radio);
			this->Controls->Add(this->new_file_radio);
			this->Controls->Add(this->changing_label);
			this->Controls->Add(this->choose_path_button);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"ChangePath";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Путь до файла";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void radio_button_Click(System::Object^ sender, System::EventArgs^ e) {
	// Меняем текст на кнопке в зависимости от radiobutton-ов
	if (this->new_file_radio->Checked) this->choose_path_button->Text = L"Создать";
	else this->choose_path_button->Text = L"Выбрать";
	this->new_path_textbox->Text = "";
}
private: System::Void choose_path_button_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ base_path = Application::StartupPath;  // Путь до .exe
	try {
		if (this->new_file_radio->Checked) {
			// Создать новый файл - используем SaveFileDialog
			SaveFileDialog^ saveDialog = gcnew SaveFileDialog();
			saveDialog->Title = L"Создать новый файл";
			saveDialog->Filter = L"CSV файлы (*.csv)|*.csv";
			saveDialog->DefaultExt = L"csv";
			saveDialog->AddExtension = true;
			if (saveDialog->ShowDialog(this) == System::Windows::Forms::DialogResult::OK) {
				this->new_path_textbox->Text = saveDialog->FileName->Replace(base_path + "\\", "");
			}
		}
		else {
			// Выбрать существующий файл - используем OpenFileDialog
			OpenFileDialog^ openDialog = gcnew OpenFileDialog();
			openDialog->Title = L"Выберите существующий CSV файл";
			openDialog->Filter = L"CSV файлы (*.csv)|*.csv";
			if (openDialog->ShowDialog(this) == System::Windows::Forms::DialogResult::OK) {
				this->new_path_textbox->Text = openDialog->FileName->Replace(base_path + "\\", "");
			}
		}
	}
	catch (Exception^ ex) {
		MessageBox::Show(this, L"Ошибка: " + ex->Message);
	}
}
private: System::Void save_button_Click(System::Object^ sender, System::EventArgs^ e) {
	if (this->new_path_textbox->Text == "") {
		MessageBox::Show(L"Нужно выбрать файл");
		return;
	}
	FILE* settings = fopen(DIR_NAME "/" CONF_NAME, "a+");
	if (!settings) {
		MessageBox::Show(L"Нет прав для изменения пути");
		return;
	}
	rewind(settings);

	// Получим путь до файла
	char new_file_path[FILE_NAME_LEN];
	copy_char_from_string(new_file_path, FILE_NAME_LEN, this->new_path_textbox->Text);

	// Создадим файл, если его нет
	if (this->new_file_radio->Checked) {
		FILE* new_file = fopen(new_file_path, "w");
		if (new_file == NULL) {
			MessageBox::Show(L"Нет прав для создания файла");
			return;
		}
		fclose(new_file);
	}

	// Заменим его в файле
	char password[PASSWORD_LEN];
	char old_file_path[FILE_NAME_LEN];
	if (fgets(password, PASSWORD_LEN, settings) == NULL) {  // Если файл пустой
		strcpy(password, "root");
		strcpy(old_file_path, DIR_NAME "/" FILE_NAME);
		fclose(settings);
	}
	else if (fgets(old_file_path, FILE_NAME_LEN, settings) == NULL) {  // Если в файле есть только пароль
		strcpy(old_file_path, DIR_NAME "/" FILE_NAME);
		fclose(settings);
	}
	else fclose(settings);
	settings = fopen(DIR_NAME "/" CONF_NAME, "w");
	// Сохраняем новый путь в файл
	fprintf(settings, "%s%s", password, new_file_path);
	fclose(settings);
	
	// Если нужно скопировать данные из старого файла в новый
	if (this->copy_file_checkbox->Checked) {
		FILE* new_file = fopen(new_file_path, "a");
		FILE* old_file = fopen(old_file_path, "r");
		if (old_file == NULL || new_file == NULL) {
			MessageBox::Show(L"Не получилось скопировать данные из файла"
				+ gcnew String(old_file_path) + L" в файл " + gcnew String(new_file_path));
		}
		else {
			char read_buffer[TEXT_LEN * FIELDS_NUM];
			while (fgets(read_buffer, TEXT_LEN * FIELDS_NUM, old_file) != NULL) {
				fputs(read_buffer, new_file);
			}
		}
		if (old_file != NULL) fclose(old_file);
		if (new_file != NULL) fclose(new_file);
	}
	// Если нужно удалить старый файл
	if (this->delete_file_checkbox->Checked) {
		remove(old_file_path);
	}
	this->Close();
}
};
}
