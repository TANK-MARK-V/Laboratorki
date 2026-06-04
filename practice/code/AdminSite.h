#pragma once

#include <stdio.h>

#include "SetFilters.h"
#include "AddFlight.h"
#include "EditFlights.h"
#include "DeleteFlights.h"
#include "ChangePath.h"

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
	/// Сводка для AdminSite
	/// </summary>
	public ref class AdminSite : public System::Windows::Forms::Form
	{
	public:
		AdminSite(void)
		{
			InitializeComponent();
			SetupDataBase();
			ReadDataBase();
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~AdminSite()
		{
			if (components)
			{
				delete components;
			}
			// Открываем главную форму
			for each (Form ^ form in Application::OpenForms) {
				if (form->GetType()->Name == "FlightMenu") {
					form->Show();
					break;
				}
			}
		}
	private: System::Windows::Forms::DataGridView^ data_base;
	private: System::Windows::Forms::Label^ mode_label;
	private: System::Windows::Forms::Button^ set_filters_button;
	private: System::Windows::Forms::Button^ add_flight_button;
	private: System::Windows::Forms::Button^ change_flights_button;
	private: System::Windows::Forms::Button^ delete_flights_button;
	private: System::Windows::Forms::Button^ change_path_button;
	private: System::Windows::Forms::Button^ exit_button;
	private: System::Windows::Forms::Button^ update_button;

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
			this->set_filters_button = (gcnew System::Windows::Forms::Button());
			this->add_flight_button = (gcnew System::Windows::Forms::Button());
			this->change_flights_button = (gcnew System::Windows::Forms::Button());
			this->delete_flights_button = (gcnew System::Windows::Forms::Button());
			this->change_path_button = (gcnew System::Windows::Forms::Button());
			this->exit_button = (gcnew System::Windows::Forms::Button());
			this->update_button = (gcnew System::Windows::Forms::Button());
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
			this->data_base->TabIndex = 0;
			// 
			// mode_label
			// 
			this->mode_label->AutoSize = true;
			this->mode_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->mode_label->Location = System::Drawing::Point(830, 9);
			this->mode_label->Name = L"mode_label";
			this->mode_label->Size = System::Drawing::Size(212, 20);
			this->mode_label->TabIndex = 1;
			this->mode_label->Text = L"Режим администратора";
			// 
			// set_filters_button
			// 
			this->set_filters_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->set_filters_button->Location = System::Drawing::Point(844, 81);
			this->set_filters_button->Name = L"set_filters_button";
			this->set_filters_button->Size = System::Drawing::Size(186, 33);
			this->set_filters_button->TabIndex = 2;
			this->set_filters_button->Text = L"Настроить фильтры";
			this->set_filters_button->UseVisualStyleBackColor = true;
			this->set_filters_button->Click += gcnew System::EventHandler(this, &AdminSite::set_filters_button_Click);
			// 
			// add_flight_button
			// 
			this->add_flight_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->add_flight_button->Location = System::Drawing::Point(844, 120);
			this->add_flight_button->Name = L"add_flight_button";
			this->add_flight_button->Size = System::Drawing::Size(186, 33);
			this->add_flight_button->TabIndex = 3;
			this->add_flight_button->Text = L"Добавить рейс";
			this->add_flight_button->UseVisualStyleBackColor = true;
			this->add_flight_button->Click += gcnew System::EventHandler(this, &AdminSite::add_flight_button_Click);
			// 
			// change_flights_button
			// 
			this->change_flights_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->change_flights_button->Location = System::Drawing::Point(844, 159);
			this->change_flights_button->Name = L"change_flights_button";
			this->change_flights_button->Size = System::Drawing::Size(186, 33);
			this->change_flights_button->TabIndex = 4;
			this->change_flights_button->Text = L"Изменение рейсов";
			this->change_flights_button->UseVisualStyleBackColor = true;
			this->change_flights_button->Click += gcnew System::EventHandler(this, &AdminSite::change_flights_button_Click);
			// 
			// delete_flights_button
			// 
			this->delete_flights_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->delete_flights_button->Location = System::Drawing::Point(844, 198);
			this->delete_flights_button->Name = L"delete_flights_button";
			this->delete_flights_button->Size = System::Drawing::Size(186, 33);
			this->delete_flights_button->TabIndex = 5;
			this->delete_flights_button->Text = L"Удаление рейсов";
			this->delete_flights_button->UseVisualStyleBackColor = true;
			this->delete_flights_button->Click += gcnew System::EventHandler(this, &AdminSite::delete_flights_button_Click);
			// 
			// change_path_button
			// 
			this->change_path_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->change_path_button->Location = System::Drawing::Point(844, 237);
			this->change_path_button->Name = L"change_path_button";
			this->change_path_button->Size = System::Drawing::Size(186, 33);
			this->change_path_button->TabIndex = 6;
			this->change_path_button->Text = L"Изменить путь до файла";
			this->change_path_button->UseVisualStyleBackColor = true;
			this->change_path_button->Click += gcnew System::EventHandler(this, &AdminSite::change_path_button_Click);
			// 
			// exit_button
			// 
			this->exit_button->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->exit_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->exit_button->Location = System::Drawing::Point(844, 276);
			this->exit_button->Name = L"exit_button";
			this->exit_button->Size = System::Drawing::Size(186, 33);
			this->exit_button->TabIndex = 7;
			this->exit_button->Text = L"Выйти в главное меню";
			this->exit_button->UseVisualStyleBackColor = false;
			this->exit_button->Click += gcnew System::EventHandler(this, &AdminSite::exit_button_Click);
			// 
			// update_button
			// 
			this->update_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->update_button->Location = System::Drawing::Point(844, 42);
			this->update_button->Name = L"update_button";
			this->update_button->Size = System::Drawing::Size(186, 33);
			this->update_button->TabIndex = 8;
			this->update_button->Text = L"Обновить таблицу";
			this->update_button->UseVisualStyleBackColor = true;
			this->update_button->Click += gcnew System::EventHandler(this, &AdminSite::update_button_Click);
			// 
			// AdminSite
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->ClientSize = System::Drawing::Size(1056, 524);
			this->Controls->Add(this->update_button);
			this->Controls->Add(this->exit_button);
			this->Controls->Add(this->change_path_button);
			this->Controls->Add(this->delete_flights_button);
			this->Controls->Add(this->change_flights_button);
			this->Controls->Add(this->add_flight_button);
			this->Controls->Add(this->set_filters_button);
			this->Controls->Add(this->mode_label);
			this->Controls->Add(this->data_base);
			this->MaximizeBox = false;
			this->Name = L"AdminSite";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Режим администратора";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->data_base))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: Void SetupDataBase() {
		this->data_base->Columns->Add("id", L"Номер\nзаписи");
		this->data_base->Columns->Add("fnum", L"Номер\nрейса");
		this->data_base->Columns->Add("name", L"Тип\nсамолёта");
		this->data_base->Columns->Add("dest", L"Пункт\nназначения");
		this->data_base->Columns->Add("days", L"Дни\nотправления");
		this->data_base->Columns->Add("dep_time", L"Время\nвылета");
		this->data_base->Columns->Add("arr_time", L"Время\nприлёта");
		this->data_base->Columns->Add("price", L"Цена\nбилета");
	}
	private: Void ReadDataBase() {
		// Очищаем БД
		this->data_base->Rows->Clear();

		char file_path[FILE_NAME_LEN];	// Название файла БД
		if (get_file(file_path) == -1) {
			MessageBox::Show(L"Не удалось открыть файл с информацией для чтения");
			return;
		}

		// Пробуем открыть, либо создаём
		FILE* table = fopen(file_path, "r");
		if (table == NULL) {
			table = fopen(file_path, "w");
			if (table == NULL) {
				MessageBox::Show(L"Не удалось открыть файл с БД");
				return;
			}
			fclose(table);
			table = fopen(file_path, "r");
		}

		// Читаем фильтры в массив
		Flight_filter filters[FILTERS_NUM];
		int fil_err;
		if (fil_err = read_filters(filters)) {
			MessageBox::Show(L"Не удалось открыть файл с фильтрами для чтения - ошибка " + fil_err);
			fclose(table);
			return;
		}

		// Считываем файл с БД
		Flight flight_buffer;	// Буфер для чтения
		int col_num;			// Сколько столбцов успешно прочитано
		int id = 0;				// Номер записи
		while ((col_num = read_line(table, &flight_buffer)) == FIELDS_NUM) {
			id++;
			if (!compare_flight(flight_buffer, filters)) continue;
			String^ str_dep_time = (flight_buffer.dep_time % 60).ToString();				// Получаем минуты dep_time
			if (str_dep_time->Length < 2) str_dep_time = "0" + str_dep_time;				// Дополняем до формата "ММ"
			str_dep_time = (flight_buffer.dep_time / 60).ToString() + ":" + str_dep_time;	// Получаем часы

			String^ str_arr_time = (flight_buffer.arr_time % 60).ToString();				// Получаем минуты arr_time
			if (str_arr_time->Length < 2) str_arr_time = "0" + str_arr_time;				// Дополняем до формата "ММ"
			str_arr_time = (flight_buffer.arr_time / 60).ToString() + ":" + str_arr_time;	// Получаем часы
			
			// Получаем дни отправления
			String^ str_days = "";
			if (flight_buffer.days[0] != 0)
				str_days += flight_buffer.days[0].ToString();
			for (int i = 1; i < 7 && flight_buffer.days[i]; i++)
				str_days += ", " + flight_buffer.days[i].ToString();

			this->data_base->Rows->Add(
				id,
				flight_buffer.fnum,
				gcnew String(flight_buffer.name),
				gcnew String(flight_buffer.dest),
				str_days,
				str_dep_time,
				str_arr_time,
				flight_buffer.price

			);
		}
		fclose(table);
	}
	public: System::Void set_filters_button_Click(System::Object^ sender, System::EventArgs^ e) {
		SetFilters^ p = gcnew SetFilters();
		p->ShowDialog();
		ReadDataBase();
	}
	private: System::Void add_flight_button_Click(System::Object^ sender, System::EventArgs^ e) {
		AddFlight^ p = gcnew AddFlight();
		p->ShowDialog();
		ReadDataBase();
	}
	private: System::Void change_flights_button_Click(System::Object^ sender, System::EventArgs^ e) {
		EditFlights^ p = gcnew EditFlights();
		p->ShowDialog();
		ReadDataBase();
	}
	private: System::Void delete_flights_button_Click(System::Object^ sender, System::EventArgs^ e) {
		DeleteFlights^ p = gcnew DeleteFlights();
		p->ShowDialog();
		ReadDataBase();
	}
	private: System::Void change_path_button_Click(System::Object^ sender, System::EventArgs^ e) {
		char file_path[FILE_NAME_LEN];
		if (get_file(file_path) == -1) {
			MessageBox::Show(L"Недостаточно прав");
			return;
		}
		ChangePath^ p = gcnew ChangePath();
		p->ShowDialog(this);
		ReadDataBase();
	}
	public: System::Void exit_button_Click(System::Object^ sender, System::EventArgs^ e) {
		for each (Form ^ form in Application::OpenForms) {
			if (form->GetType()->Name == "FlightMenu") {
				form->Show();
				break;
			}
		}
		this->Close();
	}
	public: System::Void update_button_Click(System::Object^ sender, System::EventArgs^ e) {
		ReadDataBase();
	}
	};
}
