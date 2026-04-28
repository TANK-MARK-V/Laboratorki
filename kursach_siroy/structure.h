#pragma once

#define TEXT_LEN 16

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

	int apply[7];   // Какие столбцы нужно фильтровать (и каким образом)
	int logic[7];	// Какую операцию нужно применять при сложени фильтров
} Flight_filter;


// Ввод структуры
// Ввод поля fnum
int input_fnum(Flight* pointer);

// Ввод поля name
int input_name(Flight* pointer);

// Ввод поля dest
int input_dest(Flight* pointer);

// Ввод поля days
int input_days(Flight* pointer);

// Ввод поля dep_time
int input_dep_time(Flight* pointer);

// Ввод поля arr_time
int input_arr_time(Flight* pointer);

// Ввод поля price
int input_price(Flight* pointer);

// Ввод полной структуры
int input_flight(Flight* pointer);


// Вывод структур
// Печать границы таблицы
void print_edge();

// Печать шапки таблицы
void print_head();

// Печать отступа таблицы
void print_space();

// Печать "пустой строки"
void print_blank();

// Вывод одной структуры
void print_flight(Flight flight);

// Вывод массива структур
int print_flights(Flight_filter filters[],
	int head = 1, int full_table = 1, int show_error = 0);

// Работа с фильтрами
// Соответствует ли запись всем заданным фильтрам
int compare_flight(Flight flight, Flight_filter filters[]);

// Вывод заданного поля фильтра
int print_filter(Flight_filter filter, int field, int is_first);

// Вывод меню с фильтрами
int print_filters(Flight_filter filters[]);

// Установка фильтра
int set_filter(Flight_filter* p_filter, int n, int is_first);

// Изменение структур
// Изменение одной структуры
int edit_all_filtered(char file_path[], int len, Flight_filter filters[]);

// Изменение всех записей по фильтру
int edit_from_array(char file_path[], int len, int* to_edit, int edit_len);

// Удаление записей
// Удалить все подходящие под фильтр записи
int delete_all_filtered(char file_path[], int len, Flight_filter filters[]);

// Удалить все записи, чьи номера есть в массиве
int delete_from_array(char file_path[], int len, int* to_del, int del_len);
