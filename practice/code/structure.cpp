#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>			// Для FILE, fopen, fclose, rewind, rename, remove
#include <stdlib.h>			// Для _itoa
#include <string.h>			// Для strcpy, strstr

#include "structure.h"
#include "file_funcs.h"		// Для FILE_NAME_LEN, get_file, read_line, write_line, count_lines

#include <errno.h>  // Обязательно подключить

// Стандартный strlwr не работает(
char* mystrlwr(char* string) {
	// Преобразовать буквы верхнего регистра строки string в буквы нижнего регистра
	// string: изменяемая строка
	for (int i = 0; string[i]; i++)
		if (('A' <= string[i]) && (string[i] <= 'Z')) string[i] += 'a' - 'A';
		else if (('А' <= string[i]) && (string[i] <= 'Я')) string[i] += 'а' - 'А';
	return string;
}

// Соответствует ли запись всем заданным фильтрам
int compare_flight(Flight flight, Flight_filter filters[]) {
	int is_good = 1;  // Запись изначально подходит
	for (int i = 0; i < FIELDS_NUM && is_good; i++)
		for (int fil = 0; fil < FILTERS_NUM; fil++) {
			Flight_filter cur_filter = filters[fil];	// Текущий фильтр
			if (!cur_filter.apply[i]) continue;			// Пропускаем, если его не нужно применить
			int cur_good = 1;  // Подходит ли текущее поле под текущий фильтр
			if (i == 0) {		// Поле fnum
				char flight_fnum[16], filter_fnum[16];
				_itoa(flight.fnum, flight_fnum, 10);
				_itoa(cur_filter.fnum, filter_fnum, 10);
				if (strstr(flight_fnum, filter_fnum) == NULL) cur_good = 0;
			}
			if (i == 1) {		// Поле name
				char flight_name[16], filter_name[16];
				mystrlwr(strcpy(flight_name, flight.name));
				mystrlwr(strcpy(filter_name, cur_filter.name));
				if (strstr(flight_name, filter_name) == NULL) cur_good = 0;
			}
			if (i == 2) {		// Поле dest
				char flight_dest[16], filter_dest[16];
				mystrlwr(strcpy(flight_dest, flight.dest));
				mystrlwr(strcpy(filter_dest, cur_filter.dest));
				if (strstr(flight_dest, filter_dest) == NULL) cur_good = 0;
			}
			if (i == 3) {		// Поле days
				int common = 0;
				for (int i = 0; i < 7 && cur_filter.days[i]; i++)
					for (int j = 0; j < 7 && flight.days[j]; j++)
						if (cur_filter.days[i] == flight.days[j]) common += 1;
				if (!common) cur_good = 0;
			}
			if (i == 4) {		// Поле dep_time
				if (cur_filter.apply[4] == 1)  // flight > filter
					if (flight.dep_time <= cur_filter.dep_time) cur_good = 0;
				if (cur_filter.apply[4] == 2)  // flight < filter
					if (flight.dep_time >= cur_filter.dep_time) cur_good = 0;
				if (cur_filter.apply[4] == 3)  // flight = filter
					if (flight.dep_time != cur_filter.dep_time) cur_good = 0;
				if (cur_filter.apply[4] == 4)  // flight >= filter
					if (flight.dep_time < cur_filter.dep_time) cur_good = 0;
				if (cur_filter.apply[4] == 5)  // flight <= filter
					if (flight.dep_time > cur_filter.dep_time) cur_good = 0;
			}
			if (i == 5) {		// Поле arr_time
				if (cur_filter.apply[5] == 1)  // flight > filter
					if (flight.arr_time <= cur_filter.arr_time) cur_good = 0;
				if (cur_filter.apply[5] == 2)  // flight < filter
					if (flight.arr_time >= cur_filter.arr_time) cur_good = 0;
				if (cur_filter.apply[5] == 3)  // flight = filter
					if (flight.arr_time != cur_filter.arr_time) cur_good = 0;
				if (cur_filter.apply[5] == 4)  // flight >= filter
					if (flight.arr_time < cur_filter.arr_time) cur_good = 0;
				if (cur_filter.apply[5] == 5)  // flight <= filter
					if (flight.arr_time > cur_filter.arr_time) cur_good = 0;
			}
			if (i == 6) {		// Поле price
				if (cur_filter.apply[6] == 1)  // flight > filter
					if (flight.price <= cur_filter.price) cur_good = 0;
				if (cur_filter.apply[6] == 2)  // flight < filter
					if (flight.price >= cur_filter.price) cur_good = 0;
				if (cur_filter.apply[6] == 3)  // flight = filter
					if (flight.price != cur_filter.price) cur_good = 0;
				if (cur_filter.apply[6] == 4)  // flight >= filter
					if (flight.price < cur_filter.price) cur_good = 0;
				if (cur_filter.apply[6] == 5)  // flight <= filter
					if (flight.price > cur_filter.price) cur_good = 0;
			}
			// Применяем логическую операцию
				 if (cur_filter.logic[i] == 0) is_good = is_good && cur_good;
			else if (cur_filter.logic[i] == 1) is_good = is_good || cur_good;
				 
		}
	return is_good;
}

// Открыть текущий файл table.csv для чтения и dable.csv для записи
int open_dable(char *file_path, char *new_file_path, FILE **new_table, FILE **old_table) {
	/*
	Возвращает:
		-1: Недостаток прав
		0: Успешное открытие
	*/
	*strstr(strcpy(new_file_path, file_path), "table") = 'd';  // Тот же путь, только .../dable.csv
	// Открываем dable.csv для записи
	*new_table = fopen(new_file_path, "w");
	if (new_table == NULL) return -1;
	// Открываем текущий файл table.csv для чтения
	*old_table = fopen(file_path, "r");
	if (old_table == NULL) {
		fclose(*new_table);
		return -1;
	}
	return 0;
}

// Изменение всех записей по фильтру или по указанным номерам
int edit_with_example(Flight_filter example, int filtered,
	int* to_edit, int edit_len) {
	/*
	Возвращает:
		-2: Ошибка чтения
		-1: Недостаток прав
		0: Успешное изменение
	*/
	int is_error = 0;	// Ошибка чтения
	// Получим путь до файла
	char file_path[FILE_NAME_LEN];
	if (get_file(file_path) == -1) return -1;
	// Создаём новый файл для записи
	char new_file_path[FILE_NAME_LEN];
	FILE* new_table, * old_table;
	if (open_dable(file_path, new_file_path, &new_table, &old_table) == -1) return -1;
	// Получаем фильтры
	Flight_filter filters[FILTERS_NUM];
	read_filters(filters);

	Flight buffer;		// Буфер для чтения полёта
	int len, fil_len;	// Количество записей в файле
	count_lines(old_table, filters, &len, &fil_len);
	rewind(old_table);

	if (filtered) {  // Если нужно изменить все подходящие под фильтр записи
		// Если строка не подходит под фильтр, то переписываем её
		// Иначе изменяем её по шаблону и записываем
		for (int cur_line = 0; cur_line < len && !is_error; cur_line++)
			if (read_line(old_table, &buffer) != FIELDS_NUM) is_error = 1;
			else if (!compare_flight(buffer, filters)) write_line(new_table, buffer);
			else {
				for (int i = 0; i < FIELDS_NUM; i++)
					if (i == 0 && example.apply[i])			buffer.fnum = example.fnum;
					else if (i == 1 && example.apply[i])	strcpy(buffer.name, example.name);
					else if (i == 2 && example.apply[i])	strcpy(buffer.dest, example.dest);
					else if (i == 3 && example.apply[i])	for (int j = 0; j < 7; j++) buffer.days[j] = example.days[j];
					else if (i == 4 && example.apply[i])	buffer.dep_time = example.dep_time;
					else if (i == 5 && example.apply[i])	buffer.arr_time = example.arr_time;
					else if (i == 6 && example.apply[i])	buffer.price = example.price;
				write_line(new_table, buffer);
			}
	}
	else {  // Если изменение по указанным номерам
		int last_edit = 0;	// Для прохода по массиву to_edit
		int cur_line = 0;	// Для прохода по файлу
		for (; cur_line < len && last_edit < edit_len && !is_error; cur_line++)
			if (read_line(old_table, &buffer) != FIELDS_NUM) is_error = 1;
			else if (cur_line + 1 < to_edit[last_edit]) write_line(new_table, buffer);
			else {
				for (int i = 0; i < FIELDS_NUM; i++)
					if (i == 0 && example.apply[i])			buffer.fnum = example.fnum;
					else if (i == 1 && example.apply[i])	strcpy(buffer.name, example.name);
					else if (i == 2 && example.apply[i])	strcpy(buffer.dest, example.dest);
					else if (i == 3 && example.apply[i])	for (int j = 0; j < 7; j++) buffer.days[j] = example.days[j];
					else if (i == 4 && example.apply[i])	buffer.dep_time = example.dep_time;
					else if (i == 5 && example.apply[i])	buffer.arr_time = example.arr_time;
					else if (i == 6 && example.apply[i])	buffer.price = example.price;
				write_line(new_table, buffer);
				last_edit++;
			}
		for (; cur_line < len && !is_error; cur_line++)
			if (read_line(old_table, &buffer) != FIELDS_NUM) is_error = 1;
			else write_line(new_table, buffer);

	}

	// Удаляем прошлый файл и переименовываем новый
	fclose(new_table);
	fclose(old_table);
	remove(file_path);
	rename(new_file_path, file_path);

	if (is_error) return -2;
	return 0;
}

// Удаление всех записей по фильтру или по указанным номерам
int delete_flights(int filtered, int* to_del, int del_len) {
	/*
	Возвращает:
		-2: Ошибка чтения
		-1: Недостаток прав
		0: Успешное изменение
	*/

	int is_error = 0;	// Ошибка чтения
	// Получим путь до файла
	char file_path[FILE_NAME_LEN];
	if (get_file(file_path) == -1) return -1;
	// Создаём новый файл для записи
	char new_file_path[FILE_NAME_LEN];
	FILE* new_table, * old_table;
	if (open_dable(file_path, new_file_path, &new_table, &old_table) == -1) return -1;
	// Получаем фильтры
	Flight_filter filters[FILTERS_NUM];
	read_filters(filters);

	Flight buffer;		// Буфер для чтения полёта
	int len, fil_len;	// Количество записей в файле
	count_lines(old_table, filters, &len, &fil_len);
	rewind(old_table);

	if (filtered) {  // Если нужно удалить все подходящие под фильтр записи
		// Если строка не подходит под фильтр, то переписываем её
		for (int cur_line = 0; cur_line < len && !is_error; cur_line++)
			if (read_line(old_table, &buffer) != FIELDS_NUM) is_error = 1;
			else if (!compare_flight(buffer, filters)) write_line(new_table, buffer);
	}
	else { // Если удаление по указанным номерам
		// Удаление будем совершать следующим образом:
		// Если номер строки в массиве - пропускаем её
		int last_del = 0;	// Для прохода по массиву to_edit
		int cur_line = 0;	// Для прохода по файлу
		for (; cur_line < len && last_del < del_len && !is_error; cur_line++)
			if (read_line(old_table, &buffer) != FIELDS_NUM) is_error = 1;
			else if (cur_line + 1 < to_del[last_del]) write_line(new_table, buffer);
			else last_del++;
		for (; cur_line < len && !is_error; cur_line++)
			if (read_line(old_table, &buffer) != FIELDS_NUM) is_error = 1;
			else write_line(new_table, buffer);
	}

	// Удаляем прошлый файл и переименовываем новый
	fclose(new_table);
	fclose(old_table);
	remove(file_path);
	rename(new_file_path, file_path);

	if (is_error) return -2;
	return 0;
}