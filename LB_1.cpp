#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>  // Стандартный вход/выход
#include <locale.h>  // Вывод на русском языке
#include <conio.h>  // Задержка экрана
#include <math.h>  // Математические функции
#include <windows.h>  // Очистка экрана

#define N 100  // Максимальная длина последовательности


int main() {
    setlocale(LC_ALL, "Russian");

    int array[N];  // Создаём массив

    do {
        system("cls");
        int n;
        do {
            printf("Введите n <= %d\n", N);
            scanf("%d", &n);
        } while (n < 1 || N < n);

        printf("Введите %d членов последовательности\n", n); 
        for (int i = 0; i < n; i++) scanf("%d", &array[i]);
        
        printf("Получилась следующая последовательность: ");
        for (int i = 0; i < n; i++) {
            if (i != n - 1) printf("%d, ", array[i]);
            else printf("%d\n", array[i]);
        }

        printf("\nПроведём циклическую перестановку со сдвигом вида \"два последних элемента – в начало массив\"...\n");
        int take;
        int start = n - 1, end = 0, move = -1;
        for (int i = 0; i < 2; i++) {
            take = array[start];
            for (int buble = start; buble > end; buble += move) {  // Заменить >, если move > 0
                array[buble] = array[buble + move];
            }
            array[end] = take;
        }
        printf("Получилась следующая последовательность: ");
        for (int i = 0; i < n; i++) {
            if (i != n - 1) printf("%d, ", array[i]);
            else printf("%d\n", array[i]);
        }
        printf("\nНажмите ESC, чтобы закончить\n");
        printf("Нажмите любую другую кнопку, чтобы продолжить\n");
    } while (_getch() != 27);
    return 0;
}