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


#define SEP {' ', ',', '.', '?', '!', '-', ';', ':', '(', ')', '/',  '\\', '|', '\'', '\"', '\n', '\0'}  // Символы, которые разделяют слова


int main() {
    SetConsoleCP(1251); SetConsoleOutputCP(1251);  // Ввод на русском
    system("color F0");
    do {  // Ввод текста
        char sep[] = SEP;  // Символы, которые разделяют слова
        char text[MAX_LEN + 2];  // Массив с текстом
        char word[MAX_LEN / 2 + 1];  // Массив со словом
        int is_letter;  // Флаг "хотя бы раз встретилась буква"
        do {
            system("cls");  // Очищаем консоль
            printf("Эта программа печатает те слова заданного текста, которые можно\n");
            printf("составить из букв, входящих в заданное слово.Каждую букву можно использовать не\n");
            printf("более числа ее вхождений в заданное слово\n");
            printf("Программа выполнена без использования стандартной библиотеки <string.h>\n\n");

            mystrnset(text, 0, MAX_LEN + 2);  // Проставляем везде '\0'
            printf("Введите текст (не более %d символов).\nЧтобы закончить ввод нажмите enter:\n", MAX_LEN);
            char letter; int l = 0;
            is_letter = 0;
            while ((letter = getchar()) != '\n' && l < MAX_LEN) {
                text[l++] = letter;
                if (!mystrchr(sep, letter)) is_letter = 1;
            }
            if (letter != '\n') while (getchar() != '\n');  // Очищаем поток
            text[l] = ' ';  // Ставим знак-разделитель в конце
        } while (!is_letter);  // Повторяем ввод, пока пользователь не введёт хотя бы одну буковку
        
        do {  // Ввод слова
            system("cls");  // Очищаем консоль
            printf("Эта программа печатает те слова заданного текста, которые можно\n");
            printf("составить из букв, входящих в заданное слово.Каждую букву можно использовать не\n");
            printf("более числа ее вхождений в заданное слово\n");
            printf("Программа выполнена без использования стандартной библиотеки <string.h>\n\n");

            printf("\nВведённый текст:\n");
            for (int i = 0; text[i]; i++) printf("%c", text[i]);

            mystrnset(word, 0, MAX_LEN / 2 + 1);  // Проставляем везде '\0
            printf("\n\nВведите слово (не более %d символов).\nЧтобы закончить ввод нажмите enter:\n", MAX_LEN / 2);
            char letter; int l = 0;
            is_letter = 0;
            while (!mystrchr(sep, letter = getchar()) && l < MAX_LEN / 2) word[l++] = letter;
            if (letter != '\n') while (getchar() != '\n');  // Очищаем поток
        } while (!mystrlen(word));  // Повторяем ввод, пока пользователь не введёт хотя бы одну буковку
        mystrlwr(word);

        // Теперь найдём слова, которые можно составить из букв, входящих в заданное слово
        char words[MAX_LEN + 2];  // Массив для слов
        mystrnset(words, 0, MAX_LEN + 2);  // Проставляем везде '\0'
        int last = 0;  // Индекс последней буквы в массиве words
        int start = 0, end = -1;  // Индексы начала и конца слова;

        for (int i = 0; text[i]; i++) {
            if (!mystrchr(sep, text[i]))  // Если мы наткнулись на слово, а не разделитель
                if (end == -1) start = end = i;  // Если это начало слова, то ставим и начало и конец на i
                else end = i;  // Если конец слова уже не равен -1, то обновляем конец слова

            else if (end >= start) { // Если мы наткнулись на разделитель и до этого было слово (конец слова стоит не перед его началом
                int is_good = end - start + 1 <= MAX_LEN / 2;  // Подходит ли нам слово
                char cur_word[MAX_LEN / 2 + 2];  // Текущее слово
                int letter;
                for (letter = 0; letter <= end - start && letter < MAX_LEN / 2; letter++) cur_word[letter] = text[start + letter];
                cur_word[letter++] = '\"'; cur_word[letter] = '\0';
                
                char lower_cur_word[MAX_LEN / 2 + 2];
                mystrcpy(lower_cur_word, cur_word);
                mystrlwr(lower_cur_word);
                
                for (int j = 0; j < letter - 1 && is_good; j++)
                    if (mystrcount(lower_cur_word, lower_cur_word[j]) > mystrcount(word, lower_cur_word[j])) is_good = 0;
                if (is_good) mystrcat(words, cur_word);
                start = i; end = -1;
            }
        }
        
        if (mystrlen(words)) {
            printf("Слова: \"");
            for (int i = 0; words[i]; i++)
                if (words[i] == '\"' && words[i + 1]) printf("\", \"");
                else printf("%c", words[i]);
        }
        else {
            printf("Нет слов, которые можно составить из букв \"");
            for (int i = 0; word[i]; i++) printf("%c", word[i]);
            printf("\"\n");
        }

        printf("\n\nНажмите ESC, что бы закончить.\nНажмите любую другую кнопку, чтобы продолжить:\n");
    } while (_getch() != 27);
    return 0;
}