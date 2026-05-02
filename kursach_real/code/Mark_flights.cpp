#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>		// Для printf, FILE, fclose
#include <conio.h>		// Для _getch
#include <stdlib.h>		// Для system, free
// Все доп. файлы
#include "functions.h"
#include "structure.h"
#include "input_funcs.h"
#include "file_funcs.h"


int main() {
	// Подготовка пользователя
	char file_path[FILE_NAME_LEN];  // Путь до файла
	if (user_prepare(file_path) == -1) {
		printf("\nДальнейшая работа невозможна\n");
		return 1;
	}

	// Создаём фильтры
	Flight_filter filters[FILTERS_NUM];
	for (int fil = 0; fil < FILTERS_NUM; fil++)
		for (int i = 0; i < FIELDS_NUM; i++)
			filters[fil].apply[i] = filters[fil].logic[i]= 0;  // Обнуляем фильтр
	
	int run = 1;  // Программа работает
	while (run) {
		int first_action = get_first_action(filters);
		// 1 - Вывод таблицы
		if (first_action == 1) {
			system("cls");
			int len, fil_len;
			print_flights(filters, &len, &fil_len, 1);
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
			// 2 - Изменение записей
			else if (edit_action == 2) {
				edit_menu(file_path, filters);
				printf("\nНажмите любую кнопку, чтобы продолжить");
				_getch();
			}
			// 3 - Удаление записей
			else if (edit_action == 3) {
				delete_menu(file_path, filters);
				printf("\nНажмите любую кнопку, чтобы продолжить");
				_getch();
			}
			// 4 - Вернуться в главное меню
			else if (edit_action == 4);
		}
		// 3 - Установка фильтров
		else if (first_action == 3) {
			filters_menu(filters);
			printf("\nНажмите любую кнопку, чтобы продолжить");
			_getch();
		}
		// 4 - Изменить путь до файла
		else if (first_action == 4) {
			system("cls");
			if (change_path() == -1) {
				printf("\nДальнейшая работа невозможна\n");
				return 1;
			}
			int get_res;
			if ((get_res = get_file(file_path)) == -1) {
				printf("Ошибка получения прав доступа к файлу %s\n", DIR_NAME "/" CONF_NAME);
				printf("\nДальнейшая работа невозможна\n");
				return 1;
			}
			printf("\nНажмите любую кнопку, чтобы продолжить");
			_getch();
		}
		// 5 - Выход из программы
		else if (first_action == 5) {
			int cur_filters_num = 0;
			for (int fil = 0; fil < FILTERS_NUM; fil++)
				for (int i = 0; i < FIELDS_NUM; i++)
					cur_filters_num += filters[fil].apply[i];
			if (cur_filters_num) {  // Если есть хоть один фильтр
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