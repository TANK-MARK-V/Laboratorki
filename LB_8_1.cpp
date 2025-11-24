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

		int m = 0;  // Размер массива
		char buffer;  // Сюда мы будем сохранять ввод
		int n;  // Количество букв "a" и "z"
		char* array;  // Массив на ввод
		char* array_ind;  // Массив на индексы

		printf("Введите m, размер символьного массива, m > 0\n");
		do scanf("%d", &m);
		while (m < 1);

		// Выделяем память
		array = (char*)calloc(m, sizeof(char));
		if (array == NULL)
		{
			puts("Нет памяти. Конец работы\n");
			return 1;
		}

		// Пользователь вводит массив
		printf("\nВведите массив посимвольно:\n");
		getchar();  // Очищаем поток
		n = 0;
		for (int i = 0; i < m; i++) {
			buffer = getchar();
			*(array + i) = buffer;
			if (buffer == 'a' || buffer == 'z')
				n++;
		}

		printf("\nПолучился вот такой массив:\n");
		for (int i = 0; i < m - 1; i++)
			printf("%c, ", *(array + i));
		printf("%c\n", *(array + m - 1));
		printf("\nВ памяти лежат значения:\n");
		for (int i = 0; i < m; i++)
			printf("%p - %c ~ %d\n", array + i, *(array + i), *(array + i));
		printf("В нём %d элементов-символов \"a\" и \"z\"\n", n);

		// Теперь создадим новый массив из индексов "a" и "z"
		array_ind = (char*)calloc(n, sizeof(char));
		for (int i = 0, j = 0; j < n; i++) {
			if (*(array + i) == 'a' || *(array + i) == 'z')
				*(array_ind + j++) = i + 1;
		}

		printf("\nИз символов \"a\" и \"z\" получился вот такой массив:\n");
		for (int i = 0; i < n - 1; i++)
			printf("%d, ", *(array_ind + i));
		printf("%d\n", *(array_ind + n - 1));
		printf("\nВ памяти лежат значения:\n");
		for (int i = 0; i < n; i++)
			printf("%p - %d\n", array_ind + i, *(array_ind + i));
		free(array); free(array_ind);  // Очищаем память
		printf("Нажмите ESC, чтобы закончить.\n");
		printf("Нажмите любую другу кнопку, чтобы продолжить...\n");
	} while (_getch() != 27);
	return 0;
}