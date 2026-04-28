#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "input_funcs.h"  // Вспомогательные функции
#include <conio.h>

#include "structure.h"
#include "file_funcs.h"


// Стандартный strlwr не работает(
char* mystrlwr(char* string) {
	// Преобразовать буквы верхнего регистра строки string в буквы нижнего регистра
	// string: изменяемая строка
	for (int i = 0; string[i]; i++)
		if (('A' <= string[i]) && (string[i] <= 'Z')) string[i] += 'a' - 'A';
		else if (('А' <= string[i]) && (string[i] <= 'Я')) string[i] += 'а' - 'А';
	return string;
}


// Ввод поля fnum
int input_fnum(Flight* pointer) {
	printf("\nВведите номер рейса: ");
	int result;  // Результат ввода
	do {
		result = int_input(&(*pointer).fnum);
		if (result > 2) printf("Некорректный ввод. Введите номер рейса: ");
		else if (result == 0 && pointer->fnum < 1) printf("Некорректный ввод: номер должен быть >0. Введите номер рейса: ");
	} while (result > 1 || (result == 0 && pointer->fnum < 1));
	return result;
}

// Ввод поля name
int input_name(Flight* pointer) {
	printf("\nВведите тип самолёта: ");
	int result;  // Результат ввода
	char user_input[TEXT_LEN];  // Буфер для ввода
	char* p_input = user_input;  // Указатель на буфер
	do result = input(&p_input, TEXT_LEN - 1);
	while (result ||  // Ввод, пока не получим непустую строку
		strspn(user_input, " ") == strlen(user_input) ||  // Не из пробелов
		strchr(user_input, ';') != NULL);  // Не содержащуюю ';'
	result = !strcmp(user_input, "###");
	if (result == 0) {
		strcpy((*pointer).name, user_input);
		if (strlen(user_input) == TEXT_LEN - 1)
			printf("Строчка не влезла целиком. Сохранено: %s", user_input);
	}
	return result;
}

// Ввод поля dest
int input_dest(Flight* pointer) {
	printf("\nВведите пункт назначения: ");
	int result;  // Результат ввода
	char user_input[TEXT_LEN];  // Буфер для ввода
	char* p_input = user_input;  // Указатель на буфер
	do result = input(&p_input, TEXT_LEN - 1);
	while (result ||  // Ввод, пока не получим непустую строку
		strspn(user_input, " ") == strlen(user_input) ||  // Не из пробелов
		strchr(user_input, ';') != NULL);  // Не содержащуюю ';'
	result = !strcmp(user_input, "###");
	if (result == 0) {
		strcpy((*pointer).dest, user_input);
		if (strlen(user_input) == TEXT_LEN - 1)
			printf("Строчка не влезла целиком. Сохранено: %s", user_input);
	}
	return result;
}

// Ввод поля days
int input_days(Flight* pointer) {
	int days[7];   // Массив номеров дней
	int last_day = 0;  // Индекс последнего элемента массива
	printf("\nВведите дни отправления (1-7) через запятую: ");
	int result = 0;  // Результат ввода
	do {
		if (result == 3) printf("Некорректный ввод. "
					"Введите дни отправления через запятую: ");
		result = input_number_list(days, &last_day);
		if (result == 1) return 1;  // Закончить ввод
	} while (result);

	// Запись в структуру
	for (int i = 0; i < last_day; i++)
		(*pointer).days[i] = days[i];
	// Всё остальное заполняем нулями
	for (int i = last_day; i < 7; i++)
		(*pointer).days[i] = 0;
	return 0;
}


// Ввод поля dep_time
int input_dep_time(Flight* pointer) {
	printf("\nВведите время вылета (например, 13:00): ");
	int result = 0;  // Результат ввода
	do {
		result = input_time(&(*pointer).dep_time);
		if (result == 2) printf("Некорректный ввод. Введите время вылета (например, 13:00): ");
	} while (result > 1);
	return result;
}

// Ввод поля arr_time
int input_arr_time(Flight* pointer) {
	printf("\nВведите время прилёта (например, 14:00): ");
	int result = 0;  // Результат ввода
	do {
		result = input_time(&pointer->arr_time);
		if (result == 2) printf("Некорректный ввод. Введите время прилёта (например, 14:00): ");
	} while (result > 1);
	return result;
}

// Ввод поля price
int input_price(Flight* pointer) {
	printf("\nВведите цену билета: ");
	int result;  // Результат ввода
	do {
		result = double_input(&(*pointer).price);
		if (result > 2) printf("Некорректный ввод. Введите цену билета: ");
	} while (result > 1 || (result == 0 && (*pointer).price < 0));
	return result;
}

// Ввод полной структуры
int input_flight(Flight* pointer) {
	printf("\nВведите запись по столбцам. "
		"Чтобы закончить ввод, введите \"###\"");
	int result = 0;
	// Ввод всех полей
	if (input_fnum(pointer) || input_name(pointer) ||
		input_dest(pointer) || input_days(pointer) ||
		input_dep_time(pointer) || input_arr_time(pointer) ||
		input_price(pointer))
	{
		printf("\nВвод завершён, запись не была добавлена.");
		result = 1;
	}
	else printf("\nВвод завершён, запись добавлена в таблицу.");
	return result;
}

// Вывод структур

// Печать границы таблицы
void print_edge() {
	printf("+");
	for (int i = 1; i < 8 * (16); i++)
		i % 16 ? printf("-") : printf("+");
	printf("+\n");
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

// Печать отступа таблицы
void print_space() {
	for (int i = 0; i < 8 * (16); i++)
		i % 16 ? printf(" ") : printf("|");
	printf("|\n");
}

// Печать "пустой строки"
void print_blank() {
	for (int col = 0; col < 8; col++) {
		printf("|");
		for (int i = 1; i < 16; i++)
			if (i == 16 / 2 || i == (16 - 1) / 2 || i == 16 / 2 + 1)
				printf(".");
			else printf(" ");
	}
	printf("|\n");
	print_edge();
}

// Вывод одной структуры
void print_flight(Flight flight) {
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
	//printf("%s", flight.name);
	for (int i = 0; flight.name[i] && i < 15; i++) printf("%c", flight.name[i]);
	for (int i = 0; i < 7 - (len_name - 1) / 2; i++) printf(" ");
	// Пункт назначения
	printf("|"); for (int i = 0; i < 7 - len_dest / 2; i++) printf(" ");
	//printf("%s", flight.dest);
	for (int i = 0; flight.dest[i] && i < 15; i++) printf("%c", flight.dest[i]);
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

int print_flights(Flight_filter filters[],
	int head, int full_table, int show_error) {
	/*
	Возвращает:
		-1: У пользователя нет прав даже для папки DIR_NAME
		-2: Некорректный путь до файла
		-3: Из-за фильтров не получилось вывести ни одного файла
		0+: Файл успешно прочитан, вернёт кол-во напечатанных записей
	*/
	char file_path[FILE_NAME_LEN];
	int path_res = get_file(file_path, FILE_NAME_LEN);
	if (path_res == -1) return -1;  // Если всё плохо, то завершаем работу с кодом -1

	if (path_res == 1) {  // Путь до файла в settings.txt указан некорректно
		printf("Некорректный путь до файла\n");
		return -2;
	}

	FILE* table = fopen(file_path, "r");
	if (table == NULL) {  // Если файла нет, завершаем работу
		printf("Некорректный путь до файла\n");
		return -2;
	}

	int len, fil_len;  // Сколько всего записей можно вывести
	int res = count_lines(table, filters, &len, &fil_len);
	//printf("len = %d, fil_len = %d\n", len, fil_len);
	//_getch();
	if (head && len) printf("Авиарейсы Mark company:\n");
	if (show_error)
		if (res == 1) printf("Файл был повреждён. Прочитано только %d строк:\n", len);
		else if (res == -1) printf("Файл повреждён и не может быть прочитан\n");
		else if (res == 0 && len == 0) printf("Таблица пустая\n");
		else if (res == 0 && len != 0 && fil_len == 0) {
			printf("Нет записей, подходящих данным фильтрам\n");
			fclose(table);
			return -3;
		}
	rewind(table);

	Flight flight_buffer;  // Буфер для чтения
	int counter = 0;  // Сколько строчек вывели
	int line = 1;  // Перебор строчек
	if (fil_len < 6 || full_table) { // Выведем все записи, если их <6 или нужно вывести всё
		while (line <= fil_len) {
			read_line(table, &flight_buffer);
			if (!compare_flight(flight_buffer, filters)) continue;
			if (!counter++) print_head();  // Печатаем верх таблицы, если ещё не печатали
			// Выведем номер в таблице
			int len_line = log10(line) + 1;
			printf("|%*c", 7 - len_line / 2, ' ');
			printf("%d", line);
			printf("%*c", 7 - (len_line - 1) / 2, ' ');
			print_flight(flight_buffer);
			print_edge();
			line++;
		}
	}
	else { // Иначе выводим первые 2 и последние 2
		int numbers[4];  // Массив для нужных номеров
		Flight only_four[4];  // Массив для 4-ёх записей
		while (line <= fil_len && counter < 2) {
			read_line(table, &flight_buffer);
			if (compare_flight(flight_buffer, filters)) {
				only_four[counter] = flight_buffer;
				numbers[counter++] = line;
				line++;
			}
		}
		only_four[3] = only_four[1];
		numbers[3] = numbers[1];

		while (line <= fil_len) {
			read_line(table, &flight_buffer);
			if (compare_flight(flight_buffer, filters)) {
				only_four[2] = only_four[3];
				only_four[3] = flight_buffer;
				numbers[2] = numbers[3];
				numbers[3] = line;
				line++;
			}
		}
		// Вывод записей
		for (int i = 0; i < 4; i++) {
			if (i == 0) print_head();
			else if (i == 2) print_blank();
			int len_line = log10(numbers[i]) + 1;
			printf("|%*c", 7 - len_line / 2, ' ');
			printf("%d", numbers[i]);
			printf("%*c", 7 - (len_line - 1) / 2, ' ');
			print_flight(only_four[i]);
			print_edge();
		}
	}
	fclose(table);
	return fil_len;
}



// Работа с фильтрами
// Подходит ли поле fnum под заданные фильтры
int compare_fnum(Flight flight, Flight_filter filters[]) {
	int is_good = 1;  // Поле изначально подходит
	for (int fil = 0; fil < 2; fil++) {
		Flight_filter cur_filter = filters[fil];  // Текущий фильтр
		int cur_good = 1;  // Подходит ли поле под текущий фильтр
		if (cur_filter.apply[0]) {
			char flight_fnum[16], filter_fnum[16];
			_itoa(flight.fnum, flight_fnum, 10);
			_itoa(cur_filter.fnum, filter_fnum, 10);
			if (strstr(flight_fnum, filter_fnum) == NULL) cur_good = 0;
		}
		// Применяем логическую операцию
		if (cur_filter.logic[0] == 0) is_good = is_good && cur_good;
		else if (cur_filter.logic[0] == 1) is_good = is_good || cur_good;
	}
	return is_good;
}

// Подходит ли поле name под заданные фильтры
int compare_name(Flight flight, Flight_filter filters[]) {
	int is_good = 1;  // Поле изначально подходит
	for (int fil = 0; fil < 2; fil++) {
		Flight_filter cur_filter = filters[fil];  // Текущий фильтр
		int cur_good = 1;  // Подходит ли поле под текущий фильтр
		if (cur_filter.apply[1]) {
			char flight_name[16], filter_name[16];
			mystrlwr(strcpy(flight_name, flight.name));
			mystrlwr(strcpy(filter_name, cur_filter.name));
			if (strstr(flight_name, filter_name) == NULL) cur_good = 0;
		}
		// Применяем логическую операцию
		if (cur_filter.logic[1] == 0) is_good = is_good && cur_good;
		else if (cur_filter.logic[1] == 1) is_good = is_good || cur_good;
	}
	return is_good;
}

// Подходит ли поле dest под заданные фильтры
int compare_dest(Flight flight, Flight_filter filters[]) {
	int is_good = 1;  // Поле изначально подходит
	for (int fil = 0; fil < 2; fil++) {
		Flight_filter cur_filter = filters[fil];  // Текущий фильтр
		int cur_good = 1;  // Подходит ли поле под текущий фильтр
		if (cur_filter.apply[2]) {
			char flight_dest[16], filter_dest[16];
			mystrlwr(strcpy(flight_dest, flight.dest));
			mystrlwr(strcpy(filter_dest, cur_filter.dest));
			if (strstr(flight_dest, filter_dest) == NULL) cur_good = 0;
		}
		// Применяем логическую операцию
		if (cur_filter.logic[2] == 0) is_good = is_good && cur_good;
		else if (cur_filter.logic[2] == 1) is_good = is_good || cur_good;
	}
	return is_good;
}

// Подходит ли поле days под заданные фильтры
int compare_days(Flight flight, Flight_filter filters[]) {
	int is_good = 1;  // Поле изначально подходит
	for (int fil = 0; fil < 2; fil++) {
		Flight_filter cur_filter = filters[fil];  // Текущий фильтр
		int cur_good = 1;  // Подходит ли поле под текущий фильтр
		if (cur_filter.apply[3]) {
			int common = 0;
			for (int i = 0; i < 7 && cur_filter.days[i]; i++)
				for (int j = 0; j < 7 && flight.days[j]; j++)
					if (cur_filter.days[i] == flight.days[j]) common += 1;
			if (!common) cur_good = 0;
		}
		// Применяем логическую операцию
		if (cur_filter.logic[3] == 0) is_good = is_good && cur_good;
		else if (cur_filter.logic[3] == 1) is_good = is_good || cur_good;
	}
	return is_good;
}

// Подходит ли поле dep_time под заданные фильтры
int compare_dep_time(Flight flight, Flight_filter filters[]) {
	int is_good = 1;  // Поле изначально подходит
	for (int fil = 0; fil < 2; fil++) {
		Flight_filter cur_filter = filters[fil];  // Текущий фильтр
		int cur_good = 1;  // Подходит ли поле под текущий фильтр
		if (cur_filter.apply[4]) {
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
		// Применяем логическую операцию
		if (cur_filter.logic[4] == 0) is_good = is_good && cur_good;
		else if (cur_filter.logic[4] == 1) is_good = is_good || cur_good;
	}
	return is_good;
}

// Подходит ли поле arr_time под заданные фильтры
int compare_arr_time(Flight flight, Flight_filter filters[]) {
	int is_good = 1;  // Поле изначально подходит
	for (int fil = 0; fil < 2; fil++) {
		Flight_filter cur_filter = filters[fil];  // Текущий фильтр
		int cur_good = 1;  // Подходит ли поле под текущий фильтр
		if (cur_filter.apply[5]) {
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
		// Применяем логическую операцию
		if (cur_filter.logic[5] == 0) is_good = is_good && cur_good;
		else if (cur_filter.logic[5] == 1) is_good = is_good || cur_good;
	}
	return is_good;
}

// Подходит ли поле price под заданные фильтры
int compare_price(Flight flight, Flight_filter filters[]) {
	int is_good = 1;  // Поле изначально подходит
	for (int fil = 0; fil < 2; fil++) {
		Flight_filter cur_filter = filters[fil];  // Текущий фильтр
		int cur_good = 1;  // Подходит ли поле под текущий фильтр
		if (cur_filter.apply[6]) {
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
		if (cur_filter.logic[6] == 0) is_good = is_good && cur_good;
		else if (cur_filter.logic[6] == 1) is_good = is_good || cur_good;
	}
	return is_good;
}


// Соответствует ли запись всем заданным фильтрам
int compare_flight(Flight flight, Flight_filter filters[]) {
	return (compare_fnum(flight, filters) &&
		compare_name(flight, filters) &&
		compare_dest(flight, filters) &&
		compare_days(flight, filters) &&
		compare_dep_time(flight, filters) &&
		compare_arr_time(flight, filters) &&
		compare_price(flight, filters));
}

// Вывод заданного поля фильтра
int print_filter(Flight_filter filter, int field, int is_first) {
	if (!filter.apply[field]) return 0;  // Если не нужно применять фильтр
	if (!is_first)  // Если он не стоит первым
		if (filter.logic[field] == 0) printf(" && ");
		else if (filter.logic[field] == 0) printf(" || ");
	// Выведем сам фильтр
	if (field == 0) printf("%d", filter.fnum);
	else if (field == 1) printf("%s", filter.name);
	else if (field == 2) printf("%s", filter.dest);
	else if (field == 3) {
		printf("%d", filter.days[0]);
		for (int i = 1; i < 7 && filter.days[i]; i++)
			printf(", %d", filter.days[i]);
	}
	else if (field == 4) {
		if (filter.apply[4] == 1) printf(">");
		else if (filter.apply[4] == 2) printf("<");
		else if (filter.apply[4] == 3) printf("=");
		else if (filter.apply[4] == 4) printf(">=");
		else if (filter.apply[4] == 5) printf("<=");
		printf("%d:%.2d", filter.dep_time / 60, filter.dep_time % 60);
	}
	else if (field == 5) {
		if (filter.apply[5] == 1) printf(">");
		else if (filter.apply[5] == 2) printf("<");
		else if (filter.apply[5] == 3) printf("=");
		else if (filter.apply[5] == 4) printf(">=");
		else if (filter.apply[5] == 5) printf("<=");
		printf("%d:%.2d", filter.arr_time / 60, filter.arr_time % 60);
	}
	else if (field == 6) {
		if (filter.apply[6] == 1) printf(">");
		else if (filter.apply[6] == 2) printf("<");
		else if (filter.apply[6] == 3) printf("=");
		else if (filter.apply[6] == 4) printf(">=");
		else if (filter.apply[6] == 5) printf("<=");
		printf("%.2lf", filter.price);
	}
	return 1;
}

// Вывод меню с фильтрами
int print_filters(Flight_filter filters[]) {
	system("cls");
	int res = print_flights(filters, 1, 1, 1);
	if (res != -3 && res < 1) return 0;
	const char filters_names[7][20] = {
		"Номер рейса",
		"Тип самолёта",
		"Пункт назначения",
		"Дни отправления",
		"Время вылета",
		"Время прилёта",
		"Цена билета"
	};
	printf("\n\nТекущие фильтры:");
	for (int col = 0; col < 7; col++) {
		int counter = 0;  // Сколько фильтров вывели
		printf("\n%d. %s - ", col + 1, filters_names[col]);
		for (int i = 0; i < 2; i++)
			counter += print_filter(filters[i], col, counter == 0);
		if (counter == 0) printf("не используется");
	}
	return 1;
}

// Установка фильтра
int set_filter(Flight_filter* p_filter, int n, int is_first) {
	int fil_result;  // Результат ввода фильтра
	Flight holder;  // Для удобного ввода
	if (n == 0) {
		fil_result = input_fnum(&holder);
		if (!fil_result) {
			(*p_filter).fnum = holder.fnum;
			(*p_filter).apply[0] = 1;
		}
	}
	if (n == 1) {
		fil_result = input_name(&holder);
		if (!fil_result) {
			strcpy((*p_filter).name, holder.name);
			(*p_filter).apply[1] = 1;
		}
	}
	if (n == 2) {
		fil_result = input_dest(&holder);
		if (!fil_result) {
			strcpy((*p_filter).dest, holder.dest);
			(*p_filter).apply[2] = 1;
		}
	}
	if (n == 3) {
		fil_result = input_days(&holder);
		if (!fil_result) {
			for (int i = 0; i < 7; i++)
				(*p_filter).days[i] = holder.days[i];
			(*p_filter).apply[3] = 1;
		}

	}
	if (n == 4) {
		fil_result = input_dep_time(&holder);
		if (!fil_result) {
			printf("\nВведите оператор сравнения:");
			printf("\n1. \">\" (Позже %d:%.2d)",
				holder.dep_time / 60, holder.dep_time % 60);
			printf("\n2. \"<\" (Раньше %d:%.2d)",
				holder.dep_time / 60, holder.dep_time % 60);
			printf("\n3. \"=\" (Точно в %d:%.2d)",
				holder.dep_time / 60, holder.dep_time % 60);
			printf("\n4. \">=\" (Позже или в %d:%.2d)",
				holder.dep_time / 60, holder.dep_time % 60);
			printf("\n5. \"<=\" (Раньше или в %d:%.2d)\n",
				holder.dep_time / 60, holder.dep_time % 60);

			int comp;  // Выбранный оператор
			int comp_res;  // Результат ввода оператора
			do comp_res = int_input(&comp);
			while (comp_res > 1 || (comp_res == 0 && (comp < 1 || 5 < comp)));
			if (comp_res) (*p_filter).apply[4] = 0;
			else {
				(*p_filter).apply[4] = comp;
				(*p_filter).dep_time = holder.dep_time;
			}
		}
	}
	if (n == 5) {
		fil_result = input_arr_time(&holder);
		if (!fil_result) {
			printf("\nВведите оператор сравнения:");
			printf("\n1. \">\" (Позже %d:%.2d)",
				holder.arr_time / 60, holder.arr_time % 60);
			printf("\n2. \"<\" (Раньше %d:%.2d)",
				holder.arr_time / 60, holder.arr_time % 60);
			printf("\n3. \"=\" (Точно в %d:%.2d)",
				holder.arr_time / 60, holder.arr_time % 60);
			printf("\n4. \">=\" (Позже или в %d:%.2d)",
				holder.arr_time / 60, holder.arr_time % 60);
			printf("\n5. \"<=\" (Раньше или в %d:%.2d)\n",
				holder.arr_time / 60, holder.arr_time % 60);

			int comp;  // Выбранный оператор
			int comp_res;  // Результат ввода оператора
			do comp_res = int_input(&comp);
			while (comp_res > 1 || (comp_res == 0 && (comp < 1 || 5 < comp)));
			if (comp_res) (*p_filter).apply[5] = 0;
			else {
				(*p_filter).apply[5] = comp;
				(*p_filter).arr_time = holder.arr_time;
			}
		}
		else (*p_filter).apply[5] = 0;
	}
	if (n == 6) {
		fil_result = input_price(&holder);
		if (!fil_result) {
			printf("\nВведите оператор сравнения:");
			printf("\n1. \">\" (Дороже %.2lf)", holder.price);
			printf("\n2. \"<\" (Дешевле %.2lf)", holder.price);
			printf("\n3. \"=\" (Ровно %.2lf)", holder.price);
			printf("\n4. \">=\" (Дороже или ровно %.2lf)", holder.price);
			printf("\n5. \"<=\" (Дешевле или ровно %.2lf)\n", holder.price);

			int comp;  // Выбранный оператор
			int comp_res;  // Результат ввода оператора
			do comp_res = int_input(&comp);
			while (comp_res > 1 || (comp_res == 0 && (comp < 1 || 5 < comp)));
			if (comp_res) (*p_filter).apply[6] = 0;
			else {
				(*p_filter).apply[6] = comp;
				(*p_filter).price = holder.price;
			}
		}
	}
	if (!fil_result && !is_first) {
		printf("\nВведите логический оператор:");
		printf("\n0. Логическое И (&&)");
		printf("\n1. Логическое ИЛИ (||)\n");
		int comp;  // Выбранный оператор
		int comp_res;  // Результат ввода оператора
		do comp_res = int_input(&comp);
		while (comp_res > 1 || (comp != 0 && comp != 1));
		if (comp_res) (*p_filter).apply[n] = 0;
		else (*p_filter).logic[n] = comp;
	}
	if (!fil_result)
		printf("\nФильтр успешно добавлен.");
	else printf("\nФильтр не был добавлен");
	return fil_result;
}

// Изменение структур
// Изменение всех записей по фильтру
int edit_all_filtered(char file_path[], int len, Flight_filter filters[]) {
	// Открываем файлы
	char new_file_path[FILE_NAME_LEN];
	*strstr(strcpy(new_file_path, file_path), "table") = 'c';  // Тот же путь, только .../cable.csv
	FILE* new_table = fopen(new_file_path, "w");
	if (new_table == NULL) {
		printf("\nУдаление отменено по причине недостатка прав");
		return -1;
	}
	FILE* old_table = fopen(file_path, "r");
	if (old_table == NULL) {
		fclose(new_table);
		printf("\nУдаление отменено по причине недостатка прав");
		return -1;
	}

	printf("\nВведите номера столбцов, которые вы хотите изменить, через запятую:\n");
	printf("1 - Номер рейса\n");
	printf("2 - Тип самолёта\n");
	printf("3 - Пункт назначения\n");
	printf("4 - Дни отправления\n");
	printf("5 - Время вылета\n");
	printf("6 - Время прилёта\n");
	printf("7 - Цена билета\n");
	int cols[7];				// Массив номеров столбцов
	int last_ind = 0;			// Индекс последнего элемента массива
	int cols_res = 0;			// Результат ввода массива столбцов
	do {
		if (cols_res == 3) printf("Некорректный ввод. "
			"\nВведите номера столбцов, которые вы хотите изменить, через запятую: ");
		cols_res = input_number_list(cols, &last_ind);
	} while (cols_res > 1);
	if (cols_res == 1) return 2;  // Если нужно остановить ввод
	
	// Меняем столбцы
	int change_res = 0;  // Результат ввода новых значений
	Flight new_data;  // Тут будем хранить введённые данные

	for (int i = 0; i < last_ind && !change_res; i++)
		if (cols[i] == 1) change_res = input_fnum(&new_data);
		else if (cols[i] == 2) change_res = input_name(&new_data);
		else if (cols[i] == 3) change_res = input_dest(&new_data);
		else if (cols[i] == 4) change_res = input_days(&new_data);
		else if (cols[i] == 5) change_res = input_dep_time(&new_data);
		else if (cols[i] == 6) change_res = input_arr_time(&new_data);
		else if (cols[i] == 7) change_res = input_price(&new_data);

	// Если строка подходит не под фильтр, то переписываем её
	// Иначе изменяем её по шаблону и записываем
	int is_error = 0;  // Ошибка чтения
	Flight buffer;  // Буфер для чтения полёта
	for (int cur_line = 0; cur_line < len && !is_error; cur_line++)
		if (read_line(old_table, &buffer) != 7) is_error = 1;
		else if (!compare_flight(buffer, filters)) write_line(new_table, buffer);
		else {
			for (int i = 0; i < last_ind && !change_res; i++)
				if (cols[i] == 1) buffer.fnum = new_data.fnum;
				else if (cols[i] == 2) strcpy(buffer.name, new_data.name);
				else if (cols[i] == 3) strcpy(buffer.dest, new_data.dest);
				else if (cols[i] == 4) for (int j = 0; j < 7; j++) buffer.days[j] = new_data.days[j];
				else if (cols[i] == 5) buffer.dep_time = new_data.dep_time;
				else if (cols[i] == 6) buffer.arr_time = new_data.arr_time;
				else if (cols[i] == 7) buffer.price = new_data.price;
			write_line(new_table, buffer);
		}

	// Удаляем прошлый файл и переименовываем новый
	fclose(new_table);
	fclose(old_table);
	remove(file_path);
	rename(new_file_path, file_path);

	if (!is_error) {
		printf("\nИзменение завершено.");
		return change_res * 2;  // Если ввод полный, то 0 - иначе 2
	}
	else {
		printf("\nПроизошла ошибка чтения. Не все строки были были изменены");
		return is_error;
	}
}

// Изменить все записи, чьи номера есть в массиве
int edit_from_array(char file_path[], int len, int* to_edit, int edit_len) {
	// Открываем файлы
	char new_file_path[FILE_NAME_LEN];
	*strstr(strcpy(new_file_path, file_path), "table") = 'c';  // Тот же путь, только .../cable.csv
	FILE* new_table = fopen(new_file_path, "w");
	if (new_table == NULL) {
		printf("\nУдаление отменено по причине недостатка прав");
		return -1;
	}
	FILE* old_table = fopen(file_path, "r");
	if (old_table == NULL) {
		fclose(new_table);
		printf("\nУдаление отменено по причине недостатка прав");
		return -1;
	}

	printf("\nВведите номера столбцов, которые вы хотите изменить, через запятую:\n");
	printf("1 - Номер рейса\n");
	printf("2 - Тип самолёта\n");
	printf("3 - Пункт назначения\n");
	printf("4 - Дни отправления\n");
	printf("5 - Время вылета\n");
	printf("6 - Время прилёта\n");
	printf("7 - Цена билета\n");
	int cols[7];				// Массив номеров столбцов
	int last_ind = 0;			// Индекс последнего элемента массива
	int cols_res = 0;			// Результат ввода массива столбцов
	do {
		if (cols_res == 3) printf("Некорректный ввод. "
			"\nВведите номера столбцов, которые вы хотите изменить, через запятую: ");
		cols_res = input_number_list(cols, &last_ind);
	} while (cols_res > 1);
	if (cols_res == 1) return 2;  // Если нужно остановить ввод
	
	// Меняем столбцы
	int change_res = 0;  // Результат ввода новых значений
	Flight new_data;  // Тут будем хранить введённые данные

	for (int i = 0; i < last_ind && !change_res; i++)
		if (cols[i] == 1) change_res = input_fnum(&new_data);
		else if (cols[i] == 2) change_res = input_name(&new_data);
		else if (cols[i] == 3) change_res = input_dest(&new_data);
		else if (cols[i] == 4) change_res = input_days(&new_data);
		else if (cols[i] == 5) change_res = input_dep_time(&new_data);
		else if (cols[i] == 6) change_res = input_arr_time(&new_data);
		else if (cols[i] == 7) change_res = input_price(&new_data);


	int is_error = 0;  // Ошибка чтения
	Flight buffer;  // Буфер для чтения полёта
	int last_edit = 0;  // Для прохода по массиву to_edit
	int cur_line = 0;  // Для прохода по файлу
	printf("\n");
	for (; cur_line < len && last_edit < edit_len && !is_error; cur_line++)
		if (read_line(old_table, &buffer) != 7) is_error = 1;
		else if (cur_line + 1 < to_edit[last_edit]) write_line(new_table, buffer);
		else {
			for (int i = 0; i < last_ind && !change_res; i++)
				if (cols[i] == 1) buffer.fnum = new_data.fnum;
				else if (cols[i] == 2) strcpy(buffer.name, new_data.name);
				else if (cols[i] == 3) strcpy(buffer.dest, new_data.dest);
				else if (cols[i] == 4) for (int j = 0; j < 7; j++) buffer.days[j] = new_data.days[j];
				else if (cols[i] == 5) buffer.dep_time = new_data.dep_time;
				else if (cols[i] == 6) buffer.arr_time = new_data.arr_time;
				else if (cols[i] == 7) buffer.price = new_data.price;
			write_line(new_table, buffer);
			printf("Строка %d успешно изменена\n", cur_line + 1);
			last_edit++;
		}
	for (; cur_line < len && !is_error; cur_line++)
		if (read_line(old_table, &buffer) != 7) is_error = 1;
		else write_line(new_table, buffer);

	// Удаляем прошлый файл и переименовываем новый
	fclose(new_table);
	fclose(old_table);
	remove(file_path);
	rename(new_file_path, file_path);

	if (!is_error) {
		printf("\nИзменение завершено.");
		return change_res * 2;  // Если ввод полный, то 0 - иначе 2
	}
	else {
		printf("\nПроизошла ошибка чтения. Не все строки были были изменены");
		return is_error;
	}
}


// Удаление записей
// Удалить все подходящие под фильтр записи
int delete_all_filtered(char file_path[], int len, Flight_filter filters[]) {
	// Открываем файлы
	char new_file_path[FILE_NAME_LEN];
	*strstr(strcpy(new_file_path, file_path), "table") = 'd';  // Тот же путь, только .../dable.csv
	FILE* new_table = fopen(new_file_path, "w");
	if (new_table == NULL) {
		printf("\nУдаление отменено по причине недостатка прав");
		return -1;
	}
	FILE* old_table = fopen(file_path, "r");
	if (old_table == NULL) {
		fclose(new_table);
		printf("\nУдаление отменено по причине недостатка прав");
		return -1;
	}

	// Если строка подходит не под фильтр, то переписываем её
	int is_error = 0;  // Ошибка чтения
	Flight buffer;  // Буфер для чтения полёта
	for (int cur_line = 0; cur_line < len && !is_error; cur_line++)
		if (read_line(old_table, &buffer) != 7) is_error = 1;
		else if (!compare_flight(buffer, filters)) write_line(new_table, buffer);

	// Удаляем прошлый файл и переименовываем новый
	fclose(new_table);
	fclose(old_table);
	remove(file_path);
	rename(new_file_path, file_path);

	if (!is_error) printf("\nУдаление завершено.");
	else printf("\nПроизошла ошибка чтения. Не все строки были удалены");
	return is_error;
}

// Удалить все записи, чьи номера есть в массиве
int delete_from_array(char file_path[], int len, int *to_del, int del_len) {
	// Открываем файлы
	char new_file_path[FILE_NAME_LEN];
	*strstr(strcpy(new_file_path, file_path), "table") = 'd';  // Тот же путь, только .../dable.csv
	FILE* new_table = fopen(new_file_path, "w");
	if (new_table == NULL) {
		printf("\nУдаление отменено по причине недостатка прав");
		return -1;
	}
	FILE* old_table = fopen(file_path, "r");
	if (old_table == NULL) {
		fclose(new_table);
		printf("\nУдаление отменено по причине недостатка прав");
		return -1;
	}

	// Удаление будем совершать следующим образом:
	// Если номер строки меньше номера для удаления, то записываем её
	// Иначе номер строки в массиве - пропускаем её
	int is_error = 0;  // Ошибка чтения
	Flight buffer;  // Буфер для чтения полёта
	int last_del = 0;  // Для прохода по массиву to_del
	int cur_line = 0;  // Для прохода по файлу
	printf("\n");
	for (; cur_line < len && last_del < del_len && !is_error; cur_line++)
		if (read_line(old_table, &buffer) != 7) is_error = 1;
		else if (cur_line + 1 < to_del[last_del]) write_line(new_table, buffer);
		else { printf("Строка %d успешно удалена\n", cur_line + 1); last_del++; }
	for (; cur_line < len && !is_error; cur_line++)
		if (read_line(old_table, &buffer) != 7) is_error = 1;
		else write_line(new_table, buffer);

	// Удаляем прошлый файл и переименовываем новый
	fclose(new_table);
	fclose(old_table);
	remove(file_path);
	rename(new_file_path, file_path);

	if (!is_error) printf("\nУдаление завершено.");
	else printf("\nПроизошла ошибка чтения. Не все строки были удалены");
	return is_error;
}