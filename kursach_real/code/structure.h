#pragma once

#define TEXT_LEN 16		// Сколько памяти нужно выделить на хранение текстовых полей
#define COLS_WIDE 15	// Ширина каждой колонки
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


// Ввод структуры
// Ввод поля fnum
int input_fnum(Flight *pointer);

// Ввод текстового поля
int input_text_field(char *field, const char *info);
// Ввод поля name
int input_name(Flight *pointer);
// Ввод поля dest
int input_dest(Flight *pointer);

// Ввод поля days
int input_days(Flight *pointer);

// Ввод временного поля
int input_time_field(int *field, const char *info);
// Ввод поля dep_time
int input_dep_time(Flight *pointer);
// Ввод поля arr_time
int input_arr_time(Flight *pointer);

// Ввод поля price
int input_price(Flight *pointer);

// Ввод полной структуры
int input_flight(Flight *pointer);


// Вывод структур
// Печать части таблицы без данных
void print_table_line(char vert = '+', char horiz = '-', int cols_num = FIELDS_NUM + 1, int cols_wide = COLS_WIDE);
// Печать шапки таблицы
void print_head();
// Печать "пустой строки"
void print_blank(int cols_num = FIELDS_NUM + 1, int cols_wide = COLS_WIDE);

// Вывод одной записи
void print_flight(Flight flight, int cols_wide = COLS_WIDE);
// Вывод всех записей
int print_flights(Flight_filter filters[], int *len, int *fil_len, int full_info = 0);


// Работа с фильтрами
// Соответствует ли запись всем заданным фильтрам
int compare_flight(Flight flight, Flight_filter filters[]);

// Вывод заданного поля фильтра
int print_filter(Flight_filter filter, int field, int is_first);

// Вывод меню с фильтрами
int print_filters(Flight_filter filters[]);

// Установка фильтра
int set_filter(Flight_filter *p_filter, int field, int is_first = 0);


// Удаление и изменение записей
// Открыть текущий файл table.csv для чтения и dable.csv для записи
int open_dable(char *file_path, char *new_file_path, FILE **new_table, FILE **old_table);

// Изменение одной структуры
int edit_all_filtered(char *file_path, Flight_filter filters[]);
// Изменение всех записей по фильтру
int edit_from_array(char *file_path, int len, int *to_edit, int edit_len);

// Удалить все подходящие под фильтр записи
int delete_all_filtered(char *file_path, Flight_filter filters[]);
// Удалить все записи, чьи номера есть в массиве
int delete_from_array(char *file_path, int len, int *to_del, int del_len);
