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
#define ALP_LEN 116  // Длина массива для букв
#define ERR 0.1E-5  // Погрешность при вычислениях


int main() {
    SetConsoleCP(1251); SetConsoleOutputCP(1251);  // Ввод на русском
    system("color F0");
    const char* sep = " ,.?!-;:()/\\|\"\'\n\0";
    do {
        // Сначала введём текст и преобразуем его в массив слов
        char* user_input, * text_string;  // Строка для ввода пользователя и для хранения текста в виде строчки
        user_input = (char*)calloc(MAX_LEN + 1, sizeof(char)); text_string = (char*)calloc(MAX_LEN + 1, sizeof(char));
        char* text_arr[MAX_LEN / 2];  // Массив для слов
        do {
            system("cls");  // Очищаем консоль
            printf("Эта программа определяет в заданном тексте наиболее часто встречающийся символ\n");
            printf("затем определяет все слова, в которых доля этого символа максимальна\n");
            printf("Программа выполнена с использованием стандартной библиотеки <string.h>\n\n");

            printf("Введите текст (не более %d символов).\nЧтобы закончить ввод нажмите enter:\n", MAX_LEN);
            _strnset(user_input, 0, MAX_LEN + 1); _strnset(text_string, 0, MAX_LEN + 1);  // Проставляем везде '\0'
            fgets(user_input, MAX_LEN + 1, stdin);  // Ввод пользователя
            strncpy(text_string, user_input, MAX_LEN + 1);  // Копируем в text_string
            text_arr[0] = strtok(user_input, sep);
        } while (!text_arr[0]);
        for (int i = 1; text_arr[i] = strtok(NULL, sep); i++);

        /*printf("\nПолучился такой массив из слов:\n\"%s\"", text_arr[0]);
        for (int i = 1; text_arr[i]; i++) printf(", \"%s\"", text_arr[i]);
        printf("\n");*/

        // Найдём наиболее часто встречающийся символ
        char often = 0;       // Самый встречающийся символ
        int counter = 0;  // Сколько раз он встречается
        for (int i = 0; text_arr[i]; i++)
            for (int j = 0; text_arr[i][j]; j++) {
                char cur_letter = text_arr[i][j];
                int cur_counter = mystrcount(text_string, cur_letter);
                if (cur_counter > counter) { often = cur_letter; counter = cur_counter; }
            }
        printf("\n\nНаиболее часто встречающийся символ - \"%c\". ", often);

        // Теперь найдём слова, в которых доля этого символа максимальна
        double percent = 0;  // Максимальная доля символа
        char* words[MAX_LEN / 2];  // Массив для всех слов, в которых доля этого символа максимальна
        int last = 0;  // Индекс последнего слова в массиве words

        for (int i = 0; text_arr[i]; i++) {
            int cur_counter = mystrcount(text_arr[i], often);
            double cur_percent = (double)cur_counter / strlen(text_arr[i]);  // Доля символа в этом слове

            if (fabs(cur_percent - percent) < ERR)
                words[last++] = text_arr[i];

            else if (cur_percent > percent) {
                percent = cur_percent;
                for (int w = 0; w < last; w++) words[w] = 0;
                last = 0;
                words[last++] = text_arr[i];
            }
        }

        printf("Слова, в которых доля этого символа максимальна: ");
        printf("\"%s\"", words[0]);
        for (int w = 1; w < last; w++) printf(", \"%s\"", words[w]);
        printf(" (%.2lf)", percent);

        printf("\n\nНажмите ESC, что бы закончить.\nНажмите любую другую кнопку, чтобы продолжить:\n");
        if (text_string[MAX_LEN - 1]) while (getchar() != '\n');  // Очищаем поток
        free(text_string);
    } while (_getch() != 27);
    return 0;
}