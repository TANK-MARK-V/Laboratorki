#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <math.h>
#include <windows.h>

#define MAX_SIZE 10

int main()
{
	system("color f0");
	setlocale(LC_ALL, "Russian");
	int a[MAX_SIZE][MAX_SIZE], maxInRow[MAX_SIZE], n, m;
	do {
		do {
			printf("Введите кол-во строк n (n <= %d):\n", MAX_SIZE);
			scanf("%d", &n);
		} while (n < 1 || n > MAX_SIZE);
		do {
			printf("Введите кол-во столбцов m (m <= %d):\n", MAX_SIZE);
			scanf("%d", &m);
		} while (m < 1 || m > MAX_SIZE);

		printf("Введите элементы матрицы [%d*%d] построчно:\n", n, m);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				scanf("%d", &a[i][j]);
		printf("Исходная матрица:\n");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				printf("%d ", a[i][j]);
			}
			printf("\n");
		}

		for (int i = 0; i < n; i++) {
			int first = a[i][0];
			for (int k = 0; k < m; k++) {
				int s = 0;
				int t;
				for (int j = 1 + s; j < m; j++) {
					if (a[i][j] > first) {
						t = a[i][j];
						a[i][j] = a[i][j - 1];
						a[i][j - 1] = t;
						s++;
					}
				}
			}
		}

		printf("Промежуточная матрица:\n");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				printf("%d ", a[i][j]);
			}
			printf("\n");
		}

		for (int i = 0; i < n; i++) {
			int max = a[i][0];
			for (int j = 1; j < m; j++) {
				if (a[i][j] > max) {
					max = a[i][j];
				}
			}
			maxInRow[i] = max;
		}

		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < n - 1 - i; j++) {
				if (maxInRow[j] < maxInRow[j + 1]) {
					int t = maxInRow[j];
					maxInRow[j] = maxInRow[j + 1];
					maxInRow[j + 1] = t;

					int tempRow[MAX_SIZE];
					for (int k = 0; k < m; k++) {
						tempRow[k] = a[j][k];
						a[j][k] = a[j + 1][k];
						a[j + 1][k] = tempRow[k];
					}
				}
			}
		}

		printf("Полученная матрица:\n");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				printf("%d ", a[i][j]);
			}
			printf("\n");
		}

		printf("\nНажмите ESC для выхода из программы, или же любую другую клавишу для повторного запуска программы:\n\n");
	} while (_getch() != 27);
}