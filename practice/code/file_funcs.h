#pragma once


#define DIR_NAME "flights_data"		// Название папки со всеми данными
#define FILE_NAME "table.csv"		// Название файла с таблицей
#define FILE_NAME_LEN 512			// Максимальная длина названия файла
#define CONF_NAME "settings.txt"	// Название файла с конифигурацией
#define PASSWORD_LEN 256			// Максимальная длина пароля

#include <stdio.h>		// Для FILE
#include "structure.h"	// Для Flight, Flight_filter

// Проверка, влезло ли название файла FILE_NAME в строку
int correct_name(char *file_path);

// Получить путь до файла, в который нужно написывать данные
int get_file(char *file_path, int buffer_len = FILE_NAME_LEN);

// Получить пароль
int get_password(char* password, int buffer_len = PASSWORD_LEN);

// Записать одну строчку файла в структуру
int read_line(FILE *table, Flight *flight);

// Записать одну структуру таблицы в файл
int write_line(FILE *table, Flight flight);

// Посчитать количество подходящих под фильтр строк
int count_lines(FILE *table, Flight_filter filters[], int *len, int *fil_len);

// Прочитать фильтры из файла DIR_NAME/filters.csv в массив 
int read_filters(Flight_filter filterts[FILTERS_NUM]);

// Записать фильтры массива в файл DIR_NAME/filters.csv
int write_filters(Flight_filter filterts[FILTERS_NUM]);

// Перенести данные из String^ в char*
void copy_char_from_string(char* buffer, int len, System::String^ string);

// Перевести данные из String^ формата ЧЧ:ММ в int
int convert_string_time(System::String^ string);