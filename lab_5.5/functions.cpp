#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functions.h"  // Вспомогательные функции
#include <conio.h>

#include "structure.h"


// Ввод поля fnum
int input_fnum(Flight* pointer) {
	printf("\nВведите номер рейса: ");
	int result;  // Результат ввода
	do {
		result = int_input(&(*pointer).fnum);
		if (result > 2) printf("Некорректный ввод. Введите номер рейса: ");
	} while (result > 1);
	return result;
}

// Ввод поля name
int input_name(Flight* pointer) {
	printf("\nВведите тип самолёта: ");
	int result;  // Результат ввода
	char user_input[16];  // Буфер для ввода
	char* p_input = user_input;  // Указатель на буфер
	do result = input(&p_input);
	while (result);  // Ввод, пока не получим непустую строку
	result = !strcmp(user_input, "###");
	if (result == 0) strcpy((*pointer).name, user_input);
	return result;
}

// Ввод поля dest
int input_dest(Flight* pointer) {
	printf("\nВведите пункт назначения: ");
	int result;  // Результат ввода
	char user_input[16];  // Буфер для ввода
	char* p_input = user_input;  // Указатель на буфер
	do result = input(&p_input);
	while (result);  // Ввод, пока не получим непустую строку
	result = !strcmp(user_input, "###");
	if (result == 0) strcpy((*pointer).dest, user_input);
	return result;
}

// Ввод поля days
int input_days(Flight* pointer) {
	int days[7];   // Массив номеров дней
	int last_day = 0;  // Индекс последнего элемента массива
	printf("\nВведите дни отправления через запятую: ");
	int result = 0;  // Результат ввода
	char user_input[16];  // Буфер для ввода
	char* p_input = user_input;  // Указатель на буфер
	do {
		if (result == 3) printf("Некорректный ввод. "
					"Введите дни отправления через запятую: ");
		result = input_number_list(days, &last_day);
		if (result == 1) return 1;  // Закончить ввод
	} while (result);
	// Сортировка пузырьком
	for (int k = 1; k < last_day; k++)
		for (int i = 0; i < last_day - k; i++)
			if (days[i] > days[i + 1]) {
				int buffer = days[i];
				days[i] = days[i + 1];
				days[i + 1] = buffer;
			}
	// Запись в структуру
	for (int i = 0; i < last_day; i++)
		(*pointer).days[i] = days[i];
	// Всё остальное заполняем нулями
	for (int i = last_day; i < 7; i++)
		(*pointer).days[i] = 0;
	return 0;
}

// Ввод поля ***_time
int input_time(Flight* pointer, int field) {
	// Строка на вывод
	const char* info[] = { "Введите время вылета: ",
							"Введите время прилёта: " };
	int time[2];   // Массив для времени (часы и минуты)
	printf("\n%s", info[field]);
	int result = 0;  // Результат ввода
	char user_input[16];  // Буфер для ввода
	char* p_input = user_input;  // Указатель на буфер
	do {
		if (result) printf("Некорректный ввод. %s", info[field]);
		do result = input(&p_input);
		while (result);  // Ввод, пока не получим непустую строку
		if (!strcmp(user_input, "###")) return 1;  // Закончить ввод
		// Проверим на лишние символы
		if (strcspn(user_input, " .:0123456789")) { result = 1; continue; }
		char* parts[2];  // Разделим ввод на несколько частей
		parts[0] = strtok(user_input, " .:");
		parts[1] = strtok(NULL, " .:");
		// Строка должна поделиться на две части, а третьей быть NULL
		if ((parts[1] == NULL) || (strtok(NULL, " .:") != NULL)) { result = 1; continue; }
		// Длина первой части должна быть 1 или 2
		switch (strlen(parts[0])) {
		case 1: { time[0] = parts[0][0] - '0'; break; }
		case 2: { time[0] = (parts[0][0] - '0') * 10 + parts[0][1] - '0'; break; }
		default: { result = 1; break; }
		}
		// Длина второй всегда 2
		if (strlen(parts[1]) != 2) { result = 1; continue; }
		time[1] = (parts[1][0] - '0') * 10 + parts[1][1] - '0';
		// Проверим на корректные значения
		if (time[0] > 23 || time[1] > 59) result = 1;
	} while (result);
	switch (field) {
	case 0: { (*pointer).dep_time = time[0] * 60 + time[1]; break; }
	case 1: { (*pointer).arr_time = time[0] * 60 + time[1]; break; }
	}
	return 0;
}

// Ввод поля price
int input_price(Flight* pointer) {
	printf("\nВведите цену билета: ");
	int result;  // Результат ввода
	do {
		result = double_input(&(*pointer).price);
		if (result > 2) printf("Некорректный ввод. Введите цену билета: ");
	} while (result > 1 || (*pointer).price < 0);
	return result;
}

// Ввод полной структуры
int input_structure(Flight* pointer) {
	printf("\nВведите запись по столбцам. "
		"Чтобы закончить ввод, введите \"###\"");
	int result = 0;
	// Ввод всех полей
	if (input_fnum(pointer) || input_name(pointer) ||
		input_dest(pointer) || input_days(pointer) ||
		input_time(pointer, 0) || input_time(pointer, 1) ||
		input_price(pointer))
	{
		printf("\nВвод завершён, запись не была добавлена.");
		result = 1;
	}
	else printf("\nВвод завершён, запись добавлена в таблицу.");
	return result;
}

// Вывод одной структуры
void print_structure(Flight flight) {
	// Получим длины каждого поля
	int len_fnum = 1;
	if (flight.fnum) len_fnum = log10(flight.fnum) + 1;
	int len_name = strlen(flight.name);
	int len_dest = strlen(flight.dest);
	int len_dep_time = (flight.dep_time / 60 >= 10) + 1;
	int len_arr_time = (flight.arr_time / 60 >= 10) + 1;
	int len_price = 4;
	if (flight.price > 0) len_price = log10(flight.price) + 1 + 3;
	int len_days = 0;
	for (int i = 0; flight.days[i] && i < 7; i++)
		len_days += 2;
	len_days -= 1;
	// Теперь выведем каждое поле
	// Номер рейса
	printf("|"); for (int i = 0; i < 7 - len_fnum / 2; i++) printf(" ");
	printf("%d", flight.fnum);
	for (int i = 0; i < (7 - (len_fnum - 1) / 2); i++) printf(" ");
	// Тип самолёта
	printf("|"); for (int i = 0; i < 7 - len_name / 2; i++) printf(" ");
	printf("%s", flight.name);
	for (int i = 0; i < 7 - (len_name - 1) / 2; i++) printf(" ");
	// Пункт назначения
	printf("|"); for (int i = 0; i < 7 - len_dest / 2; i++) printf(" ");
	printf("%s", flight.dest);
	for (int i = 0; i < 7 - (len_dest - 1) / 2; i++) printf(" ");
	// Дни отправления
	printf("|%*c%d", (15 - len_days) / 2, ' ', flight.days[0]);
	for (int i = 1; flight.days[i] && i < 7; i++) printf(",%d", flight.days[i]);
	printf("%*c", (16 - len_days) / 2, ' ');
	// Время вылета
	printf("|%*c", 7 - len_dep_time, ' ');
	printf("%d:%.2d", flight.dep_time / 60, flight.dep_time % 60);
	printf("%*c", 7 - 2, ' ');
	// Время прилёта
	printf("|%*c", 7 - len_arr_time, ' ');
	printf("%d:%.2d", flight.arr_time / 60, flight.arr_time % 60);
	printf("%*c", 7 - 2, ' ');
	// Цена билета
	if (len_price <= 13) {
		printf("|%*c", 7 - len_price / 2, ' ');
		printf("%.2lf", flight.price);
		printf("%*c", 7 - (len_price - 1) / 2, ' ');
	}
	else printf("|%9.9e", flight.price);
	printf("|\n");
}

// Печать границы таблицы
void print_edge() {
	printf("+");
	for (int i = 1; i < 8 * (16); i++)
		i % 16 ? printf("-") : printf("+");
	printf("+\n");
}

// Печать отступа таблицы
void print_space() {
	printf("|");
	for (int i = 1; i < 8 * (16); i++)
		i % 16 ? printf(" ") : printf("|");
	printf("|\n");
}

// Печать шапки таблицы
void print_head() {
	printf("Список авиарейсов:\n");
	// Шапка таблицы
	print_edge();
	// Первая строка
	printf("|     Номер     |     Номер     |      Тип      |     Пункт     "
		   "|      Дни      |     Время     |     Время     |     Цена      |\n");
	// Вторая строка
	printf("|   в таблице   |     рейса     |   самолёта    |  назначения   "
		   "|  отправления  |    вылета     |    прилёта    |    билета     |\n");
	print_edge();
}

// Соответствует ли запись заданным фильтрам
int compare_flight(Flight flight, Flight_filter filter) {
	int is_good = 1;  // Запись изначально подходит
	// Сверяем номера рейсов
	if (filter.apply[0]) {
		char flight_fnum[16], filter_fnum[16];
		_itoa(flight.fnum, flight_fnum, 10);
		_itoa(filter.fnum, filter_fnum, 10);
		if (strstr(flight_fnum, filter_fnum) == NULL) is_good = 0;

	}
	// Сверяем типы самолётов
	if (is_good && filter.apply[1]) {
		char flight_name[16], filter_name[16];
		_strlwr(strcpy(flight_name, flight.name));
		_strlwr(strcpy(filter_name, filter.name));
		if (strstr(flight_name, filter_name) == NULL) is_good = 0;
	}
	// Сверяем пункты назначения
	if (is_good && filter.apply[2]) {
		char flight_dest[16], filter_dest[16];
		_strlwr(strcpy(flight_dest, flight.dest));
		_strlwr(strcpy(filter_dest, filter.dest));
		if (strstr(flight_dest, filter_dest) == NULL) is_good = 0;
	}
	// Сверяем дни отправления
	if (is_good && filter.apply[3]) {
		int common = 0;
		for (int i = 0; i < 7 && filter.days[i]; i++)
			for (int j = 0; j < 7 && flight.days[j]; j++)
				if (filter.days[i] == flight.days[j]) common += 1;
		if (!common) is_good = 0;
	}
	// Сверяем время вылета
	if (is_good && filter.apply[4]) {
		if (filter.apply[4] == 1)  // flight > filter
			if (flight.dep_time <= filter.dep_time) is_good = 0;
		if (filter.apply[4] == 2)  // flight < filter
			if (flight.dep_time >= filter.dep_time) is_good = 0;
		if (filter.apply[4] == 3)  // flight = filter
			if (flight.dep_time != filter.dep_time) is_good = 0;
		if (filter.apply[4] == 4)  // flight >= filter
			if (flight.dep_time < filter.dep_time) is_good = 0;
		if (filter.apply[4] == 5)  // flight <= filter
			if (flight.dep_time > filter.dep_time) is_good = 0;
	}
	// Сверяем время прилёта
	if (is_good && filter.apply[5]) {
		if (filter.apply[5] == 1)  // flight > filter
			if (flight.arr_time <= filter.arr_time) is_good = 0;
		if (filter.apply[5] == 2)  // flight < filter
			if (flight.arr_time >= filter.arr_time) is_good = 0;
		if (filter.apply[5] == 3)  // flight = filter
			if (flight.arr_time != filter.arr_time) is_good = 0;
		if (filter.apply[5] == 4)  // flight >= filter
			if (flight.arr_time < filter.arr_time) is_good = 0;
		if (filter.apply[5] == 5)  // flight <= filter
			if (flight.arr_time > filter.arr_time) is_good = 0;
	}
	// Сверяем цену билета
	if (is_good && filter.apply[6]) {
		if (filter.apply[6] == 1)  // flight > filter
			if (flight.price <= filter.price) is_good = 0;
		if (filter.apply[6] == 2)  // flight < filter
			if (flight.price >= filter.price) is_good = 0;
		if (filter.apply[6] == 3)  // flight = filter
			if (flight.price != filter.price) is_good = 0;
		if (filter.apply[6] == 4)  // flight >= filter
			if (flight.price < filter.price) is_good = 0;
		if (filter.apply[6] == 5)  // flight <= filter
			if (flight.price > filter.price) is_good = 0;
	}
	return is_good;
}

// Вывод массива структур
int print_structures(Flight* flights, int len, Flight_filter filter) {
	if (len == 0) { printf("Таблица на данный момент пустая."); return -1; }
	int counter = 0;
	for (int line = 0; line < len; line++) {
		// Выведем номер в таблице
		if (!compare_flight(flights[line], filter)) continue;
		if (!counter) print_head();  // Печатаем верх таблицы, если ещё не печатали
		int len_line = log10(line + 1) + 1;
		printf("|%*c", 7 - len_line / 2, ' ');
		printf("%d", line + 1);
		printf("%*c", 7 - (len_line - 1) / 2, ' ');
		print_structure(flights[line]);
		print_edge();
		counter += 1;
	}
	if (!counter) printf("\nНет записей, соответствующих заданным фильтрам.");
	return counter;
}

// Изменение одной структуры
int edit_structure(Flight* pointer) {
	printf("\nВведите номера столбцов, которые вы хотите изменить, через запятую:\n");
	printf("1 - Номер рейса\n");
	printf("2 - Тип самолёта\n");
	printf("3 - Пункт назначения\n");
	printf("4 - Дни отправления\n");
	printf("5 - Время вылета\n");
	printf("6 - Время прилёта\n");
	printf("7 - Цена билета\n");
	int cols[7];   // Массив номеров столбцов
	int last_ind = 0;  // Индекс последнего элемента массива
	int cols_res = 0;  // Результат ввода массива столбцов
	char user_input[16];  // Буфер для ввода
	char* p_input = user_input;  // Указатель на буфер
	do {
		if (cols_res == 3) printf("Некорректный ввод. "
			"\nВведите номера столбцов, которые вы хотите изменить, через запятую: ");
		cols_res = input_number_list(cols, &last_ind);
	} while (cols_res > 1);
	if (cols_res == 1) return 2;  // Если нужно остановить ввод
	// Сортировка пузырьком
	for (int k = 1; k < last_ind; k++)
		for (int i = 0; i < last_ind - k; i++)
			if (cols[i] > cols[i + 1]) {
				int buffer = cols[i];
				cols[i] = cols[i + 1];
				cols[i + 1] = buffer;
			}
	// Меняем столбцы
	int change_res = 0;  // Результат ввода новых значений
	for (int i = 0; i < last_ind && !change_res; i++)
		if (cols[i] == 1) change_res = input_fnum(pointer);
		else if (cols[i] == 2) change_res = input_name(pointer);
		else if (cols[i] == 3) change_res = input_dest(pointer);
		else if (cols[i] == 4) change_res = input_days(pointer);
		else if (cols[i] == 5) change_res = input_time(pointer, 0);
		else if (cols[i] == 6) change_res = input_time(pointer, 1);
		else if (cols[i] == 7) change_res = input_price(pointer);
	return change_res;  // Если ввод полный, то 0 - иначе 1
}
