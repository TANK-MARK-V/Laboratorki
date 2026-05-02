#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>			// Для FILE, fopen, fclose, fgets, fputs, printf, remove
#include <string.h>			// Для strlen, strcat, strstr, _strnset
#include <direct.h>			// Для _mkdir

#include "file_funcs.h"
#include "structure.h"		// Для FIELDS_NUM, Flight, Flight_filter
#include "input_funcs.h"	// Для input, int_input


// Проверка, влезло ли название файла FILE_NAME в строку
int correct_name(char *file_path) {
	char* file_pntr = strstr(file_path, FILE_NAME);  // Указатель на начало названия файла в строке
	if (file_pntr == NULL)
		return 0;  // Если в строке вообще нет названия файла
	if (file_pntr - file_path + strlen(FILE_NAME) != strlen(file_path))
		return 0;  // Если название файла не в конце
	return 1;
}

// Получить путь до файла, в который нужно написывать данные
int get_file(char *file_path, int buffer_len) {
	/*
	Возвращает:
		-1: У пользователя нет прав даже для папки DIR_NAME
		0: Путь до файла успешно получен
		1: Слишком длинный путь (кто-то вручную поменял файл) - запись произойдёт по пути DIR_NAME/FILE_NAME
	*/
	_mkdir(DIR_NAME);  // Пробуем создать папку на случай, если её нету
	FILE* settings = fopen(DIR_NAME "/" CONF_NAME, "a+");
	if (!settings) return -1;
	rewind(settings);

	// Если файл пустой, то возвращаем путь DIR_NAME/FILE_NAME
	if (fgets(file_path, buffer_len, settings) == NULL) {
		strcpy(file_path, DIR_NAME "/" FILE_NAME);
		fclose(settings);
		return 0;
	}
	fclose(settings);
	
	// Меняем \n на \0
	if (file_path[strlen(file_path) - 1] == '\n')
		file_path[strlen(file_path) - 1] = '\0';

	if (!correct_name(file_path))  {
		strcpy(file_path, DIR_NAME "/" FILE_NAME);
		return 1;  // Возвращаем путь DIR_NAME / FILE_NAME и код "путь не влез"
	}
	return 0;
}

// Изменить путь до файла, в который нужно написывать данные
int change_path() {
	/*
	Возвращает:
		-1: У пользователя нет прав даже для папки DIR_NAME
		0: Путь до файла успешно получен
		1: Отмена ввода
	*/
	char old_file_path[FILE_NAME_LEN];  // Буфер для хранения пути до файла
	int old_exists = 0;  // Путь до файла, указанный в settings.txt существует и корректен
	FILE* old_file;

	// Пробуем прочитать файл
	FILE* settings = fopen(DIR_NAME "/" CONF_NAME, "r");
	if (settings == NULL) {  // Если файла нет, то создаём его
		settings = fopen(DIR_NAME "/" CONF_NAME, "w");
		if (settings == NULL) return -1;  // Если его нельзя создать, то возвращаем -1
		else fclose(settings);
		settings = fopen(DIR_NAME "/" CONF_NAME, "r");
	}
	// Если файл не пустой, то выведем информацию о пути
	if (fgets(old_file_path, FILE_NAME_LEN, settings) != NULL) {
		old_exists = correct_name(old_file_path);
		printf("Текущий путь до файла %s", old_file_path);
		if (!old_exists) printf(" является некорректным");
		printf("\n");
	}
	fclose(settings);

	// Ввод нового адреса и его проверка
	printf("Данные о полётах хранятся в файле table.csv.\n");
	printf("Введите новый адрес файла, например %s. Максимальная длина %d символов\n",
		DIR_NAME "/" FILE_NAME, FILE_NAME_LEN - 1);

	int new_file_error = 1;				// Некорректно указан новый адрес
	char new_file_path[FILE_NAME_LEN];	// Буфер для хранения пути до файла
	FILE* new_file;						// Новый файл

	while (new_file_error) {
		if (input(new_file_path, FILE_NAME_LEN) == 1) return 1;  // Отмена ввода
		if (!correct_name(new_file_path))
			printf("Некорректно указан новый адрес: названия файла нет в строке или не в конце\n");
		else  // Проверим, что файл уже существует или его можно создать
			if (new_file = fopen(new_file_path, "r")) {
				printf("УСПЕШНО: файл по указанному адресу существует\n");
				fclose(new_file);
				new_file_error = 0;
			}
			else
				if (new_file = fopen(new_file_path, "w")) {
					printf("УСПЕШНО: файл по указанному адресу создан\n");
					fclose(new_file);
					new_file_error = 0;
				}
				else printf("Некорректно указан новый адрес\n");
	}

	// Проверим, что файл по адресу в файле существует
	if (old_exists) {
		old_file = fopen(old_file_path, "r");
		if (old_file == NULL) old_exists = 0;
		else fclose(old_file);
	}
	// Нужно ли перенести информацию из прошлого файла в новый
	if (old_exists) {
		printf("\nНужно ли перенести информацию из прошлого файла в новый?\n");
		printf("0 - Нет\n");
		printf("1 - Да\n");
		int adding_res;
		if (!int_input(&adding_res) && adding_res == 1 &&  // Если пользователь ввёл 1
			(old_file = fopen(old_file_path, "r")) != NULL) {  // Если файл существует (да-да, ещё одна проверка)
			char read_buffer[64];  // Буфер для переноса
			if ((new_file = fopen(new_file_path, "a")) == NULL) // Если не получилось открыть новый файл
				printf("Произошла ошибка, информация не была перенесена\n");
			else {
				while (fgets(read_buffer, 64, old_file) != NULL)
					fputs(read_buffer, new_file);
				fclose(new_file);
			}
			fclose(old_file);
		}
	}
	// Нужно ли удалить прошлый файл
	if (old_exists) {
		printf("\nНужно ли удалить прошлый файл?\n");
		printf("0 - Нет\n");
		printf("1 - Да\n");
		int adding_res;
		if (!int_input(&adding_res) && adding_res == 1) {
			remove(old_file_path);
			printf("Файла больше не существует >:3\n");
		}
	}
	// Записываем адрес нового файла в settings.txt
	settings = fopen(DIR_NAME "/" CONF_NAME, "w");
	if (settings == NULL) return -1;  // Если его нельзя создать, то возвращаем -1
	fputs(new_file_path, settings);
	fclose(settings);
	return 0;
}

// Записать одну строчку файла в структуру
int read_line(FILE *table, Flight *flight) {
	int days = 0;  // Хранение дней в int, например [1, 2, 4] -> 1240000
	int res = fscanf(table, "%d;%15[^;];%15[^;];%d;%d;%d;%lf",
		&flight->fnum,
		flight->name,
		flight->dest,
		&days,
		&flight->dep_time,
		&flight->arr_time,
		&flight->price);
	for (int i = 6; i >= 0; i--) {  // Переводим int days в массив
		flight->days[i] = days % 10;
		days /= 10;
	}
	return res;
}

// Записать одну структуру таблицы в файл
int write_line(FILE *table, Flight flight) {
	int days = 0;  // Хранение дней в int, например [1, 2, 4] -> 1240000
	// Переводим массив в int days
	for (int i = 0; i < 7; i++) days = days * 10 + flight.days[i];
	int res = fprintf(table, "%d;%s;%s;%d;%d;%d;%lf\n",
		flight.fnum,
		flight.name,
		flight.dest,
		days,
		flight.dep_time,
		flight.arr_time,
		flight.price);
	return res;
}

// Посчитать количество подходящих под фильтр строк
int count_lines(FILE *table, Flight_filter filters[], int *len, int *fil_len) {
	*len = 0;		// Сколько записей получилось успешно прочитать
	*fil_len = 0;	// Сколько записей, подходящих фильтрам, получилось успешно прочитать
	/*
	После использования рекомендуется использовать rewind()
	Возвращает:
		0: все строки успешно прочитаны или файл пустой
		1: не все строки были прочитаны и файл не пустой
		-1: ни одна строка не была прочитана, но файл не пустой
	*/
	
	Flight flight_buffer;  // Буфер для чтения
	int col_num;  // Сколько столбцов успешно прочитано

	while ((col_num = read_line(table, &flight_buffer)) == FIELDS_NUM) {
		*len = *len + 1;
		if (compare_flight(flight_buffer, filters))
			*fil_len = *fil_len + 1;  // Только если подходит под фильтр
	}
	if (*len != 0)
		return (col_num != EOF);
	return -(col_num != EOF);
}