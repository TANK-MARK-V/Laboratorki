#pragma once

#include <fstream>
#include <ctime>


namespace MarkflightsUI {
    using namespace System;
    using namespace System::IO;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;
    using namespace System::Media;

    public ref class TheZondbie : public System::Windows::Forms::Form
    {
    private:
        // Игровые объекты
        List<PictureBox^>^ zondbies;
        Timer^ game_timer;
        Timer^ spawn_timer;
        Timer^ animation_timer;
        Timer^ world_time;

        // Состояние игры
        int bullets_left;       // Осталось пуль (0-2)
        int is_gun_open;        // Открыто ли ружьё
        int best_score;         // Лучший результат
        float zondbie_speed;    // Текущая скорость зомби
        int animation_frame;    // Кадр анимации (1 или 2)
        int time_passed;        // Сколько времени прошло

        // Элементы UI
        PictureBox^ zondbieBox;

        // Константы
        static const int ZONDBIE_SIZE_X = 61;
        static const int ZONDBIE_SIZE_Y = 111;
        static const int MAX_BULLETS = 2;
        static const float BASE_SPEED = 2.0f;

        // Путь к файлу рекордов
        String^ best_score_file;
        
        // Звуки
        SoundPlayer^ shoot_sound;
        SoundPlayer^ open_Peet_sound;
        SoundPlayer^ new_bullet_sound;
        SoundPlayer^ zondbie_death_sound;
        SoundPlayer^ game_over_sound;

    public:
        TheZondbie(void)
        {
            InitializeComponent();
            InitializeGame();
        }

    protected:
        ~TheZondbie()
        {
            if (components)
            {
                delete components;
            }
            game_timer->Stop();
            spawn_timer->Stop();
            animation_timer->Stop();
            world_time->Stop();
            // Проигрываем звук проигрыша
            try {
                game_over_sound->Play();
            }
            catch (...) {}
            // Последнее сообщение
            MessageBox::Show("Вы держались как могли...");
            // Пробуем записать результат игры
            int best = 0;
            try {
                if (File::Exists("game_data/score.txt")) {
                    StreamReader^ reader = gcnew StreamReader("game_data/score.txt");
                    best = Convert::ToInt32(reader->ReadLine());
                    reader->Close();
                }

            }
            catch (...) {}
            if (best < time_passed) {
                try {
                    StreamWriter^ writer = gcnew StreamWriter("game_data/score.txt");
                    writer->WriteLine(time_passed);
                    writer->Close();
                }
                catch (Exception^ ex) {
                    MessageBox::Show(L"Ошибка сохранения: " + ex->Message);
                }
            }
            // Показываем стартовую форму при закрытии
            for each (Form ^ form in Application::OpenForms) {
                if (form->GetType()->Name == "StartGame") {
                    form->Show();
                    break;
                }
            }
        }

    private: System::Windows::Forms::PictureBox^ street_box;
    private: System::Windows::Forms::PictureBox^ Peet_closed_box;
    private: System::Windows::Forms::PictureBox^ Peet_open_box;
    private: System::Windows::Forms::PictureBox^ bullet_ready_left_box;
    private: System::Windows::Forms::PictureBox^ bullet_ready_right_box;
    private: System::Windows::Forms::PictureBox^ bullet_done_left_box;
    private: System::Windows::Forms::PictureBox^ bullet_done_right_box;
    private: System::Windows::Forms::Label^ time_word_label;
    private: System::Windows::Forms::Label^ time_label;
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
            System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(TheZondbie::typeid));
            this->street_box = (gcnew System::Windows::Forms::PictureBox());
            this->Peet_closed_box = (gcnew System::Windows::Forms::PictureBox());
            this->Peet_open_box = (gcnew System::Windows::Forms::PictureBox());
            this->bullet_ready_left_box = (gcnew System::Windows::Forms::PictureBox());
            this->bullet_ready_right_box = (gcnew System::Windows::Forms::PictureBox());
            this->bullet_done_left_box = (gcnew System::Windows::Forms::PictureBox());
            this->bullet_done_right_box = (gcnew System::Windows::Forms::PictureBox());
            this->time_word_label = (gcnew System::Windows::Forms::Label());
            this->time_label = (gcnew System::Windows::Forms::Label());
            this->exit_button = (gcnew System::Windows::Forms::Button());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->street_box))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Peet_closed_box))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Peet_open_box))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bullet_ready_left_box))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bullet_ready_right_box))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bullet_done_left_box))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bullet_done_right_box))->BeginInit();
            this->SuspendLayout();
            // 
            // street_box
            // 
            this->street_box->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"street_box.Image")));
            this->street_box->Location = System::Drawing::Point(240, 13);
            this->street_box->Name = L"street_box";
            this->street_box->Size = System::Drawing::Size(599, 427);
            this->street_box->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
            this->street_box->TabIndex = 0;
            this->street_box->TabStop = false;
            // 
            // Peet_closed_box
            // 
            this->Peet_closed_box->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Peet_closed_box.Image")));
            this->Peet_closed_box->Location = System::Drawing::Point(12, 12);
            this->Peet_closed_box->Name = L"Peet_closed_box";
            this->Peet_closed_box->Size = System::Drawing::Size(222, 50);
            this->Peet_closed_box->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
            this->Peet_closed_box->TabIndex = 1;
            this->Peet_closed_box->TabStop = false;
            this->Peet_closed_box->Click += gcnew System::EventHandler(this, &TheZondbie::Peet_closed_Click);
            // 
            // Peet_open_box
            // 
            this->Peet_open_box->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Peet_open_box.Image")));
            this->Peet_open_box->Location = System::Drawing::Point(12, 13);
            this->Peet_open_box->Name = L"Peet_open_box";
            this->Peet_open_box->Size = System::Drawing::Size(222, 108);
            this->Peet_open_box->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
            this->Peet_open_box->TabIndex = 2;
            this->Peet_open_box->TabStop = false;
            this->Peet_open_box->Visible = false;
            this->Peet_open_box->Click += gcnew System::EventHandler(this, &TheZondbie::Peet_open_Click);
            // 
            // bullet_ready_left_box
            // 
            this->bullet_ready_left_box->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"bullet_ready_left_box.Image")));
            this->bullet_ready_left_box->Location = System::Drawing::Point(17, 127);
            this->bullet_ready_left_box->Name = L"bullet_ready_left_box";
            this->bullet_ready_left_box->Size = System::Drawing::Size(93, 93);
            this->bullet_ready_left_box->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
            this->bullet_ready_left_box->TabIndex = 3;
            this->bullet_ready_left_box->TabStop = false;
            this->bullet_ready_left_box->Visible = false;
            // 
            // bullet_ready_right_box
            // 
            this->bullet_ready_right_box->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"bullet_ready_right_box.Image")));
            this->bullet_ready_right_box->Location = System::Drawing::Point(136, 127);
            this->bullet_ready_right_box->Name = L"bullet_ready_right_box";
            this->bullet_ready_right_box->Size = System::Drawing::Size(93, 93);
            this->bullet_ready_right_box->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
            this->bullet_ready_right_box->TabIndex = 4;
            this->bullet_ready_right_box->TabStop = false;
            this->bullet_ready_right_box->Visible = false;
            // 
            // bullet_done_left_box
            // 
            this->bullet_done_left_box->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"bullet_done_left_box.Image")));
            this->bullet_done_left_box->Location = System::Drawing::Point(17, 127);
            this->bullet_done_left_box->Name = L"bullet_done_left_box";
            this->bullet_done_left_box->Size = System::Drawing::Size(93, 93);
            this->bullet_done_left_box->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
            this->bullet_done_left_box->TabIndex = 5;
            this->bullet_done_left_box->TabStop = false;
            this->bullet_done_left_box->Visible = false;
            this->bullet_done_left_box->Click += gcnew System::EventHandler(this, &TheZondbie::bullet_done_left_Click);
            // 
            // bullet_done_right_box
            // 
            this->bullet_done_right_box->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"bullet_done_right_box.Image")));
            this->bullet_done_right_box->Location = System::Drawing::Point(136, 127);
            this->bullet_done_right_box->Name = L"bullet_done_right_box";
            this->bullet_done_right_box->Size = System::Drawing::Size(93, 93);
            this->bullet_done_right_box->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
            this->bullet_done_right_box->TabIndex = 6;
            this->bullet_done_right_box->TabStop = false;
            this->bullet_done_right_box->Visible = false;
            this->bullet_done_right_box->Click += gcnew System::EventHandler(this, &TheZondbie::bullet_done_right_Click);
            // 
            // time_word_label
            // 
            this->time_word_label->AutoSize = true;
            this->time_word_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->time_word_label->Location = System::Drawing::Point(13, 344);
            this->time_word_label->Name = L"time_word_label";
            this->time_word_label->Size = System::Drawing::Size(73, 20);
            this->time_word_label->TabIndex = 7;
            this->time_word_label->Text = L"Время: ";
            // 
            // time_label
            // 
            this->time_label->AutoSize = true;
            this->time_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->time_label->Location = System::Drawing::Point(91, 344);
            this->time_label->Name = L"time_label";
            this->time_label->Size = System::Drawing::Size(19, 20);
            this->time_label->TabIndex = 8;
            this->time_label->Text = L"0";
            // 
            // exit_button
            // 
            this->exit_button->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
                static_cast<System::Int32>(static_cast<System::Byte>(128)));
            this->exit_button->Location = System::Drawing::Point(12, 401);
            this->exit_button->Name = L"exit_button";
            this->exit_button->Size = System::Drawing::Size(129, 34);
            this->exit_button->TabIndex = 9;
            this->exit_button->Text = L"Сдаться";
            this->exit_button->UseVisualStyleBackColor = false;
            this->exit_button->Click += gcnew System::EventHandler(this, &TheZondbie::exit_button_Click);
            // 
            // TheZondbie
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
            this->ClientSize = System::Drawing::Size(843, 447);
            this->Controls->Add(this->exit_button);
            this->Controls->Add(this->time_label);
            this->Controls->Add(this->time_word_label);
            this->Controls->Add(this->bullet_done_right_box);
            this->Controls->Add(this->bullet_done_left_box);
            this->Controls->Add(this->bullet_ready_right_box);
            this->Controls->Add(this->bullet_ready_left_box);
            this->Controls->Add(this->Peet_closed_box);
            this->Controls->Add(this->street_box);
            this->Controls->Add(this->Peet_open_box);
            this->DoubleBuffered = true;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"TheZondbie";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"TheZondbie";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->street_box))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Peet_closed_box))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Peet_open_box))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bullet_ready_left_box))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bullet_ready_right_box))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bullet_done_left_box))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bullet_done_right_box))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion
    private:
        void InitializeGame() {
            // Инициализация списков
            zondbies = gcnew List<PictureBox^>();
            // Инициализация переменных
            bullets_left = MAX_BULLETS;
            is_gun_open = 0;
            zondbie_speed = BASE_SPEED;
            animation_frame = 1;
            time_passed = 0;
            // Таймер игрового цикла
            game_timer = gcnew Timer();
            game_timer->Interval = 16; // ~60 FPS
            game_timer->Tick += gcnew EventHandler(this, &TheZondbie::GameTick);
            game_timer->Start();
            // Таймер спавна зомби
            spawn_timer = gcnew Timer();
            spawn_timer->Interval = 1500; // Каждые 1.5 секунды
            spawn_timer->Tick += gcnew EventHandler(this, &TheZondbie::SpawnZondbie);
            spawn_timer->Start();
            // Таймер анимации зомби
            animation_timer = gcnew Timer();
            animation_timer->Interval = 200; // 5 FPS для анимации
            animation_timer->Tick += gcnew EventHandler(this, &TheZondbie::AnimationTick);
            animation_timer->Start();
            // Таймер времени
            world_time = gcnew Timer();
            world_time->Interval = 1000;
            world_time->Tick += gcnew EventHandler(this, &TheZondbie::TimeTick);
            world_time->Start();
            // Создание звуков
            shoot_sound = gcnew SoundPlayer("game_data/shoot_sound.wav");
            open_Peet_sound = gcnew SoundPlayer("game_data/open_Peet_sound.wav");
            new_bullet_sound = gcnew SoundPlayer("game_data/new_bullet_sound.wav");
            zondbie_death_sound = gcnew SoundPlayer("game_data/zondbie_death_sound.wav");
            game_over_sound = gcnew SoundPlayer("game_data/game_over_sound.wav");
        }
        void SpawnZondbie(Object^ sender, EventArgs^ e) {
            PictureBox^ zondbie = gcnew PictureBox();
            zondbie->Size = Drawing::Size(ZONDBIE_SIZE_X, ZONDBIE_SIZE_Y);
            zondbie->Tag = 0; // 0 - не уничтожен
            // Случайный выбор стороны
            Random^ rand = gcnew Random();
            int from_left = rand->Next(0, 2) == 0;
            if (from_left) {
                zondbie->Location = Point(-ZONDBIE_SIZE_X, 0);
                zondbie->Tag = 1; // 1 - идёт слева направо
            }
            else {
                zondbie->Location = Point(street_box->Width, 0);
                zondbie->Tag = -1; // -1 - идёт справа налево
            }
            // Устанавливаем картинку
            UpdateZondbieImage(zondbie);
            zondbie->Click += gcnew EventHandler(this, &TheZondbie::Zondbie_Click);
            street_box->Controls->Add(zondbie);
            zondbies->Add(zondbie);
        }
        void UpdateZondbieImage(PictureBox^ zondbie) {
            int direction = (int)zondbie->Tag;
            String^ side = (direction == 1 || direction == -1) ?
                (direction != 1 ? L"right" : L"left") : L"left";
            String^ imagePath = String::Format(L"game_data/Zondbie_{0}_{1}.png", side, (animation_frame % 2) + 1);
            try {
                zondbie->Image = Image::FromFile(imagePath);
            }
            catch (...) {
                // Если картинки нет - закрашиваем цветом
                zondbie->BackColor = Color::Green;
            }
        }

        // Обработки таймеров
        void GameTick(Object^ sender, EventArgs^ e) {
            // Двигаем всех зомби
            for (int i = zondbies->Count - 1; i >= 0; i--)
            {
                PictureBox^ zondbie = zondbies[i];
                int direction = (int)zondbie->Tag;
                Point pos = zondbie->Location;
                // Получаем центр street_box по X
                int centerX = street_box->Width / 2;
                // Расстояние от зомби до центра (по модулю)
                int distanceToCenter = Math::Abs(pos.X + ZONDBIE_SIZE_X / 2 - centerX);
                // Максимальное смещение по Y (насколько низко может опуститься зомби)
                int maxYOffset = street_box->Height - ZONDBIE_SIZE_Y;
                // Y меняется пропорционально расстоянию до центра
                // Чем ближе к центру (distanceToCenter меньше), тем больше Y
                pos.Y = maxYOffset - (distanceToCenter * maxYOffset / centerX);
                // Движение по X
                pos.X += (int)(zondbie_speed * direction);
                // Ограничиваем Y, чтобы зомби не выходил за пределы
                if (pos.Y < 0) pos.Y = 0;
                if (pos.Y > maxYOffset) pos.Y = maxYOffset;
                zondbie->Location = pos;
                // Проверка, дошёл ли зомби до центра
                if ((direction == 1 && pos.X >= centerX - ZONDBIE_SIZE_X/ 2) ||
                    (direction == -1 && pos.X <= centerX + ZONDBIE_SIZE_X / 2)) {
                    // Зомби дошёл - конец игры
                    this->Close();
                    return;
                }
                // Удаляем зомби за пределами экрана
                if (pos.X < -ZONDBIE_SIZE_X || pos.X > street_box->Width + ZONDBIE_SIZE_X) {
                    street_box->Controls->Remove(zondbie);
                    zondbies->RemoveAt(i);
                    delete zondbie;
                }
            }
        }
        void AnimationTick(Object^ sender, EventArgs^ e) {
            // Меняем кадр анимации
            animation_frame++;
            // Обновляем картинки всех зомби
            for each (PictureBox ^ zondbie in zondbies)
                UpdateZondbieImage(zondbie);
        }
        void TimeTick(Object^ sender, EventArgs^ e) {
            time_passed++;
            time_label->Text = time_passed.ToString();
        }

        // Нажатия игрока
        void Zondbie_Click(Object^ sender, EventArgs^ e) {
            PictureBox^ zondbie = safe_cast<PictureBox^>(sender);
            // Проверяем, можно ли стрелять
            if (is_gun_open || bullets_left <= 0) return;
            try {
                Random^ rand = gcnew Random();
                if (rand->Next(0, 2))
                    shoot_sound->Play();
                else
                    zondbie_death_sound->Play();
            }
            catch (...) {}
            // Убиваем зомби
            street_box->Controls->Remove(zondbie);
            zondbies->Remove(zondbie);
            delete zondbie;
            bullets_left--;
            zondbie_speed += 0.05f; // Увеличиваем скорость
        }
        void Peet_closed_Click(Object^ sender, EventArgs^ e) {
            if (bullets_left) return;
            try {
                open_Peet_sound->Play();
            }
            catch (...) {}
            // Переключаем состояние ружья и патронов
            is_gun_open = 1;
            Peet_closed_box->Visible = 0;
            Peet_open_box->Visible = 1;
            bullet_done_left_box->Visible = 1;
            bullet_done_right_box->Visible = 1;
        }
        void Peet_open_Click(Object^ sender, EventArgs^ e) {
            if (bullets_left != 2) return;
            try {
                open_Peet_sound->Play();
            }
            catch (...) {}
            // Переключаем состояние ружья и патронов
            is_gun_open = 0;
            Peet_closed_box->Visible = 1;
            Peet_open_box->Visible = 0;
            bullet_ready_left_box->Visible = 0;
            bullet_ready_right_box->Visible = 0;
        }
        void bullet_done_left_Click(Object^ sender, EventArgs^ e) {
            try {
                new_bullet_sound->Play();
            }
            catch (...) {}
            // Добавляем патрон и меняем картинку
            bullets_left++;
            bullet_done_left_box->Visible = 0;
            bullet_ready_left_box->Visible = 1;
        }
        void bullet_done_right_Click(Object^ sender, EventArgs^ e) {
            try {
                new_bullet_sound->Play();
            }
            catch (...) {}
            // Добавляем патрон и меняем картинку
            bullets_left++;
            bullet_done_right_box->Visible = 0;
            bullet_ready_right_box->Visible = 1;
        }
    private: System::Void exit_button_Click(System::Object^ sender, System::EventArgs^ e) {
        this->Close();
    }
};
}