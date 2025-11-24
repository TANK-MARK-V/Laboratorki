#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>  // Стандартный вход/выход
#include <locale.h>  // Вывод на русском языке
#include <conio.h>  // Задержка экрана
#include <string.h>  // Работа со строками
#include <stdlib.h>  // Создание динамических массивов
#include <math.h>  // Математические функции

#include <windows.h>  // Очистка консоли


#define RU setlocale(LC_ALL, "Russian")  // Для вывода русских слов




int main() {
	RU;
	do {

		int n, m;  // Размеры массива
		char* array;  // Массив на ввод
		char* array_ind;  // Массив на индексы
		int* h;

		printf("Введите n, количество строчек двумерного символьного массива, n > 0\n");
		do scanf("%d", &n);
		while (n < 1);

		printf("Введите m, количество столбцов двумерного символьного массива, m > 0\n");
		do scanf("%d", &m);
		while (m < 1);

		// Выделяем память
		array = (char*)calloc(n * m, sizeof(char));
		if (array == NULL)
		{
			puts("Нет памяти на массив. Конец работы\n");
			return 1;
		}

		// Пользователь вводит массив
		printf("\nВведите массив посимвольно:\n");
		getchar();  // Очищаем поток

		for (int i = 0;i < n;i++)
			for (int j = 0;j < m;j++)
				*(array + i * m + j) = getchar();

		printf("\nПолучился вот такой массив:\n");
		for (int i = 0;i < n;i++) {
			for (int j = 0;j < m;j++)
				printf("%c", *(array + i * m + j));
			printf("\n");
		}
		printf("\nВ памяти лежат значения:\n");
		for (int i = 0; i < m * n; i++)
			printf("%p - %c ~ %d\n", array + i, *(array + i), *(array + i));

		h = (int*)malloc(sizeof(int));
		if (h == NULL)
		{
			puts("Нет памяти на h. Конец работы\n");
			return 1;
		}

		printf("\nВведите h:\n");
		scanf("%d", h);

		printf("\nВ памяти лежит значение:\n");
		printf("%p - %d\n", h, *h);

		// Обрабатываем данные в зависимости от h
		if (*h < 1) {
			int* diff = (int*)calloc(n, sizeof(int));
			if (diff == NULL)
			{
				puts("Нет памяти на массив. Конец работы\n");
				return 1;
			}
			for (int i = 0; i < n; i++) {
				*(diff + i) = 0;
				for (int j = 0; j < m; j++) {
					if (*(array + i * m + j) == 'a')
						*(diff + i) += 1;
					else if (*(array + i * m + j) == 'b')
						*(diff + i) -= 1;
				}
				if (*(diff + i) < 0)
				*(diff + i) *= -1;
			}
			printf("\nПолучился вот такой массив из разниц количеств \"a\" и \"b\::\n");
			for (int i = 0;i < n - 1;i++)
				printf("%d, ", *(diff + i));
			printf("%d\n", *(diff + n - 1));

			printf("\nВ памяти лежат значения:\n");
			for (int i = 0; i < n; i++)
				printf("%p - %d\n", diff + i, *(diff + i));
		}
		else {
			int* diff = (int*)malloc(sizeof(int));
			if (diff == NULL)
			{
				puts("Нет памяти на количество a и b. Конец работы\n");
				return 1;
			}
			*diff = 0;
			for (int i = 0; i < n; i++) 
				for (int j = 0; j < m; j++) 
					if (*(array + i * m + j) == 'a' || *(array + i * m + j) == 'b')
						*diff += 1;
			printf("\nПолучается, всего в массиве %d элементов \"a\" и \"b\"\n", *diff);
			printf("\nВ памяти лежит значение:\n");
			printf("%p - %d\n", diff, *diff);
		}
		free(array); free(h);  // Очищаем память
		printf("\nНажмите ESC, чтобы закончить.\n");
		printf("Нажмите любую другу кнопку, чтобы продолжить...\n");
	} while (_getch() != 27);
	return 0;
}