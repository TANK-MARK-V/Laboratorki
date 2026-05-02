#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>			// Для FILE, fopen, fclose, fputs, printf
#include <conio.h>			// Для _getch
#include <windows.h>		// Для system, SetConsoleCP и SetConsoleOutputCP
#include <direct.h>			// Для _mkdir

#include "functions.h"
#include "structure.h"		// Для Flight_filter, set_filter
#include "input_funcs.h"	// Для int_input
#include "file_funcs.h"		// Для DIR_NAME, FILE_NAME, CONF_NAME, change_path, get_file


// Подготовка пользователя
int user_prepare(char *file_path) {
	/*
	Возвращает:
		-1: У пользователя нет прав даже для папки DIR_NAME
		0: Путь до файла успешно получен
		1: Слишком длинный путь (кто-то вручную поменял файл) - запись произойдёт по пути DIR_NAME/FILE_NAME
	*/
	system("mode con cols=140 lines=40");
	SetConsoleCP(1251); SetConsoleOutputCP(1251);

	printf("Mark Company Flights\n");
	int dir_res = _mkdir(DIR_NAME);  // Пробуем создать папку на случай, если её нету
	if (!dir_res) {  // Если папки не было, то это новый пользователь
		printf("Данные о полётах хранятся в файле table.csv.\n");
		printf("Путь по умолчанию: \"%s\". Хотите поменять путь? (вы сможете изменить его позже)\n", DIR_NAME "/" FILE_NAME);
		printf("0 - Нет\n");
		printf("1 - Да\n");
		int answer;					// Ответ на вопрос
		int use_default_path = 1;	// Флаг "использовать стандартный путь"
		if (!int_input(&answer) && answer == 1)
			if ((use_default_path = change_path()) == -1)
				printf("Ошибка получения прав доступа к файлу %s\n", DIR_NAME "/" FILE_NAME);
		if (use_default_path != 0) {
			// Сохраняем стандартный путь
			FILE* settings = fopen(DIR_NAME "/" CONF_NAME, "w");
			if (settings == NULL) printf("Ошибка получения прав доступа к файлу %s\n", DIR_NAME "/" CONF_NAME);
			else {
				fputs(DIR_NAME "/" FILE_NAME, settings);
				fclose(settings);
			}
			// Сохраняем создаём файл, если его не существует
			FILE* flights = fopen(DIR_NAME "/" FILE_NAME, "r");
			if (flights == NULL) {
				flights = fopen(DIR_NAME "/" FILE_NAME, "w");
				if (flights == NULL) printf("Ошибка получения прав доступа к файлу %s\n", DIR_NAME "/" FILE_NAME);
			}
			if (flights != NULL) fclose(flights);
		}
	}
	else printf("Убедитесь, что папка %s используется только программой.\n", DIR_NAME);
	printf("Нажмите любую кнопку, чтобы продолжить:");
	_getch();
	system("cls");
	int get_res;
	if ((get_res = get_file(file_path)) == -1)
		printf("Ошибка получения прав доступа к файлу %s\n", DIR_NAME "/" CONF_NAME);
	return get_res;
}

// Выбор первичного действия
int get_first_action(Flight_filter filters[]) {
	// Ввод пока не получим число от 1 до 5
	int action;  // Выбор пользователя
	do {
		system("cls");
		int len, fil_len;
		print_flights(filters, &len, &fil_len);
		if (fil_len) printf("\n");
		printf("Выберите действие:\n");
		printf("1 - Вывод таблицы\n");
		printf("2 - Ввод и корректировка списка\n");
		printf("3 - Установка фильтров\n");
		printf("4 - Изменить путь до файла\n");
		printf("5 - Выход из программы\n");
		printf("Ваш выбор: ");
	} while (int_input(&action) || (action < 1 || 5 < action));
	return action;
}

// Выбор действия по вводу и корректировке списка
int get_edit_action(Flight_filter filters[]) {
	// Ввод пока не получим число от 1 до 4
	int action;  // Выбор пользователя
	do {
		system("cls");
		int len, fil_len;
		print_flights(filters, &len, &fil_len);
		if (fil_len) printf("\n");
		printf("Выберите действие по вводу и корректировке:\n");
		printf("1 - Ввод таблицы\n");
		printf("2 - Изменение записей\n");
		printf("3 - Удаление записей\n");
		printf("4 - Вернуться в главное меню\n");
		printf("Ваш выбор: ");
	} while (int_input(&action) || (action < 1 || 4 < action));
	return action;
}

// Меню "Изменение записей"
int edit_menu(char *file_path, Flight_filter filters[]) {
	system("cls");
	int len, fil_len;
	print_flights(filters, &len, &fil_len, 1);
	if (fil_len == 0) return 0;

	printf("\nВведите 0, чтобы изменить все вышепоказанные записи.");
	printf("\nВведите комера записей (1-%d), которые хотите изменить, через запятую: ", len);
	int* to_edit;  // Массив индексов на удаление
	int res;  // Результат ввода
	res = int_array_input(&to_edit, len);

	// Обработка ошибок
		 if (res == -1) printf("\nОшибка выделения памяти.");
	else if (res == 1) printf("\nИзменение записей отменено.");
	else if (res == 2 || res == 3) printf("\nНекорректный ввод.");

	else if (to_edit[0] == 0) {  // Если это "полный массив"
		free(to_edit);
		printf("\nВыбрано изменение всех записей по фильтру\n");
		int edit_result = edit_all_filtered(file_path, filters);
			 if (edit_result == -2) printf("\nПроизошла ошибка чтения. Не все строки были были изменены");
		else if (edit_result == -1) printf("\nИзменение отменено по причине недостатка прав");
		else if (edit_result == 0) printf("\nИзменение завершено");
		else if (edit_result == 1) printf("\nИзменение отменено");
	}
	else {  // Просим у пользователя подтверждение операции и заодно считаем кол-во элементов
		int edit_len;
		printf("\nДля изменения выбраны следующие записи:\n%d", to_edit[0]);
		for (edit_len = 1; to_edit[edit_len]; edit_len++) printf(", %d", to_edit[edit_len]);

		// Изменяем все указанные записи
		int edit_result = edit_from_array(file_path, len, to_edit, edit_len);
			 if (edit_result == -2) printf("\nПроизошла ошибка чтения. Не все строки были были изменены");
		else if (edit_result == -1) printf("\nИзменение отменено по причине недостатка прав");
		else if (edit_result == 0) printf("\nИзменение завершено");
		else if (edit_result == 1) printf("\nИзменение отменено");
		free(to_edit);
	}
	return 1;
}

// Меню "Удаление записей"
int delete_menu(char *file_path, Flight_filter filters[]) {
	system("cls");
	int len, fil_len;
	print_flights(filters, &len, &fil_len, 1);
	if (fil_len == 0) return 0;

	printf("\nВведите 0, чтобы удалить все вышепоказанные записи.");
	printf("\nВведите комера записей (1-%d), которые хотите удалить, через запятую: ", len);
	int* to_del;  // Массив индексов на удаление
	int res;  // Результат ввода
	res = int_array_input(&to_del, len);

	// Обработка ошибок
		 if (res == -1) printf("\nОшибка выделения памяти.");
	else if (res == 1) printf("\nУдаление записей отменено.");
	else if (res == 2 || res == 3) printf("\nНекорректный ввод.");

	else if (to_del[0] == 0) {  // Если это "полный массив"
		free(to_del);
		// Просим у пользователя подтверждение операции
		printf("\nВы уверены, что хотите удалить все эти записи?\n");
		printf("\n0 - Отмена\n");
		printf("1 - Удалить\n");
		int confirm;  // Буфер для ввода
		if (int_input(&confirm) || confirm != 1) printf("\nУдаление отменено.");
		else {
			int delete_result = delete_all_filtered(file_path, filters);
				 if (delete_result == -2) printf("\nПроизошла ошибка чтения. Не все строки были удалены");
			else if (delete_result == -1) printf("\nУдаление отменено по причине недостатка прав");
			else if (delete_result == 0) printf("\nУдаление завершено");
		}
	}
	else {  // Просим у пользователя подтверждение операции и заодно считаем кол-во элементов
		int del_len;
		printf("\nВы уверены, что хотите удалить следующие записи:\n%d", to_del[0]);
		for (del_len = 1; to_del[del_len]; del_len++) printf(", %d", to_del[del_len]);
		printf("\n0 - Отмена\n");
		printf("1 - Удалить\n");
		int confirm;  // Буфер для ввода
		if (int_input(&confirm) || confirm != 1) printf("\nУдаление отменено.");
		else {  // Удаляем все указанные записи
			int delete_result = delete_from_array(file_path, len, to_del, del_len);
				 if (delete_result == -2) printf("\nПроизошла ошибка чтения. Не все строки были удалены");
			else if (delete_result == -1) printf("\nУдаление отменено по причине недостатка прав");
			else if (delete_result == 0) printf("\nУдаление завершено");
		}
		free(to_del);
	}
}


// Меню "Установка фильтров"
int filters_menu(Flight_filter filters[]) {
	if (print_filters(filters) == 0) return 0;
	printf("\n\n");
	printf("Введите 0, чтобы вернуться в главное меню.\n");
	printf("Введите номер столбца, чтобы настроить ему фильтр: ");
	int filters_num = 0;	// Кол-во фильтров (считаем позже)
	int n, res;				// Выбранный столбец и результат ввода
	res = int_input(&n);
	if (res || n == 0) return 1;

	// Считаем, сколько фильтров по указанному полю
	for (int fil = 0; fil < 2; fil++)
		filters_num += filters[fil].apply[n - 1];

	printf("\n\nВ любой момент вы можете ввести %s для отмены.\n", CANCEL);
	if (filters_num) {  // Если есть хоть один фильтр
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
		if (res == 1);  // Выход по ###
		else if (choice == 0) {
			for (int fil = 0; fil < 2; fil++)
				filters[fil].apply[n - 1] = 0;
			printf("\nФильтр удалён.");
		}
		else set_filter(&filters[choice - 1], n - 1, (choice - 1) == 0);
	}
	else set_filter(&filters[0], n - 1, 1);  // Иначе сразу устанавливаем фильтр
	return 2;
}
