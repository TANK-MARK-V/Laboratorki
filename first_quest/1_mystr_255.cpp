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


#define MAX_LEN 255  // Максимальная длина текста пользователя
#define ALP_LEN 116  // Длина массива для букв
#define ERR 0.1E-5  // Погрешность при вычислениях


#define SEP {' ', ',', '.', '?', '!', '-', ';', ':', '(', ')', '/',  '\\', '|', '\'', '\"', '\0'}  // Символы, которые разделяют слова


int main() {
    SetConsoleCP(1251); SetConsoleOutputCP(1251);  // Ввод на русском
    system("color F0");
    do {
        int free_stream = 0;  // Остались в потоке символы
        // Сначала введём текст и составим алфавит из всех введённых букв
        char sep[] = SEP;  // Символы, которые разделяют слова
        char text[MAX_LEN + 2], alphabet[ALP_LEN + 1];  // Массив с текстом и со всеми встречающимися буквами
        do {
            system("cls");  // Очищаем консоль
            printf("Эта программа определяет в заданном тексте наиболее часто встречающийся символ\n");
            printf("затем определяет все слова, в которых доля этого символа максимальна\n");
            printf("Программа выполнена без использования стандартной библиотеки <string.h>\n\n");

            mystrnset(text, 0, MAX_LEN + 2); mystrnset(alphabet, 0, ALP_LEN + 1);  // Проставляем везде '\0'
            printf("Введите текст (не более %d символов).\nЧтобы закончить ввод нажмите enter:\n", MAX_LEN);
            char letter; int l = 0; int a = 0;
            while ((letter = getchar()) != '\n' && l < MAX_LEN) {
                text[l++] = letter;
                if (!mystrchr(alphabet, letter) && !mystrchr(sep, letter)) alphabet[a++] = letter;
            }
            if (letter == '\n') free_stream = 1;
            text[l] = ' ';  // Ставим знак-разделитель в конце
        } while (!mystrlen(alphabet));  // Повторяем ввод, пока пользователь не введёт хотя бы одну буковку

        /*printf("\nВведённый текст:\n");
        for (int i = 0; text[i]; i++) printf("%c", text[i]);
        printf("\nВведённый алфавит:\n");
        for (int i = 0; alphabet[i]; i++) printf("%c", alphabet[i]);*/

        // Найдём наиболее часто встречающийся символ
        char often;       // Самый встречающийся символ
        int counter = 0;  // Сколько раз он встречается
        for (int i = 0; alphabet[i]; i++) {
            char cur_letter = alphabet[i];
            int cur_counter = mystrcount(text, cur_letter);
            if (cur_counter > counter) { often = cur_letter; counter = cur_counter; }
        }
        printf("\n\nНаиболее часто встречающийся символ - \"%c\". ", often);

        // Теперь найдём слова, в которых доля этого символа максимальна
        double percent = 0;  // Максимальная доля символа
        char words[MAX_LEN + 2];  // Массив для всех слов, в которых доля этого символа максимальна
        mystrnset(words, 0, MAX_LEN + 2);  // Проставляем везде '\0'
        int last = 0;  // Индекс последней буквы в массиве words
        int start = 0, end = -1;  // Индексы начала и конца слова;

        for (int i = 0; text[i]; i++) {
            if (mystrchr(alphabet, text[i]))  // Если мы наткнулись на слово, а не разделитель
                if (end == -1) start = end = i;  // Если это начало слова, то ставим и начало и конец на i
                else end = i;  // Если конец слова уже не равен -1, то обновляем конец слова

            else if (end >= start) { // Если мы наткнулись на разделитель и до этого было слово (конец слова стоит не перед его началом)

                int cur_counter = 0;  // Сколько в найденном слове нужных букв
                for (int l = start; l <= end; l++)
                    cur_counter += text[l] == often;
                double cur_percent = (double)cur_counter / (end - start + 1);  // Доля символа в этом слове

                if (fabs(cur_percent - percent) < ERR) {  // Если доли примерно равны
                    for (int l = 0; l <= end - start; l++)  // Запишем в words слово
                        words[last++] = text[start + l];
                    words[last++] = '\"';  // Разделитель между словами
                }
                else if (cur_percent > percent) {  // Если доля больше, то очищаем массив
                    percent = cur_percent;
                    mystrnset(words, 0, last);  // Обновляем массив слов
                    last = 0;  // Обновляем индекс последней буквы
                    for (int l = 0; l <= end - start; l++)  // Запишем в words слово
                        words[last++] = text[start + l];
                    words[last++] = '\"';  // Разделитель между словами
                }
                start = i; end = -1;
            }
        }

        printf("Слова, в которых доля этого символа максимальна: \"");
        for (int i = 0; words[i]; i++)
            if (words[i] == '\"' && words[i + 1]) printf("\", \"");
            else printf("%c", words[i]);
        printf(" (%.2lf)", percent);


        printf("\n\nНажмите ESC, что бы закончить.\nНажмите любую другую кнопку, чтобы продолжить:\n");
        if (!free_stream) while (getchar() != '\n');  // Очищаем поток
    } while (_getch() != 27);
    return 0;
}