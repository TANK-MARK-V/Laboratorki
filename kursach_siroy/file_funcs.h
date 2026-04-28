#pragma once

#include <windows.h>  // Очистка консоли и установка кодировки

#define DIR_NAME "flights_data"  // Название папки со всеми данными
#define FILE_NAME "table.csv"  // Название файла с таблицей
#define FILE_NAME_LEN 128  // Максимальная длина названия файла
#define CONF_NAME "settings.txt"  // Название файла с конифигурацией

#include "structure.h"

#define SETIO SetConsoleCP(1251); SetConsoleOutputCP(1251);  // Ввод и вывод на русском
#define UTF SetConsoleCP(65001); SetConsoleOutputCP(65001);  // Ввод и вывод на кодировке UTF

// Получить путь до файла, в который нужно написывать данные
int get_file(char file_path[], int buffer_len = FILE_NAME_LEN);

// Изменить путь до файла, в который нужно написывать данные
int change_path();

// Записать одну строчку файла в структуру
int read_line(FILE* table, Flight* flight);

// Записать одну структуру таблицы в файл
int write_line(FILE* table, Flight flight);

// Посчитать количество подходящих под фильтр строк
int count_lines(FILE* table, Flight_filter filters[], int* len, int* fil_len);
