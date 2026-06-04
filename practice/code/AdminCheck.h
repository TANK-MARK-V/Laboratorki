#pragma once

#include "AdminSite.h"
#include "file_funcs.h"

namespace MarkflightsUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для AdminCheck
	/// </summary>
	public ref class AdminCheck : public System::Windows::Forms::Form
	{
	public:
		AdminCheck(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~AdminCheck()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ enter_label;
	private: System::Windows::Forms::TextBox^ password_box;
	private: System::Windows::Forms::Button^ conf_button;
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
			this->enter_label = (gcnew System::Windows::Forms::Label());
			this->password_box = (gcnew System::Windows::Forms::TextBox());
			this->conf_button = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// enter_label
			// 
			this->enter_label->AutoSize = true;
			this->enter_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->enter_label->Location = System::Drawing::Point(12, 9);
			this->enter_label->Name = L"enter_label";
			this->enter_label->Size = System::Drawing::Size(154, 20);
			this->enter_label->TabIndex = 0;
			this->enter_label->Text = L"Введите пароль:";
			// 
			// password_box
			// 
			this->password_box->Location = System::Drawing::Point(16, 32);
			this->password_box->Name = L"password_box";
			this->password_box->Size = System::Drawing::Size(150, 20);
			this->password_box->TabIndex = 1;
			// 
			// conf_button
			// 
			this->conf_button->Location = System::Drawing::Point(16, 58);
			this->conf_button->Name = L"conf_button";
			this->conf_button->Size = System::Drawing::Size(150, 23);
			this->conf_button->TabIndex = 2;
			this->conf_button->Text = L"Войти";
			this->conf_button->UseVisualStyleBackColor = true;
			this->conf_button->Click += gcnew System::EventHandler(this, &AdminCheck::conf_button_Click);
			// 
			// AdminCheck
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->ClientSize = System::Drawing::Size(185, 92);
			this->Controls->Add(this->conf_button);
			this->Controls->Add(this->password_box);
			this->Controls->Add(this->enter_label);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"AdminCheck";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Подтверждение";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void conf_button_Click(System::Object^ sender, System::EventArgs^ e) {
		char password[PASSWORD_LEN];
		get_password(password, PASSWORD_LEN);
		if (this->password_box->Text != gcnew String(password)) {
			MessageBox::Show(L"Неверный пароль");
			return;
		}
		AdminSite^ p = gcnew AdminSite();
		p->Show();
		this->Close();
		for each (Form ^ form in Application::OpenForms) {
			if (form->GetType()->Name == "FlightMenu") {
				form->Hide();
				break;
			}
		}
	}
	};
}
