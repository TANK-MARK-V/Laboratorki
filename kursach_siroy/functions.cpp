#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>  // Стандартный вход/выход
#include <locale.h>  // Вывод на русском языке
#include <conio.h>  // Задержка экрана

#include <string.h>  // Работа со строками

#include <windows.h>  // Очистка консоли и установка кодировки
#include <direct.h>  // Работа с файлами


#include "input_funcs.h"  // Функции для ввода
#include "file_funcs.h"  // Файловые функции
#include "functions.h"  // Вспомогательные функции

// Подготовка пользователя
int user_prepare(char file_path[]) {
	system("color F0");
	system("mode con cols=140 lines=40");
	SETIO;
	printf("Mark Company Flights\n");
	int dir_res = _mkdir(DIR_NAME);  // Пробуем создать папку на случай, если её нету
	if (!dir_res) {
		printf("Данные о полётах хранятся в файле table.csv.\n");
		printf("Путь по умолчанию: \"%s/%s\". Хотите поменять путь? (вы сможете изменить его позже)\n", DIR_NAME, FILE_NAME);
		printf("0 - Нет\n");
		printf("1 - Да\n");
		int new_path_res;
		if (!int_input(&new_path_res) && new_path_res == 1) {
			if (change_path() == -1) printf("Ошибка получения прав доступа к файлу %s/%s\n", DIR_NAME, CONF_NAME);
		}
		else {
			// Сохраняем имя в settings.txt
			FILE* settings = fopen(DIR_NAME "/" CONF_NAME, "w");
			if (settings == NULL) printf("Ошибка получения прав доступа к файлу %s/%s\n", DIR_NAME, CONF_NAME);
			else {
				fputs(DIR_NAME "/" FILE_NAME, settings);
				fclose(settings);
			}
			// Сохраняем создаём файл, если его не существует
			FILE* flights = fopen(DIR_NAME "/" FILE_NAME, "r");
			if (flights == NULL) {
				flights = fopen(DIR_NAME "/" FILE_NAME, "w");
				if (flights == NULL) printf("Ошибка получения прав доступа к файлу %s/%s\n", DIR_NAME, FILE_NAME);
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
		printf("Ошибка получения прав доступа к файлу %s/%s\n", DIR_NAME, CONF_NAME);
	return get_res;
}

// Выбор первичного действия
int get_first_action(Flight_filter filters[]) {
	// Ввод пока не получим число от 1 до 4
	int action;  // Выбор пользователя
	do {
		system("cls");
		print_flights(filters, 1, 0);
		printf("\nВыберите действие:\n");
		printf("1 - Вывод таблицы\n");
		printf("2 - Ввод и корректировка списка\n");
		printf("3 - Обработка запроса по списку\n");
		printf("4 - Изменить путь до файла\n");
		printf("5 - Выход из программы\n");
	} while (int_input(&action) || (action < 1 || 5 < action));
	return action;
}

// Выбор действия по вводу и корректировке списка
int get_edit_action(Flight_filter filters[]) {
	// Ввод пока не получим число от 1 до 4
	int action;  // Выбор пользователя
	do {
		system("cls");
		print_flights(filters, 1, 0);
		printf("\nВыберите действие по вводу и корректировке:\n");
		printf("1 - Ввод таблицы\n");
		printf("2 - Изменение записи по номеру\n");
		printf("3 - Удаление записей по номерам\n");
		printf("4 - Вернуться в главное меню\n");
	} while (int_input(&action) || (action < 1 || 4 < action));
	return action;
}

