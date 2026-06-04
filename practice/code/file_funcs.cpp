#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>			// Для FILE, fopen, fclose, fgets, fputs, printf, remove
#include <string.h>			// Для strlen, strcat, strstr, _strnset
#include <direct.h>			// Для _mkdir

#include "file_funcs.h"
#include "structure.h"		// Для FIELDS_NUM, Flight, Flight_filter

// Проверка, влезло ли название файла FILE_NAME в строку
int correct_name(char *file_path) {
	char* file_pntr = strstr(file_path, ".csv");  // Указатель на расширение
	if (file_pntr == NULL)
		return 0;
	return 1;
}

// Получить путь до файла, в который нужно написывать данные
int get_file(char *file_path, int buffer_len) {
	/*
	Возвращает:
		-1: У пользователя нет прав даже для папки DIR_NAME
		0: Путь до файла успешно получен
		1: Слишком длинный путь (кто-то вручную поменял файл) - запись произойдёт по пути DIR_NAME/FILE_NAME
		2: У пользователя нет прав для создания файла - запись произойдёт по пути DIR_NAME/FILE_NAME
	*/
	_mkdir(DIR_NAME);  // Пробуем создать папку на случай, если её нету
	FILE* settings = fopen(DIR_NAME "/" CONF_NAME, "a+");
	if (!settings) return -1;
	rewind(settings);

	// Если файл пустой, то возвращаем путь DIR_NAME/FILE_NAME
	char password[256];
	if (fgets(password, 256, settings) == NULL) {
		strcpy(password, "root");
		strcpy(file_path, DIR_NAME "/" FILE_NAME);
		fclose(settings);
		return 0;
	}
	else if (fgets(file_path, FILE_NAME_LEN, settings) == NULL) {
		strcpy(file_path, DIR_NAME "/" FILE_NAME);
		fclose(settings);
		return 0;
	}
	else fclose(settings);
	
	// Меняем \n на \0
	if (file_path[strlen(file_path) - 1] == '\n')
		file_path[strlen(file_path) - 1] = '\0';

	if (!correct_name(file_path))  {
		strcpy(file_path, DIR_NAME "/" FILE_NAME);
		return 1;  // Возвращаем путь DIR_NAME / FILE_NAME и код "путь не влез"
	}

	// Создаём файл, если его нет
	FILE* table = fopen(file_path, "r");
	if (table == NULL) {
		table = fopen(file_path, "w");
		if (table == NULL) {
			strcpy(file_path, DIR_NAME "/" FILE_NAME);
			return -2;
		}
		fclose(table);
	}
	else fclose(table);
	return 0;
}

// Получить пароль
int get_password(char* password, int buffer_len) {
	/*
	Возвращает:
		-1: У пользователя нет прав даже для папки DIR_NAME
		0: Пароль успешно получен
	*/
	_mkdir(DIR_NAME);  // Пробуем создать папку на случай, если её нету
	FILE* settings = fopen(DIR_NAME "/" CONF_NAME, "a+");
	if (!settings) return -1;
	rewind(settings);

	// Если файл пустой, то возвращаем пароль root
	if (fgets(password, PASSWORD_LEN, settings) == NULL) {
		strcpy(password, "root");
		fclose(settings);
		return 0;
	}
	else fclose(settings);

	// Меняем \n на \0
	if (password[strlen(password) - 1] == '\n')
		password[strlen(password) - 1] = '\0';
	return 0;
}

// Записать одну строчку файла в структуру
int read_line(FILE *table, Flight *flight) {
	int days = 0;  // Хранение дней в int, например [1, 2, 4] -> 1240000
	int res = fscanf(table, "%d;%31[^;];%31[^;];%d;%d;%d;%lf",
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

// Прочитать фильтры из файла DIR_NAME/filters.csv в массив 
int read_filters(Flight_filter filters[FILTERS_NUM]) {
	FILE* filters_table = fopen(DIR_NAME "/filters.csv", "r");
	if (filters_table == NULL) return -2;
	for (int f = 0; f < FILTERS_NUM; f++) {
		int days = 0;				// Хранение дней в int, например [1, 2, 4] -> 1240000
		int apply = 0, logic = 0;	// Похожее для apply и logic: [1, 0, 1] -> 101
		int res = fscanf(filters_table, "%d;%31[^;];%31[^;];%d;%d;%d;%lf;%d;%d",
			&(filters[f].fnum),
			filters[f].name,
			filters[f].dest,
			&days,
			&(filters[f].dep_time),
			&(filters[f].arr_time),
			&(filters[f].price),
			&apply,
			&logic);
		if (res != FIELDS_NUM + 2) {
			fclose(filters_table);
			return res;
		}
		for (int i = 6; i >= 0; i--) {  // Переводим int days в массив
			filters[f].days[i] = days % 10;
			days /= 10;
		}
		for (int i = FIELDS_NUM - 1; i >= 0; i--) {  // Переводим int apply и logic в массивы
			filters[f].apply[i] = apply % 10;
			apply /= 10;
			filters[f].logic[i] = logic % 10;
			logic /= 10;
		}
	}
	fclose(filters_table);
	return 0;
}

// Записать фильтры массива в файл DIR_NAME/filters.csv
int write_filters(Flight_filter filters[FILTERS_NUM]) {
	FILE* filters_table = fopen(DIR_NAME "/filters.csv", "w");
	if (filters_table == NULL) return -2;
	for (int f = 0; f < FILTERS_NUM; f++) {
		int days = 0;				// Хранение дней в int, например [1, 2, 4] -> 1240000
		int apply = 0, logic = 0;	// Похожее для apply и logic: [1, 0, 1] -> 101
		for (int i = 0; i < 7; i++) days = days * 10 + filters[f].days[i];
		for (int i = 0; i < FIELDS_NUM; i++) {
			apply = apply * 10 + filters[f].apply[i];
			logic = logic * 10 + filters[f].logic[i];
		}
		int res = fprintf(filters_table, "%d;%s;%s;%d;%d;%d;%lf;%d;%d\n",
			filters[f].fnum,
			filters[f].name,
			filters[f].dest,
			days,
			filters[f].dep_time,
			filters[f].arr_time,
			filters[f].price,
			apply,
			logic);
	}
	fclose(filters_table);
	return 0;
}

// Перенести данные из String^ в char*
void copy_char_from_string(char* buffer, int len, System::String^ string) {
	System::IntPtr ptr = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(string);
	char* char_data = (char*)ptr.ToPointer();
	strncpy(buffer, char_data, len);
	buffer[len - 1] = '\0';
	System::Runtime::InteropServices::Marshal::FreeHGlobal(ptr);
}

// Перевести данные из String^ формата ЧЧ:ММ в int
int convert_string_time(System::String^ string) {
	// Возвращает результат перевода (-1, при ошибке

	int time[5];	// Буфер для хранения времени

	// Перебор двух символов ЧЧ (которые обязаны присутствовать)
	for (int i = 0; i < 2; i++)
		if (string[i] != ' ')
			time[i] = string[i] - '0';  // Делаем переход char->int
		else time[i] = 0; // Стоит пробел

	// Перебор двух символов ММ (которых может не быть)
	for (int i = 3; i < 5; i++)
		if (i < string->Length)  // Если ещё есть символы
			if (string[i] != ' ')
				time[i] = string[i] - '0';  // Делаем переход char->int
			else time[i] = 0; // Стоит пробел
		else
			time[i] = 0;  // Проставляем нолики

	// Проверяем на корректность формата
	if ((time[0] * 10 + time[1] > 23) || (time[3] > 5)) return -1;
	// Возвращаем время
	return (time[0] * 10 + time[1]) * 60 + time[3] * 10 + time[4];
}