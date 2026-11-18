#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>  // Стандартный вход/выход
#include <locale.h>  // Вывод на русском языке
#include <conio.h>  // Задержка экрана
#include <math.h>  // Математические функции

#define EXTRA 5  // Дополнительное место для красоты

double taylor(double x, double e);
void edge(int down, int col, int wide);
void center(int col, int space, int left, int right, double num);


int main() {
    setlocale(LC_ALL, "Russian");
    double x1, x2, h, e;

    do {
        printf("Введите левую границу x1 диапазона для x\n");
        printf("Рекоммендуется вводить x1 > 0\n");
        scanf("%lf", &x1);

        printf("Введите правую границу x2 диапазона для x.\n");
        printf("Рекоммендуется вводить x2 < 2\n");
        printf("Помните, левая граница не может быть больше правой\n");
        scanf("%lf", &x2);
    } while (x1 > x2);

    do {
        printf("Введите шаг h аргумента x\n");
        scanf("%lf", &h);
    } while ((h <= 0) || (h > x2 - x1));

    do {
        printf("Введите точноть e, 0 < e < 1\n");
        scanf("%lf", &e);
    } while ((e <= 0) || (1 <= e));

    int left = log10(fabs(x2)) + (x1 < 0);  // Сколько символов слева от запятой
    int right = 1;  // Сколько цифер после запятой будем выводить

    double prec = (e < h) ? e:h;  // Выбираем наименьшее среди h и e

    while (prec > 0) {  // Считаем количество цифер после запятой
        prec *= 10;
        right++;
        prec -= (int)prec;
    }
    if (6 > right) right = 6;  // Выводим не меньше 6 цифер

    int col = left + right + EXTRA;  // Ширина колонки
    int space = (col - (left + right)) / 2;  // Расстояние от колонки до числа
    int wide = col * 3 + 4;  // Ширина всей таблицы
    double y, root;  // Создаём переменные для хранения y и кубического корня

    // Выводим верх таблицы
    edge(1, col, wide); edge(0, col, wide); edge(1, col, wide);

    for (double x = x1; x <= x2 + h / 2; x += h) {
        y = taylor(x, e); root = cbrt(x);

        // Вывод x
        center(col, space, left, right, x);

        // Вывод y
        if (y == x + 1) {  // Ряд не сходится
            printf("*");
            for (int i = 0; i < col; i++) {
                if ((col / 2) == (i)) printf("-");
                else printf(" ");
            }
        }
        else center(col, space, left, right, y);

        // Вывод cbrt(x)
        center(col, space, left, right, root);
        printf("*\n");
    }
    edge(1, col, wide);  // Выводим низ таблицы
    printf("Нажмите любую кнопку, чтобы продолжить\n");
    _getch();
    return 0;
}

double taylor(double x, double e) {
    // Данная функция использует идею сохранения n члена для домножения его до n + 1
    // Каждый n домножается на (x - 1)
    // Член n <= 2 домножается на 1./3
    // член n > 2 домножается на (5 + 3 * (n - 3)) и делится на (9 + 3 * (n - 3))
    // Члены n > 1 меняют знаки

    double sum = 0;  // Сумма членов ряда
    double previous_mem;  // Предыдущий член ряда
    double current_mem = 1;  // Текущий член ряда
    int n = 0;  // Номер члена в ряду
    do {
        // Сохраняем последний член, добавляем его к сумме, увеличиваем номер на 1
        previous_mem = current_mem; sum += current_mem; n++;
        if (n > 1) current_mem *= -1;
        if (n <= 2) current_mem *= 1./3;
        else current_mem *= (double)(5 + 3 * (n - 3)) / (9 + 3 * (n - 3));
        current_mem *= x - 1;
    } while ((fabs(current_mem) > e) && (fabs(previous_mem) > fabs(current_mem)));
    return (fabs(previous_mem) > fabs(current_mem)) ? sum: x + 1;
}


void edge(int line, int col, int wide) {
    // Вывод частей таблиц
    if (line) {
        for (int i = 0; i < wide; i++) printf("*");
        printf("\n");
    }
    else {
        // Шапка таблицы
        printf("*");  // x
        for (int i = 0; i < col; i++) {
            if ((col / 2) == (i)) printf("x");
            else printf(" ");
        }
        printf("*");  // y
        for (int i = 0; i < col; i++) {
            if ((col / 2) == (i)) printf("y");
            else printf(" ");
        }
        printf("*");  // cbrt(x)
        for (int i = 0; i < col - 6; i++) {
            if ((col / 2) == (i + 3)) printf("cbrt(x)");
            else printf(" ");
        }
        printf("*\n");
    }
}


void center(int col, int space, int left, int right, double num) {
    // Вывод переменных по центру колонки
    printf("*");
    printf("%*.*lf", space + left + right + 1, right, num);
    for (int i = 0; i < space; i++) printf(" ");
}