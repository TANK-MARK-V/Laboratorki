#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>  // Стандартный вход/выход
#include <locale.h>  // Вывод на русском языке
#include <conio.h>  // Задержка экрана

#include <string.h>  // Работа со строками
#include <math.h>  // Математические функции

#include <stdlib.h>  // Создание динамических массивов, использование рандома и преобразования строк
#include <windows.h>  // Очистка консоли и установка кодировки
#include <time.h>  // Обновление рандома


#include "mystr.cpp"  // Своя библиотека для работы со строками


#define RU setlocale(LC_ALL, "Russian")  // Для вывода русских слов
#define UT setlocale(LC_ALL, "ru_RU.UTF-8")  // Для вывода текста файла


#define MAX_LEN 16  // Максимальная длина текста пользователя


int main() {
    SetConsoleCP(1251); SetConsoleOutputCP(1251);  // Ввод на русском
    system("color F0");
    const char* sep = " ,.?!-;:()/\\|\"\'\n\0";
    do {  // Ввод текста
        char* user_input;  // Строка для ввода пользователя и для хранения текста в виде строчки
        user_input = (char*)calloc(MAX_LEN + 1, sizeof(char));
        char* text_arr[MAX_LEN / 2];  // Массив для слов
        do {
            system("cls");  // Очищаем консоль
            printf("Эта программа печатает те слова заданного текста, которые можно\n");
            printf("составить из букв, входящих в заданное слово.Каждую букву можно использовать не\n");
            printf("более числа ее вхождений в заданное слово\n");
            printf("Программа выполнена c использованием стандартной библиотеки <string.h>\n\n");

            printf("Введите текст (не более %d символов).\nЧтобы закончить ввод нажмите enter:\n", MAX_LEN);
            _strnset(user_input, 0, MAX_LEN + 1);  // Проставляем везде '\0'
            fgets(user_input, MAX_LEN + 1, stdin);  // Ввод пользователя
            if (user_input[MAX_LEN - 1]) while (getchar() != '\n');  // Очищаем поток
            text_arr[0] = strtok(user_input, sep);
        } while (!text_arr[0]);
        for (int i = 1; text_arr[i] = strtok(NULL, sep); i++);


        char* word;  // Строка-слово
        int good_word;  // Пользователь успешно ввёл слово
        do {  // Ввод слова
            good_word = 1;
            system("cls");  // Очищаем консоль
            printf("Эта программа печатает те слова заданного текста, которые можно\n");
            printf("составить из букв, входящих в заданное слово.Каждую букву можно использовать не\n");
            printf("более числа ее вхождений в заданное слово\n");
            printf("Программа выполнена без использования стандартной библиотеки <string.h>\n\n");

            printf("\nВведённые слова:\n");
            printf("\"%s\"", text_arr[0]);
            for (int i = 1; text_arr[i]; i++) printf(", \"%s\"", text_arr[i]);

            word = (char*)calloc(MAX_LEN / 2 + 1, sizeof(char));
            printf("\n\nВведите слово (не более %d символов).\nЧтобы закончить ввод нажмите enter:\n", MAX_LEN / 2);
            fgets(word, MAX_LEN / 2 + 1, stdin);
            if (word[MAX_LEN / 2 - 1]) while (getchar() != '\n');  // Очищаем поток

            if (!word[0]) good_word = 0;
            else if (!(word = strtok(word, sep))) good_word = 0;
        } while (!good_word);  // Повторяем ввод, пока пользователь не введёт хотя бы одну буковку
        _strlwr(word);
        
        // Теперь найдём слова, которые можно составить из букв, входящих в заданное слово
        int second_word = 0;  // Мы нашли хотя бы одно слово
        for (int w = 0; text_arr[w]; w++)
            if (strlen(text_arr[w]) <= strlen(word)) {
                int is_good = 1;  // Подходит ли нам слово

                char* lower_cur_word;
                lower_cur_word = (char*)calloc(MAX_LEN / 2 + 1, sizeof(char));
                strcpy(lower_cur_word, text_arr[w]);
                _strlwr(lower_cur_word);

                for (int i = 0; lower_cur_word[i] && is_good; i++)
                    if (mystrcount(lower_cur_word, lower_cur_word[i]) > mystrcount(word, lower_cur_word[i]))
                        is_good = 0;

                if (is_good) {
                    if (second_word) printf(", \"%s\"", text_arr[w]);
                    else { second_word = 1; printf("Слова: \"%s\"", text_arr[w]); }
                }
                free(lower_cur_word);
            }

        if (!second_word) printf("Нет слов, которые можно составить из букв \"%s\"", word);

        printf("\n\nНажмите ESC, что бы закончить.\nНажмите любую другую кнопку, чтобы продолжить:\n");
    } while (_getch() != 27);
    return 0;
}