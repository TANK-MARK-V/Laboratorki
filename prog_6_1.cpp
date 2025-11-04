#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>  // Стандартный вход/выход
#include <locale.h>  // Вывод на русском языке
#include <conio.h>  // Задержка экрана
#include <math.h>  // Математические функции
#include <windows.h>  // Очистка экрана

#define N 10  // Максимальная длина последовательности


int main() {
    setlocale(LC_ALL, "Russian");
    do {
        system("cls");
        int n;
        do {
            printf("Введите n <= %d\n", N);
            scanf("%d", &n);
        } while (n < 1 || N < n);

        int array[N];  // Создаём массив
        int was_odd = 0;  // Встретилось хоть одно нечётное число
        int get_pos = 0;  // Какие числа мы будем дальше брать: отрицательные или положительные

        for (int i = 0; i < n; i++) {
            printf("Введите %d член последовательности\n", i + 1);
            scanf("%d", &array[i]);
            if (fabs(array[i] % 2) == 0) {
                if (was_odd) get_pos = 1;
            }
            else was_odd = 1;
        }
        printf("Получилась следующая последовательность: ");
        for (int i = 0; i < n; i++) {
            if (i != n - 1) printf("%d, ", array[i]);
            else printf("%d\n", array[i]);
        }

        printf("\nВыбираем только %s элементы...\n", (get_pos) ? "положительные" : "отрицательные");
        int need = 0;
        for (int i = 0; i < n; i++) {
            if (array[i] < 0 && !get_pos || array[i] > 0 && get_pos) {
                array[need] = array[i];
                need++;
            }
        }
        if (need > 0) {
            printf("Получилась следующая последовательность: ");
            for (int i = 0; i < need; i++) {
                if (i != need - 1) printf("%d, ", array[i]);
                else printf("%d\n", array[i]);
            }

            // Теперь будем использовать get_pos в качестве переменной для замены
            printf("\nЗаменяем порядок чисел на обратный...\n");
            for (int i = 0; i < need / 2; i++) {
                get_pos = array[i];
                array[i] = array[need - i - 1];
                array[need - i - 1] = get_pos;
            }
            printf("Конечная последовательность: ");
            for (int i = 0; i < need; i++) {
                if (i != need - 1) printf("%d, ", array[i]);
                else printf("%d\n", array[i]);
            }
        }
        else printf("Таких элементов нет\n");

        printf("\nНажмите ESC, чтобы закончить\n");
        printf("Нажмите любую другую кнопку, чтобы продолжить\n");
    } while (_getch() != 27);
    return 0;
}
