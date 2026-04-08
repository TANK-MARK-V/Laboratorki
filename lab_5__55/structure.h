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
} Flight_filter;

// Ввод поля fnum
int input_fnum(Flight* pointer);

// Ввод поля name
int input_name(Flight* pointer);

// Ввод поля dest
int input_dest(Flight* pointer);

// Ввод поля days
int input_days(Flight* pointer);

// Ввод поля ***_time
int input_time(Flight* pointer, int field);

// Ввод поля price
int input_price(Flight* pointer);

// Ввод полной структуры
int input_structure(Flight* pointer);

// Вывод одной структуры
void print_structure(Flight flight);

// Соответствует ли запись заданным фильтрам
int compare_flight(Flight flight, Flight_filter filter);

// Вывод массива структур
int print_structures(Flight* flights, int len, Flight_filter filter);

// Изменение одной структуры
int edit_structure(Flight* pointer);