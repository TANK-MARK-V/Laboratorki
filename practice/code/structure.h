#pragma once

#include <stdio.h>

#define TEXT_LEN 32		// Сколько памяти нужно выделить на хранение текстовых полей
#define FIELDS_NUM 7	// Количество полей структуры
#define FILTERS_NUM 2	// Сколько фильтров можно одновременно использовать

// Структура информации о полёте
typedef struct {
	int fnum;				// Номер рейса             (flight number)
	char name[TEXT_LEN];	// Тип самолёта            (название модели)
	char dest[TEXT_LEN];	// Пункт назначения        (destination)
	int days[7];			// Дни отправления
	int dep_time;			// Время вылета в минутах  (departure time)
	int arr_time;			// Время прилёта в минутах (arrival time)
	double price;			// Цена билета             (десятичная дробь)
} Flight;

// Структура для фильтров записей
typedef struct {
	int fnum;				// Номер рейса             (flight number)
	char name[TEXT_LEN];	// Тип самолёта            (название модели)
	char dest[TEXT_LEN];	// Пункт назначения        (destination)
	int days[7];			// Дни отправления
	int dep_time;			// Время вылета в минутах  (departure time)
	int arr_time;			// Время прилёта в минутах (arrival time)
	double price;			// Цена билета             (десятичная дробь)

	int apply[FIELDS_NUM];   // Какие столбцы нужно фильтровать (и каким образом)
	int logic[FIELDS_NUM];	// Какую операцию нужно применять при сложени фильтров
} Flight_filter;


// Соответствует ли запись всем заданным фильтрам
int compare_flight(Flight flight, Flight_filter filters[]);


// Удаление и изменение записей
// Открыть текущий файл table.csv для чтения и dable.csv для записи
int open_dable(char *file_path, char *new_file_path, FILE **new_table, FILE **old_table);

// Изменение всех записей по фильтру или по указанным номерам
int edit_with_example(Flight_filter example, int filtered, int* to_edit, int edit_len);

// Удаление всех записей по фильтру или по указанным номерам
int delete_flights(int filtered, int* to_del, int del_len);