#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>  // Стандартный вход/выход
#include <locale.h>  // Вывод на русском языке
#include <conio.h>  // Задержка экрана

#include <string.h>  // Работа со строками
#include <math.h>  // Математические функции

#include <stdlib.h>  // Создание динамических массивов
#include <windows.h>  // Очистка консоли и установка кодировки
#include <direct.h>  // Работа с файлами

#include "structure.h"  // Работа со структурой
#include "input_funcs.h"  // Функции для ввода
#include "file_funcs.h"  // Файловые функции
#include "functions.h"  // Вспомогательные функции


int main() {
	// Подготовка пользователя
	char file_path[FILE_NAME_LEN];  // Путь до файла
	if (user_prepare(file_path) == -1) {
		printf("\nДальнейшая работа невозможна\n");
		return 1;
	}

	Flight_filter filters[2];  // Создаём фильтры
	for (int fil = 0; fil < 2; fil++)
		for (int i = 0; i < 7; i++)
			filters[fil].apply[i] = filters[fil].logic[i]= 0;  // Обнуляем фильтр
	int run = 1;  // Программа работает
	while (run) {
		int first_action = get_first_action(filters);
		// 1 - Вывод таблицы
		if (first_action == 1) {
			system("cls");
			print_flights(filters, 1, 1, 1);
			printf("\nНажмите любую кнопку, чтобы продолжить");
			_getch();
		}
		// 2 - Ввод и корректировка списка
		else if (first_action == 2) {
			int edit_action = get_edit_action(filters);
			// 1 - Ввод таблицы
			if (edit_action == 1) {
				int n;  // Сколько строчек нужно добавить
				int res;  // Результат ввод
				FILE* table;
				do printf("\nВведите количество строчек, которые хотите добавить (1-99): ");
				while ((res = int_input(&n)) > 1 || (n < 1 || 99 < n));
				if (res == 1) printf("\nВвод строк отменён.");
				else if ((table = fopen(file_path, "a")) == NULL) printf("\nНевозможно открыть файл.");
				else {
					int result = 0;  // Результат ввода последней строчки
					int counter = 0;  // Сколько записей добавили
					for (int i = 0; !result && i < n; i++) {
						Flight new_line;
						result = input_flight(&new_line);
						if (!result) {
							write_line(table, new_line);
							counter++;
						}
					}
					fclose(table);
					printf("\nВвод строк закончен. Добавлено строк: %d", counter);
				}
				printf("\nНажмите любую кнопку, чтобы продолжить");
				_getch();
			}
			// 2 - Изменение записи по номеру
			else if (edit_action == 2) {
				do {
					system("cls");
					int len = print_flights(filters, 1, 1, 1);  // Сколько записей сейчас в таблице
					if (len < 1) break;
					else printf("\n");

					printf("\nВведите 0, чтобы изменить все вышепоказанные записи.");
					printf("\nВведите комера записей (1-%d), которые хотите изменить, через запятую: ", len);
					int* to_edit;  // Массив индексов на удаление
					int res;  // Результат ввода
					res = int_array_input(&to_edit, len);

					// Обработка ошибок
					if (res == -1) printf("\nОшибка выделения памяти.");
					else if (res == 1) printf("\nИзменение записей отменено.");
					else if (res == 2 || res == 3) printf("\nНекорректный ввод.");
					if (res) break;

					if (to_edit[0] == 0) {  // Если это "полный массив"
						printf("\nВыбрано изменение всех записей по фильтру\n");
						edit_all_filtered(file_path, len, filters);
						break;
					}

					// Просим у пользователя подтверждение операции и заодно считаем кол-во элементов
					int edit_len;
					printf("\nДля изменения выбраны следующие записи:\n%d", to_edit[0]);
					for (edit_len = 1; to_edit[edit_len]; edit_len++) printf(", %d", to_edit[edit_len]);

					// Удаляем все указанные записи
					edit_from_array(file_path, len, to_edit, edit_len);
					free(to_edit);
				} while (0);  // Костыль для удобного выхода в нужный момент
				printf("\nНажмите любую кнопку, чтобы продолжить");
				_getch();
			}
			// 3 - Удаление записей по номерам
			else if (edit_action == 3) {
				do {
					system("cls");
					int len = print_flights(filters, 1, 1, 1);  // Сколько записей сейчас в таблице
					if (len < 1) break;
					else printf("\n");

					printf("\nВведите 0, чтобы удалить все вышепоказанные записи.");
					printf("\nВведите комера записей (1-%d), которые хотите удалить, через запятую: ", len);
					int* to_del;  // Массив индексов на удаление
					int res;  // Результат ввода
					res = int_array_input(&to_del, len);

					// Обработка ошибок
					if (res == -1) printf("\nОшибка выделения памяти.");
					else if (res == 1) printf("\nУдаление записей отменено.");
					else if (res == 2 || res == 3) printf("\nНекорректный ввод.");
					if (res) break;
					
					if (to_del[0] == 0) {  // Если это "полный массив"
						// Просим у пользователя подтверждение операции
						printf("\nВы уверены, что хотите удалить все эти записи?\n");
						printf("\n0 - Отмена\n");
						printf("1 - Удалить\n");
						int confirm;  // Буфер для ввода
						if (int_input(&confirm) || confirm != 1) {
							printf("\nУдаление отменено.");
						}
						else {
							delete_all_filtered(file_path, len, filters);
							printf("\nЗаписи успешно удалены");
						}
						break;
					}

					// Просим у пользователя подтверждение операции и заодно считаем кол-во элементов
					int del_len;
					printf("\nВы уверены, что хотите удалить следующие записи:\n%d", to_del[0]);
					for (del_len = 1; to_del[del_len]; del_len++) printf(", %d", to_del[del_len]);
					printf("\n0 - Отмена\n");
					printf("1 - Удалить\n");
					int confirm;  // Буфер для ввода
					if (int_input(&confirm) || confirm != 1) {
						free(to_del);
						printf("\nУдаление отменено.");
						break;
					}

					// Удаляем все указанные записи
					delete_from_array(file_path, len, to_del, del_len);
					free(to_del);
				} while (0);
				printf("\nНажмите любую кнопку, чтобы продолжить");
				_getch();
			}
			// 4 - Вернуться в главное меню
			else if (edit_action == 4);
		}
		// 3 - Обработка запроса по списку
		else if (first_action == 3) {
			do {
				// Выводим доступные фильтры
				if (!print_filters(filters)) break;

				printf("\n\nВведите 0, чтобы вернуться в главное меню.\n");
				printf("Введите номер столбца, чтобы настроить ему фильтр: ");
				int n, res;  // Выбранный столбец и результат ввода
				res = int_input(&n);
				if (res || n == 0) break;

				// Считаем, сколько фильтров
				int filters_num = 0;
				for (int fil = 0; fil < 2; fil++)
					filters_num += filters[fil].apply[n - 1];

				printf("\n\nВ любой момент вы можете ввести ### для отмены.\n");
				if (filters_num) {
					printf("\nВведите 0, чтобы удалить фильтр по этому столбцу.\n");
					for (int fil = 0; fil < 2; fil++) {
						if (filters[fil].apply[n - 1]) {
							printf("Введите %d, чтобы изменить фильтр \"", fil + 1);
							print_filter(filters[fil], n - 1, 1);
							printf("\"\n");
						}
						else printf("Введите %d, чтобы добавить фильтр №%d\n", fil + 1, fil + 1);
					}
					int choice;
					do res = int_input(&choice);
					while (res > 1 || (choice < 0 && filters_num < choice));
					if (res == 1) break;
					if (choice == 0) {
						for (int fil = 0; fil < 2; fil++)
							filters[fil].apply[n - 1] = 0;
						printf("\nФильтр удалён.");
						break;
					}
					else set_filter(&filters[choice - 1], n - 1, (choice - 1) == 0);
				}
				else set_filter(&filters[0], n - 1, 1);  // Иначе сразу устанавливаем фильтр
			} while (0);
			printf("\nНажмите любую кнопку, чтобы продолжить");
			_getch();
		}
		// 4 - Изменить путь до файла
		else if (first_action == 4) {
			if (change_path() == -1) {
				printf("\nДальнейшая работа невозможна\n");
				return 1;
			}
			printf("\nНажмите любую кнопку, чтобы продолжить");
			_getch();
		}
		// 5 - Выход из программы
		else if (first_action == 5) {
			int filters_num = 0;
			for (int fil = 0; fil < 2; fil++)
				for (int i = 0; i < 7; i++)
					filters_num += filters[fil].apply[i];
			if (filters_num) {  // Если есть хоть один фильтр
				// Просим у пользователя подтверждение операции
				printf("\nВы уверены, что хотите выйти?\n");
				printf("Все выбранные фильтры будут потеряны\n");
				printf("\n0 - Отмена\n");
				printf("1 - Выход\n");
				int confirm;  // Буфер для ввода
				if (!int_input(&confirm) && confirm == 1) run = 0;
			}
			else run = 0;
		}
	}
}