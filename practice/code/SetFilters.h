#pragma once

#include "file_funcs.h"
#include "structure.h"

#include "EditFilterField.h"

#define NOT_IN_USE "не используется"

namespace MarkflightsUI {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для SetFilters
	/// </summary>
	public ref class SetFilters : public System::Windows::Forms::Form
	{
		array<String^>^ field_names;	// Названия полей
		array<String^>^ comp_ops;		// Операторы сравнения
		int cur_field;					// Какое поле нужно открыть дополнительно

	public:
		SetFilters(void)
		{
			InitializeComponent();
			// Скрываем часть для изменения конкретного фильтра
			this->ClientSize = System::Drawing::Size(440-16, 296);

			this->field_names = gcnew array<String^>{  // Заполняем названия полей
				L"номер рейса",
				L"тип самолёта",
				L"пункт назначения",
				L"дни отправления",
				L"время вылета",
				L"время прилёта",
				L"цена билета"
			};
			this->comp_ops = gcnew array<String^>{  // Заполняем операторы сравнения
				L">",
				L"<",
				L"=",
				L">=",
				L"<="
			};
			ReadFilters();
			this->cur_field = -1;
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~SetFilters()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ setting_label;
	private: System::Windows::Forms::Label^ fnum_use_label;
	private: System::Windows::Forms::Label^ name_use_label;
	private: System::Windows::Forms::Label^ dest_use_label;
	private: System::Windows::Forms::Label^ days_use_label;
	private: System::Windows::Forms::Label^ dep_time_use_label;
	private: System::Windows::Forms::Label^ arr_time_use_label;
	private: System::Windows::Forms::Label^ price_use_label;
	private: System::Windows::Forms::Button^ fnum_button;
	private: System::Windows::Forms::Button^ name_button;
	private: System::Windows::Forms::Button^ dest_button;
	private: System::Windows::Forms::Button^ days_button;
	private: System::Windows::Forms::Button^ dep_time_button;
	private: System::Windows::Forms::Button^ arr_time_button;
	private: System::Windows::Forms::Button^ price_button;
	private: System::Windows::Forms::Label^ hint_label;
	private: System::Windows::Forms::Button^ update_button;
	private: System::Windows::Forms::Label^ field_label;
	private: System::Windows::Forms::Label^ field_filter_1_label;
	private: System::Windows::Forms::Label^ num_1_label;
	private: System::Windows::Forms::Label^ num_2_label;
	private: System::Windows::Forms::Label^ field_filter_2_label;
	private: System::Windows::Forms::Button^ field_filter_1_delete_button;
	private: System::Windows::Forms::Button^ field_filter_1_edit_button;
	private: System::Windows::Forms::Button^ field_filter_2_delete_button;
	private: System::Windows::Forms::Button^ field_filter_2_edit_button;
	private: System::Windows::Forms::Button^ add_new_filter_button;
	private: System::Windows::Forms::Button^ delete_all_filters_button;
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
			this->setting_label = (gcnew System::Windows::Forms::Label());
			this->fnum_use_label = (gcnew System::Windows::Forms::Label());
			this->name_use_label = (gcnew System::Windows::Forms::Label());
			this->dest_use_label = (gcnew System::Windows::Forms::Label());
			this->days_use_label = (gcnew System::Windows::Forms::Label());
			this->dep_time_use_label = (gcnew System::Windows::Forms::Label());
			this->arr_time_use_label = (gcnew System::Windows::Forms::Label());
			this->price_use_label = (gcnew System::Windows::Forms::Label());
			this->fnum_button = (gcnew System::Windows::Forms::Button());
			this->name_button = (gcnew System::Windows::Forms::Button());
			this->dest_button = (gcnew System::Windows::Forms::Button());
			this->days_button = (gcnew System::Windows::Forms::Button());
			this->dep_time_button = (gcnew System::Windows::Forms::Button());
			this->arr_time_button = (gcnew System::Windows::Forms::Button());
			this->price_button = (gcnew System::Windows::Forms::Button());
			this->hint_label = (gcnew System::Windows::Forms::Label());
			this->update_button = (gcnew System::Windows::Forms::Button());
			this->field_label = (gcnew System::Windows::Forms::Label());
			this->field_filter_1_label = (gcnew System::Windows::Forms::Label());
			this->num_1_label = (gcnew System::Windows::Forms::Label());
			this->num_2_label = (gcnew System::Windows::Forms::Label());
			this->field_filter_2_label = (gcnew System::Windows::Forms::Label());
			this->field_filter_1_delete_button = (gcnew System::Windows::Forms::Button());
			this->field_filter_1_edit_button = (gcnew System::Windows::Forms::Button());
			this->field_filter_2_delete_button = (gcnew System::Windows::Forms::Button());
			this->field_filter_2_edit_button = (gcnew System::Windows::Forms::Button());
			this->add_new_filter_button = (gcnew System::Windows::Forms::Button());
			this->delete_all_filters_button = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// setting_label
			// 
			this->setting_label->AutoSize = true;
			this->setting_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->setting_label->Location = System::Drawing::Point(139, 9);
			this->setting_label->Name = L"setting_label";
			this->setting_label->Size = System::Drawing::Size(192, 20);
			this->setting_label->TabIndex = 1;
			this->setting_label->Text = L"Настройка фильтров";
			// 
			// fnum_use_label
			// 
			this->fnum_use_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->fnum_use_label->Location = System::Drawing::Point(178, 62);
			this->fnum_use_label->Name = L"fnum_use_label";
			this->fnum_use_label->Size = System::Drawing::Size(232, 17);
			this->fnum_use_label->TabIndex = 34;
			this->fnum_use_label->Text = L"не используется";
			// 
			// name_use_label
			// 
			this->name_use_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->name_use_label->Location = System::Drawing::Point(178, 91);
			this->name_use_label->Name = L"name_use_label";
			this->name_use_label->Size = System::Drawing::Size(232, 17);
			this->name_use_label->TabIndex = 35;
			this->name_use_label->Text = L"не используется";
			// 
			// dest_use_label
			// 
			this->dest_use_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->dest_use_label->Location = System::Drawing::Point(177, 120);
			this->dest_use_label->Name = L"dest_use_label";
			this->dest_use_label->Size = System::Drawing::Size(233, 17);
			this->dest_use_label->TabIndex = 36;
			this->dest_use_label->Text = L"не используется";
			// 
			// days_use_label
			// 
			this->days_use_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->days_use_label->Location = System::Drawing::Point(177, 149);
			this->days_use_label->Name = L"days_use_label";
			this->days_use_label->Size = System::Drawing::Size(233, 17);
			this->days_use_label->TabIndex = 37;
			this->days_use_label->Text = L"не используется";
			// 
			// dep_time_use_label
			// 
			this->dep_time_use_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->dep_time_use_label->Location = System::Drawing::Point(177, 178);
			this->dep_time_use_label->Name = L"dep_time_use_label";
			this->dep_time_use_label->Size = System::Drawing::Size(233, 17);
			this->dep_time_use_label->TabIndex = 38;
			this->dep_time_use_label->Text = L"не используется";
			// 
			// arr_time_use_label
			// 
			this->arr_time_use_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->arr_time_use_label->Location = System::Drawing::Point(177, 207);
			this->arr_time_use_label->Name = L"arr_time_use_label";
			this->arr_time_use_label->Size = System::Drawing::Size(233, 17);
			this->arr_time_use_label->TabIndex = 39;
			this->arr_time_use_label->Text = L"не используется";
			// 
			// price_use_label
			// 
			this->price_use_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->price_use_label->Location = System::Drawing::Point(177, 236);
			this->price_use_label->Name = L"price_use_label";
			this->price_use_label->Size = System::Drawing::Size(233, 17);
			this->price_use_label->TabIndex = 40;
			this->price_use_label->Text = L"не используется";
			// 
			// fnum_button
			// 
			this->fnum_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->fnum_button->Location = System::Drawing::Point(12, 59);
			this->fnum_button->Name = L"fnum_button";
			this->fnum_button->Size = System::Drawing::Size(159, 23);
			this->fnum_button->TabIndex = 41;
			this->fnum_button->Text = L"Номер рейса";
			this->fnum_button->UseVisualStyleBackColor = true;
			this->fnum_button->Click += gcnew System::EventHandler(this, &SetFilters::fnum_button_Click);
			// 
			// name_button
			// 
			this->name_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->name_button->Location = System::Drawing::Point(12, 88);
			this->name_button->Name = L"name_button";
			this->name_button->Size = System::Drawing::Size(159, 23);
			this->name_button->TabIndex = 42;
			this->name_button->Text = L"Тип самолёта";
			this->name_button->UseVisualStyleBackColor = true;
			this->name_button->Click += gcnew System::EventHandler(this, &SetFilters::name_button_Click);
			// 
			// dest_button
			// 
			this->dest_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->dest_button->Location = System::Drawing::Point(12, 117);
			this->dest_button->Name = L"dest_button";
			this->dest_button->Size = System::Drawing::Size(159, 23);
			this->dest_button->TabIndex = 43;
			this->dest_button->Text = L"Пункт назначения";
			this->dest_button->UseVisualStyleBackColor = true;
			this->dest_button->Click += gcnew System::EventHandler(this, &SetFilters::dest_button_Click);
			// 
			// days_button
			// 
			this->days_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->days_button->Location = System::Drawing::Point(12, 146);
			this->days_button->Name = L"days_button";
			this->days_button->Size = System::Drawing::Size(159, 23);
			this->days_button->TabIndex = 44;
			this->days_button->Text = L"Дни отправления";
			this->days_button->UseVisualStyleBackColor = true;
			this->days_button->Click += gcnew System::EventHandler(this, &SetFilters::days_button_Click);
			// 
			// dep_time_button
			// 
			this->dep_time_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->dep_time_button->Location = System::Drawing::Point(12, 175);
			this->dep_time_button->Name = L"dep_time_button";
			this->dep_time_button->Size = System::Drawing::Size(159, 23);
			this->dep_time_button->TabIndex = 45;
			this->dep_time_button->Text = L"Время вылета";
			this->dep_time_button->UseVisualStyleBackColor = true;
			this->dep_time_button->Click += gcnew System::EventHandler(this, &SetFilters::dep_time_button_Click);
			// 
			// arr_time_button
			// 
			this->arr_time_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->arr_time_button->Location = System::Drawing::Point(12, 204);
			this->arr_time_button->Name = L"arr_time_button";
			this->arr_time_button->Size = System::Drawing::Size(159, 23);
			this->arr_time_button->TabIndex = 46;
			this->arr_time_button->Text = L"Время прилёта";
			this->arr_time_button->UseVisualStyleBackColor = true;
			this->arr_time_button->Click += gcnew System::EventHandler(this, &SetFilters::arr_time_button_Click);
			// 
			// price_button
			// 
			this->price_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->price_button->Location = System::Drawing::Point(12, 233);
			this->price_button->Name = L"price_button";
			this->price_button->Size = System::Drawing::Size(159, 23);
			this->price_button->TabIndex = 47;
			this->price_button->Text = L"Цена билета";
			this->price_button->UseVisualStyleBackColor = true;
			this->price_button->Click += gcnew System::EventHandler(this, &SetFilters::price_button_Click);
			// 
			// hint_label
			// 
			this->hint_label->AutoSize = true;
			this->hint_label->Location = System::Drawing::Point(67, 29);
			this->hint_label->Name = L"hint_label";
			this->hint_label->Size = System::Drawing::Size(322, 13);
			this->hint_label->TabIndex = 48;
			this->hint_label->Text = L"Нажмите на название поля, чтобы редактировать его фильтр";
			// 
			// update_button
			// 
			this->update_button->Location = System::Drawing::Point(155, 262);
			this->update_button->Name = L"update_button";
			this->update_button->Size = System::Drawing::Size(165, 23);
			this->update_button->TabIndex = 49;
			this->update_button->Text = L"Обновить список";
			this->update_button->UseVisualStyleBackColor = true;
			this->update_button->Click += gcnew System::EventHandler(this, &SetFilters::update_button_Click);
			// 
			// field_label
			// 
			this->field_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->field_label->Location = System::Drawing::Point(427, 9);
			this->field_label->Name = L"field_label";
			this->field_label->Size = System::Drawing::Size(345, 17);
			this->field_label->TabIndex = 50;
			this->field_label->Text = L"Поле \"номер рейса\"";
			this->field_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// field_filter_1_label
			// 
			this->field_filter_1_label->AutoSize = true;
			this->field_filter_1_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->field_filter_1_label->Location = System::Drawing::Point(456, 35);
			this->field_filter_1_label->Name = L"field_filter_1_label";
			this->field_filter_1_label->Size = System::Drawing::Size(118, 17);
			this->field_filter_1_label->TabIndex = 51;
			this->field_filter_1_label->Text = L"не используется";
			// 
			// num_1_label
			// 
			this->num_1_label->AutoSize = true;
			this->num_1_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->num_1_label->Location = System::Drawing::Point(427, 35);
			this->num_1_label->Name = L"num_1_label";
			this->num_1_label->Size = System::Drawing::Size(30, 17);
			this->num_1_label->TabIndex = 52;
			this->num_1_label->Text = L"1) -";
			// 
			// num_2_label
			// 
			this->num_2_label->AutoSize = true;
			this->num_2_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->num_2_label->Location = System::Drawing::Point(427, 59);
			this->num_2_label->Name = L"num_2_label";
			this->num_2_label->Size = System::Drawing::Size(30, 17);
			this->num_2_label->TabIndex = 54;
			this->num_2_label->Text = L"2) -";
			// 
			// field_filter_2_label
			// 
			this->field_filter_2_label->AutoSize = true;
			this->field_filter_2_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->field_filter_2_label->Location = System::Drawing::Point(456, 59);
			this->field_filter_2_label->Name = L"field_filter_2_label";
			this->field_filter_2_label->Size = System::Drawing::Size(118, 17);
			this->field_filter_2_label->TabIndex = 53;
			this->field_filter_2_label->Text = L"не используется";
			// 
			// field_filter_1_delete_button
			// 
			this->field_filter_1_delete_button->Location = System::Drawing::Point(580, 32);
			this->field_filter_1_delete_button->Name = L"field_filter_1_delete_button";
			this->field_filter_1_delete_button->Size = System::Drawing::Size(75, 23);
			this->field_filter_1_delete_button->TabIndex = 55;
			this->field_filter_1_delete_button->Text = L"Удалить";
			this->field_filter_1_delete_button->UseVisualStyleBackColor = true;
			this->field_filter_1_delete_button->Click += gcnew System::EventHandler(this, &SetFilters::field_filter_1_delete_button_Click);
			// 
			// field_filter_1_edit_button
			// 
			this->field_filter_1_edit_button->Location = System::Drawing::Point(661, 32);
			this->field_filter_1_edit_button->Name = L"field_filter_1_edit_button";
			this->field_filter_1_edit_button->Size = System::Drawing::Size(102, 23);
			this->field_filter_1_edit_button->TabIndex = 56;
			this->field_filter_1_edit_button->Text = L"Редактировать";
			this->field_filter_1_edit_button->UseVisualStyleBackColor = true;
			this->field_filter_1_edit_button->Click += gcnew System::EventHandler(this, &SetFilters::field_filter_1_edit_button_Click);
			// 
			// field_filter_2_delete_button
			// 
			this->field_filter_2_delete_button->Location = System::Drawing::Point(580, 56);
			this->field_filter_2_delete_button->Name = L"field_filter_2_delete_button";
			this->field_filter_2_delete_button->Size = System::Drawing::Size(75, 23);
			this->field_filter_2_delete_button->TabIndex = 57;
			this->field_filter_2_delete_button->Text = L"Удалить";
			this->field_filter_2_delete_button->UseVisualStyleBackColor = true;
			this->field_filter_2_delete_button->Click += gcnew System::EventHandler(this, &SetFilters::field_filter_2_delete_button_Click);
			// 
			// field_filter_2_edit_button
			// 
			this->field_filter_2_edit_button->Location = System::Drawing::Point(661, 56);
			this->field_filter_2_edit_button->Name = L"field_filter_2_edit_button";
			this->field_filter_2_edit_button->Size = System::Drawing::Size(102, 23);
			this->field_filter_2_edit_button->TabIndex = 58;
			this->field_filter_2_edit_button->Text = L"Редактировать";
			this->field_filter_2_edit_button->UseVisualStyleBackColor = true;
			this->field_filter_2_edit_button->Click += gcnew System::EventHandler(this, &SetFilters::field_filter_2_edit_button_Click);
			// 
			// add_new_filter_button
			// 
			this->add_new_filter_button->Location = System::Drawing::Point(438, 91);
			this->add_new_filter_button->Name = L"add_new_filter_button";
			this->add_new_filter_button->Size = System::Drawing::Size(149, 32);
			this->add_new_filter_button->TabIndex = 59;
			this->add_new_filter_button->Text = L"Добавить новый фильтр";
			this->add_new_filter_button->UseVisualStyleBackColor = true;
			this->add_new_filter_button->Click += gcnew System::EventHandler(this, &SetFilters::add_new_filter_button_Click);
			// 
			// delete_all_filters_button
			// 
			this->delete_all_filters_button->Location = System::Drawing::Point(607, 91);
			this->delete_all_filters_button->Name = L"delete_all_filters_button";
			this->delete_all_filters_button->Size = System::Drawing::Size(151, 32);
			this->delete_all_filters_button->TabIndex = 60;
			this->delete_all_filters_button->Text = L"Удалить все фильтры";
			this->delete_all_filters_button->UseVisualStyleBackColor = true;
			this->delete_all_filters_button->Click += gcnew System::EventHandler(this, &SetFilters::delete_all_filters_button_Click);
			// 
			// SetFilters
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->ClientSize = System::Drawing::Size(784, 296);
			this->Controls->Add(this->delete_all_filters_button);
			this->Controls->Add(this->add_new_filter_button);
			this->Controls->Add(this->field_filter_2_edit_button);
			this->Controls->Add(this->field_filter_2_delete_button);
			this->Controls->Add(this->field_filter_1_edit_button);
			this->Controls->Add(this->field_filter_1_delete_button);
			this->Controls->Add(this->num_2_label);
			this->Controls->Add(this->field_filter_2_label);
			this->Controls->Add(this->num_1_label);
			this->Controls->Add(this->field_filter_1_label);
			this->Controls->Add(this->field_label);
			this->Controls->Add(this->update_button);
			this->Controls->Add(this->hint_label);
			this->Controls->Add(this->price_button);
			this->Controls->Add(this->arr_time_button);
			this->Controls->Add(this->dep_time_button);
			this->Controls->Add(this->days_button);
			this->Controls->Add(this->dest_button);
			this->Controls->Add(this->name_button);
			this->Controls->Add(this->fnum_button);
			this->Controls->Add(this->price_use_label);
			this->Controls->Add(this->arr_time_use_label);
			this->Controls->Add(this->dep_time_use_label);
			this->Controls->Add(this->days_use_label);
			this->Controls->Add(this->dest_use_label);
			this->Controls->Add(this->name_use_label);
			this->Controls->Add(this->fnum_use_label);
			this->Controls->Add(this->setting_label);
			this->MaximizeBox = false;
			this->Name = L"SetFilters";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Настройка фильтров";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void ReadFilters() {
	Flight_filter filters[FILTERS_NUM];
	// Обнуляем поля
	this->fnum_use_label->Text = "";
	this->name_use_label->Text = "";
	this->dest_use_label->Text = "";
	this->days_use_label->Text = "";
	this->dep_time_use_label->Text = "";
	this->arr_time_use_label->Text = "";
	this->price_use_label->Text = "";
	if (read_filters(filters)) {
		MessageBox::Show(L"Не удалось открыть файл с фильтрами для чтения");
		return;
	}
	for (int f = 0; f < FILTERS_NUM; f++) {
		// Поле fnum
		if (filters[f].apply[0]) {
			if (this->fnum_use_label->Text != "")
				if (filters[f].logic[0] == 0) this->fnum_use_label->Text += " && ";
				else this->fnum_use_label->Text += " || ";
			this->fnum_use_label->Text += filters[f].fnum;
		}
		// Поле name
		if (filters[f].apply[1]) {
			if (this->name_use_label->Text != "")
				if (filters[f].logic[1] == 0) this->name_use_label->Text += " && ";
				else this->name_use_label->Text += " || ";
			this->name_use_label->Text += gcnew String(filters[f].name);
		}
		// Поле dest
		if (filters[f].apply[2]) {
			if (this->dest_use_label->Text != "")
				if (filters[f].logic[2] == 0) this->dest_use_label->Text += " && ";
				else this->dest_use_label->Text += " || ";
			this->dest_use_label->Text += gcnew String(filters[f].dest);
		}
		// Поле days
		if (filters[f].apply[3]) {
			if (this->days_use_label->Text != "")
				if (filters[f].logic[3] == 0) this->days_use_label->Text += " && ";
				else this->days_use_label->Text += " || ";
			this->days_use_label->Text += filters[f].days[0];
			for (int i = 1; i < 7 && filters[f].days[i]; i++)
				this->days_use_label->Text += ", " + filters[f].days[i];
		}
		// Поле dep_time
		if (filters[f].apply[4]) {
			if (this->dep_time_use_label->Text != "")
				if (filters[f].logic[4] == 0) this->dep_time_use_label->Text += " && ";
				else this->dep_time_use_label->Text += " || ";
			this->dep_time_use_label->Text += this->comp_ops[filters[f].apply[4] - 1];
			this->dep_time_use_label->Text += filters[f].dep_time / 60 + ":";
			this->dep_time_use_label->Text += filters[f].dep_time % 60 / 10;
			this->dep_time_use_label->Text += filters[f].dep_time % 60 % 10;
		}
		// Поле arr_time
		if (filters[f].apply[5]) {
			if (this->arr_time_use_label->Text != "")
				if (filters[f].logic[5] == 0) this->arr_time_use_label->Text += " && ";
				else this->arr_time_use_label->Text += " || ";
			this->arr_time_use_label->Text += this->comp_ops[filters[f].apply[5] - 1];
			this->arr_time_use_label->Text += filters[f].arr_time / 60 + ":";
			this->arr_time_use_label->Text += filters[f].arr_time % 60 / 10;
			this->arr_time_use_label->Text += filters[f].arr_time % 60 % 10;
		}
		// Поле price
		if (filters[f].apply[6]) {
			if (this->price_use_label->Text != "")
				if (filters[f].logic[6] == 0) this->price_use_label->Text += " && ";
				else this->price_use_label->Text += " || ";
			this->price_use_label->Text += filters[f].price;
		}
	}
	// Если поля пустые, то ставим NOT_IN_USE
	if (this->fnum_use_label->Text == "") this->fnum_use_label->Text = NOT_IN_USE;
	if (this->name_use_label->Text == "") this->name_use_label->Text = NOT_IN_USE;
	if (this->dest_use_label->Text == "") this->dest_use_label->Text = NOT_IN_USE;
	if (this->days_use_label->Text == "") this->days_use_label->Text = NOT_IN_USE;
	if (this->dep_time_use_label->Text == "") this->dep_time_use_label->Text = NOT_IN_USE;
	if (this->arr_time_use_label->Text == "") this->arr_time_use_label->Text = NOT_IN_USE;
	if (this->price_use_label->Text == "") this->price_use_label->Text = NOT_IN_USE;
}
private: System::Void filter_field_show() {
	int n = this->cur_field;
	if (n == -1) return;
	// Читаем фильтры в массив
	Flight_filter filters[FILTERS_NUM];
	if (read_filters(filters)) return;
	// Открываем скрытую часть
	this->ClientSize = System::Drawing::Size(784, 296);
	this->field_label->Text = "Поле " + this->field_names[n];
	// Обнуляем поля
	this->field_filter_1_label->Text = "";
	this->field_filter_2_label->Text = "";
	// Открываем кнопки для всех полей
	this->field_filter_1_delete_button->Enabled = 1;
	this->field_filter_1_edit_button->Enabled = 1;
	this->field_filter_2_delete_button->Enabled = 1;
	this->field_filter_2_edit_button->Enabled = 1;
	this->add_new_filter_button->Enabled = 1;
	this->delete_all_filters_button->Enabled = 1;
	// Создаём массив строчек для удобства работы
	array<String^>^ labels = gcnew array<String^>{"", ""};
	int working_filters = 0;  // Счётчик рабочих фильтров
	for (int f = 0; f < FILTERS_NUM; f++)
		if (filters[f].apply[n]) {
			working_filters++;
			if (n == 0) labels[f] += filters[f].fnum;
			else if (n == 1) labels[f] += gcnew String(filters[f].name);
			else if (n == 2) labels[f] += gcnew String(filters[f].dest);
			else if (n == 3) {
				labels[f] += filters[f].days[0];
				for (int i = 1; i < 7 && filters[f].days[i]; i++)
					labels[f] += ", " + filters[f].days[i];
			}
			else if (n == 4) {
				labels[f] += this->comp_ops[filters[f].apply[n] - 1];
				labels[f] += filters[f].dep_time / 60 + ":";
				labels[f] += filters[f].dep_time % 60 / 10;
				labels[f] += filters[f].dep_time % 60 % 10;
			}
			else if (n == 5) {
				labels[f] += this->comp_ops[filters[f].apply[n] - 1];
				labels[f] += filters[f].arr_time / 60 + ":";
				labels[f] += filters[f].arr_time % 60 / 10;
				labels[f] += filters[f].arr_time % 60 % 10;
			}
			else if (n == 6) labels[f] += filters[f].price;

			if (f > 0)  // Проставим логические операции
				if (filters[f].logic[n] == 0) labels[f] = "&& " + labels[f];
				else labels[f] = "|| " + labels[f];
		}
		else {
			labels[f] += NOT_IN_USE;
			// Блокируем кнопки
			if (f == 0) {
				this->field_filter_1_delete_button->Enabled = 0;
				this->field_filter_1_edit_button->Enabled = 0;
			}
			else {
				this->field_filter_2_delete_button->Enabled = 0;
				this->field_filter_2_edit_button->Enabled = 0;
			}
		}
	this->field_filter_1_label->Text = labels[0];
	this->field_filter_2_label->Text = labels[1];
	// Теперь определим, будут ли доступны общие кнопки
	if (working_filters == FILTERS_NUM) this->add_new_filter_button->Enabled = 0;
	if (working_filters == 0) this->delete_all_filters_button->Enabled = 0;
}
private: System::Void fnum_button_Click(System::Object^ sender, System::EventArgs^ e) {
	this->cur_field = 0;
	filter_field_show();
}
private: System::Void name_button_Click(System::Object^ sender, System::EventArgs^ e) {
	this->cur_field = 1;
	filter_field_show();
}
private: System::Void dest_button_Click(System::Object^ sender, System::EventArgs^ e) {
	this->cur_field = 2;
	filter_field_show();

}
private: System::Void days_button_Click(System::Object^ sender, System::EventArgs^ e) {
	this->cur_field = 3;
	filter_field_show();
}
private: System::Void dep_time_button_Click(System::Object^ sender, System::EventArgs^ e) {
	this->cur_field = 4;
	filter_field_show();
}
private: System::Void arr_time_button_Click(System::Object^ sender, System::EventArgs^ e) {
	this->cur_field = 5;
	filter_field_show();
}
private: System::Void price_button_Click(System::Object^ sender, System::EventArgs^ e) {
	this->cur_field = 6;
	filter_field_show();
}
private: System::Void update_button_Click(System::Object^ sender, System::EventArgs^ e) {
	ReadFilters();
	filter_field_show();
}
private: System::Void field_filter_1_delete_button_Click(System::Object^ sender, System::EventArgs^ e) {
	// Читаем фильтры в массив
	Flight_filter filters[FILTERS_NUM];
	if (read_filters(filters)) {
		MessageBox::Show(L"Не удалось открыть файл для чтения");
		return;
	}
	filters[0].apply[this->cur_field] = 0;
	if (write_filters(filters)) {
		MessageBox::Show(L"Не удалось открыть файл для записи");
		return;
	}
	ReadFilters();
	filter_field_show();
}
private: System::Void field_filter_1_edit_button_Click(System::Object^ sender, System::EventArgs^ e) {
	EditFilterField^ p = gcnew EditFilterField(0, this->cur_field);
	p->ShowDialog();
	ReadFilters();
	filter_field_show();
}
private: System::Void field_filter_2_delete_button_Click(System::Object^ sender, System::EventArgs^ e) {
	// Читаем фильтры в массив
	Flight_filter filters[FILTERS_NUM];
	if (read_filters(filters)) {
		MessageBox::Show(L"Не удалось открыть файл с фильтрами для чтения");
		return;
	}
	filters[1].apply[this->cur_field] = 0;
	if (write_filters(filters)) {
		MessageBox::Show(L"Не удалось открыть файл с фильтрами для записи");
		return;
	}
	ReadFilters();
	filter_field_show();
}
private: System::Void field_filter_2_edit_button_Click(System::Object^ sender, System::EventArgs^ e) {
	EditFilterField^ p = gcnew EditFilterField(1, this->cur_field);
	p->ShowDialog();
	ReadFilters();
	filter_field_show();
}
private: System::Void add_new_filter_button_Click(System::Object^ sender, System::EventArgs^ e) {
	// Читаем фильтры в массив
	Flight_filter filters[FILTERS_NUM];
	if (read_filters(filters)) {
		MessageBox::Show(L"Не удалось открыть файл с фильтрами для чтения");
		return;
	}
	int free_filter = -1;  // Индекс свободного фильтра
	for (int f = 0; f < FILTERS_NUM && free_filter == -1; f++)
		if (filters[f].apply[this->cur_field] == 0)
			free_filter = f;
	if (free_filter == -1) {
		MessageBox::Show(L"ОШИБКА: Больше нет неиспользуемых полей");
		return;
	}
	EditFilterField^ p = gcnew EditFilterField(free_filter, this->cur_field);
	p->ShowDialog();
	ReadFilters();
	filter_field_show();
}
private: System::Void delete_all_filters_button_Click(System::Object^ sender, System::EventArgs^ e) {
	// Читаем фильтры в массив
	Flight_filter filters[FILTERS_NUM];
	if (read_filters(filters)) {
		MessageBox::Show(L"Не удалось открыть файл с фильтрами для чтения");
		return;
	}
	for (int f = 0; f < FILTERS_NUM; f++) filters[f].apply[this->cur_field] = 0;
	if (write_filters(filters)) {
		MessageBox::Show(L"Не удалось открыть файл с фильтрами для записи");
		return;
	}
	ReadFilters();
	this->ClientSize = System::Drawing::Size(440 - 16, 296);
	this->cur_field = -1;
}
};
}