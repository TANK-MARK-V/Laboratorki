#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>			// Для FILE, printf, fopen, fclose, rewind, rename, remove
#include <stdlib.h>			// Для system, _itoa
#include <string.h>			// Для strlen, strcpy, strchr, strstr
#include <math.h>			// Для log10

#include "structure.h"
#include "file_funcs.h"		// Для FILE_NAME_LEN, get_file, read_line, write_line, count_lines
#include "input_funcs.h"	// Для CANCEL, input, int_input, double_input, number_array_input, input_time


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
int input_fnum(Flight *pointer) {
	const char *info = "Введите номер рейса (>0)";
	printf("\n%s: ", info);
	int result;  // Результат ввода: 0 - успешно, 1 - отмена
	do {
		result = int_input(&pointer->fnum);
		if (result > 2 || result == 0 && pointer->fnum < 1)
			printf("Некорректный ввод. %s: ", info);
	} while (result > 1 || (result == 0 && pointer->fnum < 1));
	return result;
}

// Ввод текстового поля
int input_text_field(char *field, const char *info) {
	printf("\n%s: ", info);
	char user_input[TEXT_LEN];	// Буфер для ввода
	int input_res;				// Результат ввода: 0 - успешно, 1 - отмена
	int overflow;				// Сколько символов не влезло

	do input_res = input(user_input, TEXT_LEN, &overflow);
	while (input_res == 2 ||				// Пока пустая строка
		strchr(user_input, ';') != NULL);	// Или содержит ';'

	if (!input_res) {
		strcpy(field, user_input);
		if (overflow)
			printf("Строчка не влезла целиком. Сохранено: %s", user_input);
	}
	return input_res;
}

// Ввод поля name
int input_name(Flight *pointer) {
	const char *info = "Введите тип самолёта (без знака \";\")";
	return input_text_field(pointer->name, info);
}

// Ввод поля dest
int input_dest(Flight *pointer) {
	const char *info = "Введите пункт назначения (без знака \";\")";
	return input_text_field(pointer->dest, info);
}

// Ввод поля days
int input_days(Flight *pointer) {
	const char *info = "Введите дни отправления (1-7) через запятую";
	printf("\n%s: ", info);
	int days[7];		// Массив номеров дней
	int last_day = 0;	// Индекс последнего элемента массива
	int result = 0;		// Результат ввода: 0 - успешно, 1 - отмена

	do {
		if (result == 3) printf("Некорректный ввод. %s: ", info);
		result = number_array_input(days, &last_day);
		if (result == 1) return 1;
	} while (result);

	// Запись в структуру
	for (int i = 0; i < last_day; i++)
		pointer->days[i] = days[i];
	// Всё остальное заполняем нулями
	for (int i = last_day; i < 7; i++)
		pointer->days[i] = 0;
	return 0;
}

// Ввод временного поля
int input_time_field(int *field, const char *info) {
	printf("\n%s: ", info);
	int result;  // Результат ввода: 0 - успешно, 1 - отмена
	do {
		result = input_time(field);
		if (result == 3) printf("Некорректный ввод. %s: ", info);
	} while (result > 1);
	return result;
}

// Ввод поля dep_time
int input_dep_time(Flight *pointer) {
	const char *info = "Введите время вылета (например, 13:00)";
	return input_time_field(&pointer->dep_time, info);
}

// Ввод поля arr_time
int input_arr_time(Flight *pointer) {
	const char *info = "Введите время прилёта (например, 14:00)";
	return input_time_field(&pointer->arr_time, info);
}

// Ввод поля price
int input_price(Flight *pointer) {
	const char* info = "Введите цену билета (>0)";
	printf("\n%s: ", info);
	int result;  // Результат ввода: 0 - успешно, 1 - отмена
	do {
		result = double_input(&pointer->price);
		if (result > 2 || result == 0 && pointer->price <= 0)
			printf("Некорректный ввод. %s: ", info);
	} while (result > 1 || (result == 0 && (*pointer).price <= 0));
	return result;
}

// Ввод полной структуры
int input_flight(Flight *pointer) {
	printf("\nВведите запись по столбцам. "
		"Чтобы закончить ввод, введите \"%s\"", CANCEL);
	int result = 0;  // Результат ввода: 0 - успешно, 1 - отмена
	// Ввод всех полей
	if (input_fnum(pointer) ||
		input_name(pointer) || input_dest(pointer) ||
		input_days(pointer) ||
		input_dep_time(pointer) || input_arr_time(pointer) ||
		input_price(pointer))
	{
		printf("\nВвод завершён, запись не была добавлена.\n");
		result = 1;
	}
	else printf("\nВвод завершён, запись добавлена в таблицу.\n");
	return result;
}

// Печать части таблицы без данных
void print_table_line(char vert, char horiz, int cols_num, int cols_wide) {
	/*
	vert: разделитель колонок
	horiz: разделитель строк (если не стоит vert)
	cols_num: количество столбцов
	cols_wide: длина столбца
	*/
	for (int i = 0; i <= cols_num * (cols_wide + 1); i++)
		i % (cols_wide + 1) ? printf("%c", horiz) : printf("%c", vert);
	printf("\n");
}

// Печать шапки таблицы
void print_head() {
	printf("Список авиарейсов:\n");
	print_table_line();
	// Первая строка
	printf("|     Номер     |     Номер     |      Тип      |     Пункт     "
		   "|      Дни      |     Время     |     Время     |     Цена      |\n");
	// Вторая строка
	printf("|   в таблице   |     рейса     |   самолёта    |  назначения   "
		   "|  отправления  |    вылета     |    прилёта    |    билета     |\n");
	print_table_line();
}

// Печать "пустой строки"
void print_blank(int cols_num, int cols_wide) {
	for (int col = 0; col < cols_num; col++) {
		printf("|");
		for (int i = 1; i < (cols_wide + 1); i++)
			if ((cols_wide) / 2 <= i || i <= (cols_wide + 1) / 2 + 1)
				printf(".");
			else printf(" ");
	}
	printf("|\n");
	print_table_line();
}

// Вывод одной записи
void print_flight(Flight flight, int cols_wide) {
	// Получим длины каждого поля
	int len_fnum = 1;
	if (flight.fnum)
		len_fnum = log10(flight.fnum) + 1;					// fnum
	
	int len_name = strlen(flight.name);						// name
	int len_dest = strlen(flight.dest);						// dest
	int len_dep_time = (flight.dep_time / 60 >= 10) + 1;	// dep_time
	int len_arr_time = (flight.arr_time / 60 >= 10) + 1;	// arr_time
	
	int len_price = 4;
	if (flight.price > 0)
		len_price = log10(flight.price) + 1 + 3;			// price
	
	int len_days = 0;
	for (int i = 0; flight.days[i] && i < 7; i++)
		len_days += 2;
	len_days -= 1;											// days

	// Теперь выведем каждое поле
	int left_space;  // Сколько пробелов нужно добавить слева
	// Номер рейса
	left_space = (cols_wide - len_fnum) / 2;
	printf("|"); for (int i = 0; i < left_space; i++) printf(" ");
	printf("%d", flight.fnum);
	for (int i = 0; i < cols_wide - len_fnum - left_space; i++) printf(" ");
	
	// Тип самолёта
	left_space = (cols_wide - len_name) / 2;
	printf("|"); for (int i = 0; i < left_space; i++) printf(" ");
	for (int i = 0; flight.name[i] && i < cols_wide; i++) printf("%c", flight.name[i]);
	for (int i = 0; i < cols_wide - len_name - left_space; i++) printf(" ");
	
	// Пункт назначения
	left_space = (cols_wide - len_dest) / 2;
	printf("|"); for (int i = 0; i < left_space; i++) printf(" ");
	for (int i = 0; flight.dest[i] && i < cols_wide; i++) printf("%c", flight.dest[i]);
	for (int i = 0; i < cols_wide - len_dest - left_space; i++) printf(" ");
	
	// Дни отправления
	left_space = (cols_wide - len_days) / 2;
	printf("|"); for (int i = 0; i < left_space; i++) printf(" ");
	printf("%d", flight.days[0]);
	for (int i = 1; flight.days[i] && i < 7; i++) printf(",%d", flight.days[i]);
	for (int i = 0; i < cols_wide - len_days - left_space; i++) printf(" ");

	// Время вылета
	printf("|%*c", cols_wide / 2 - len_dep_time, ' ');
	printf("%d:%.2d", flight.dep_time / 60, flight.dep_time % 60);
	printf("%*c", cols_wide / 2 - 2, ' ');
	
	// Время прилёта
	printf("|%*c", cols_wide / 2 - len_arr_time, ' ');
	printf("%d:%.2d", flight.arr_time / 60, flight.arr_time % 60);
	printf("%*c", cols_wide / 2 - 2, ' ');
	
	// Цена билета
	if (len_price <= 13) {
		left_space = (cols_wide - len_price) / 2;
		printf("|%*c", left_space, ' ');
		printf("%.2lf", flight.price);
		printf("%*c", cols_wide - len_price - left_space, ' ');
	}
	else printf("|%9.9e", flight.price);
	printf("|\n");
}

// Вывод всех записей
int print_flights(Flight_filter filters[], int *len, int *fil_len, int full_info) {
	/*
	Возвращает:
		-3: Файл повреждён и не может быть прочитан
		-2: Некорректный путь до файла
		-1: У пользователя нет прав даже для папки DIR_NAME
		0: Файл успешно прочитан
		1: Файл повреждён, но строчки прочитаны
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
	int count_res = count_lines(table, filters, len, fil_len);

	// Вывод информации
	if (full_info) {
		// Проверка на ошибки чтения
		if (count_res == -1) {
			printf("Файл повреждён и не может быть прочитан\n");
			fclose(table);
			return -3;
		}
		else if (count_res == 1)
			printf("Файл был повреждён. Прочитано только %d строк\n", *len);
		// Проверка на кол-во записей в таблице
		if (*len == 0) {
			printf("Таблица пустая\n");
			fclose(table);
			return 0;
		}
		else if (*fil_len == 0) {
			printf("Нет записей, подходящих данным фильтрам\n");
			fclose(table);
			return 0;
		}
	}
	else if (*len) printf("Авиарейсы Mark company:\n");
	rewind(table);

	// Вывод записей
	Flight flight_buffer;	// Буфер для чтения
	if (*fil_len) print_head();
	if (*fil_len < 6 || full_info) {  // Выведем все записи, если их <6 или нужно вывести всё
		for (int line = 0; line < *len; line++) {
			read_line(table, &flight_buffer);
			if (!compare_flight(flight_buffer, filters)) continue;
			// Номер в таблице
			int len_line = log10(line + 1) + 1;
			int left_space = (COLS_WIDE - len_line) / 2;
			printf("|%*c", left_space, ' ');
			printf("%d", line + 1);
			printf("%*c", COLS_WIDE - len_line - left_space, ' ');
			// Сама запись
			print_flight(flight_buffer);
			print_table_line();
		}
	}
	else {  // Иначе выводим первые 2 и последние 2
		Flight four_flights[4];		// Массив для 4-ёх записей
		int four_numbers[4];		// Массив для нужных номеров
		int counter = 0;			// Сколько строчек вывели
		int i;						// Для перебора строчек
		for (i = 0; i <= *len && counter < 2; i++) {
			read_line(table, &flight_buffer);
			if (compare_flight(flight_buffer, filters)) {
				four_flights[counter] = flight_buffer;
				four_numbers[counter++] = i + 1;
			}
		}
		four_flights[3] = four_flights[1];
		four_numbers[3] = four_numbers[1];
		for (; i < *len; i++) {
			read_line(table, &flight_buffer);
			if (compare_flight(flight_buffer, filters)) {
				four_flights[2] = four_flights[3];
				four_flights[3] = flight_buffer;
				four_numbers[2] = four_numbers[3];
				four_numbers[3] = i + 1;
			}
		}
		// Вывод записей
		for (int i = 0; i < 4; i++) {
			if (i == 2) print_blank();
			// Номер в таблице
			int len_num = log10(four_numbers[i]) + 1;
			int left_space = (COLS_WIDE - len_num) / 2;
			printf("|%*c", left_space, ' ');
			printf("%d", four_numbers[i]);
			printf("%*c", COLS_WIDE - len_num - left_space, ' ');
			// Сама запись
			print_flight(four_flights[i]);
			print_table_line();
		}
	}
	fclose(table);
	return count_res;
}

// Соответствует ли запись всем заданным фильтрам
int compare_flight(Flight flight, Flight_filter filters[]) {
	int is_good = 1;  // Запись изначально подходит
	for (int i = 0; i < FIELDS_NUM && is_good; i++)
		for (int fil = 0; fil < FILTERS_NUM; fil++) {
			Flight_filter cur_filter = filters[fil];  // Текущий фильтр
			int cur_good = 1;  // Подходит ли текущее поле под текущий фильтр
			if (i == 0 && cur_filter.apply[0]) {		// Поле fnum
				char flight_fnum[16], filter_fnum[16];
				_itoa(flight.fnum, flight_fnum, 10);
				_itoa(cur_filter.fnum, filter_fnum, 10);
				if (strstr(flight_fnum, filter_fnum) == NULL) cur_good = 0;
			}
			if (i == 1 && cur_filter.apply[1]) {		// Поле name
				char flight_name[16], filter_name[16];
				mystrlwr(strcpy(flight_name, flight.name));
				mystrlwr(strcpy(filter_name, cur_filter.name));
				if (strstr(flight_name, filter_name) == NULL) cur_good = 0;
			}
			if (i == 2 && cur_filter.apply[2]) {		// Поле dest
				char flight_dest[16], filter_dest[16];
				mystrlwr(strcpy(flight_dest, flight.dest));
				mystrlwr(strcpy(filter_dest, cur_filter.dest));
				if (strstr(flight_dest, filter_dest) == NULL) cur_good = 0;
			}
			if (i == 3 && cur_filter.apply[3]) {		// Поле days
				int common = 0;
				for (int i = 0; i < 7 && cur_filter.days[i]; i++)
					for (int j = 0; j < 7 && flight.days[j]; j++)
						if (cur_filter.days[i] == flight.days[j]) common += 1;
				if (!common) cur_good = 0;
			}
			if (i == 4 && cur_filter.apply[4]) {		// Поле dep_time
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
			if (i == 5 && cur_filter.apply[5]) {		// Поле arr_time
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
			if (i == 6 && cur_filter.apply[6]) {		// Поле price
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

// Вывод заданного поля фильтра
int print_filter(Flight_filter filter, int field, int is_first) {
	if (!filter.apply[field]) return 0;  // Если не нужно применять фильтр
	if (!is_first)  // Если он не стоит первым
			 if (filter.logic[field] == 0) printf(" && ");
		else if (filter.logic[field] == 1) printf(" || ");
	// Выведем сам фильтр
	const char apply_type[5][3] = { ">", "<", "=", ">=", "<=" };
		 if (field == 0) printf("%d", filter.fnum);
	else if (field == 1) printf("%s", filter.name);
	else if (field == 2) printf("%s", filter.dest);
	else if (field == 3) {
		printf("%d", filter.days[0]);
		for (int i = 1; i < 7 && filter.days[i]; i++)
			printf(", %d", filter.days[i]);
	}
	else if (field == 4)
		printf("%s%d:%.2d", apply_type[filter.apply[4] - 1], filter.dep_time / 60, filter.dep_time % 60);
	else if (field == 5)
		printf("%s%d:%.2d", apply_type[filter.apply[5] - 1], filter.arr_time / 60, filter.arr_time % 60);
	else if (field == 6)
		printf("%s%.2lf", apply_type[filter.apply[6] - 1], filter.price);
	return 1;
}

// Вывод меню с фильтрами
int print_filters(Flight_filter filters[]) {
	system("cls");
	int len, fil_len;
	if (print_flights(filters, &len, &fil_len, 1) < 0 || len == 0) return 0;
	printf("\n");
	const char *cols_names[FIELDS_NUM];  // Названия колонок
	cols_names[0] = "Номер рейса     ";
	cols_names[1] = "Тип самолёта    ";
	cols_names[2] = "Пункт назначения";
	cols_names[3] = "Дни отправления ";
	cols_names[4] = "Время вылета    ";
	cols_names[5] = "Время прилёта   ";
	cols_names[6] = "Цена билета     ";
	printf("Текущие фильтры:");
	for (int col = 0; col < FIELDS_NUM; col++) {
		int counter = 0;  // Сколько фильтров вывели
		printf("\n%d. %s - ", col + 1, cols_names[col]);
		for (int i = 0; i < FILTERS_NUM; i++)
			counter += print_filter(filters[i], col, counter == 0);
		if (counter == 0) printf("не используется");
	}
	return 1;
}

// Установка фильтра
int set_filter(Flight_filter *p_filter, int field, int is_first) {
	int filter_result = 0;	// Результат ввода фильтра
	int apply_result = 1;	// Выбранный оператор сравнения (для некоторых полей)
	int logic_result = 0;   // Выбранный логический оператор (если не первый = !is_first)
	Flight holder;			// Буфер ввода
		 if (field == 0) filter_result = input_fnum(&holder);		// Поле fnum
	else if (field == 1) filter_result = input_name(&holder);		// Поле name
	else if (field == 2) filter_result = input_dest(&holder);		// Поле dest
	else if (field == 3) filter_result = input_days(&holder);		// Поле days
	else if (field == 4) filter_result = input_dep_time(&holder);	// Поле dep_time
	else if (field == 5) filter_result = input_arr_time(&holder);	// Поле arr_time
	else if (field == 6) filter_result = input_price(&holder);		// Поле price

	// Выбор оператора сравнения
	if (!filter_result && 4 <= field && field <= 6) {
		if (field == 6) {  // Цена
			printf("\nВведите оператор сравнения:");
			printf("\n1. \">\" (Дороже %.2lf)", holder.price);
			printf("\n2. \"<\" (Дешевле %.2lf)", holder.price);
			printf("\n3. \"=\" (Ровно %.2lf)", holder.price);
			printf("\n4. \">=\" (Дороже или ровно %.2lf)", holder.price);
			printf("\n5. \"<=\" (Дешевле или ровно %.2lf)\n", holder.price);
		}
		else {  // Время
			int hours, minutes;
			if (field == 4) {  // dep_time
				hours = holder.dep_time / 60;
				minutes = holder.dep_time % 60;
			}
			if (field == 5) {  // arr_time
				hours = holder.arr_time / 60;
				minutes = holder.arr_time % 60;
			}
			printf("\nВведите оператор сравнения:");
			printf("\n1. \">\" (Позже %d:%.2d)", hours, minutes);
			printf("\n2. \"<\" (Раньше %d:%.2d)", hours, minutes);
			printf("\n3. \"=\" (Точно в %d:%.2d)", hours, minutes);
			printf("\n4. \">=\" (Позже или в %d:%.2d)", hours, minutes);
			printf("\n5. \"<=\" (Раньше или в %d:%.2d)\n", hours, minutes);
		}
		int answer_res;  // Результат ввода оператора
		do answer_res = int_input(&apply_result);
		while (answer_res > 1 || (answer_res == 0 && (apply_result < 1 || 5 < apply_result)));
	}

	// Выбор логического оператора
	if (!filter_result && !is_first) {
		printf("\nВведите логический оператор:");
		printf("\n0. Логическое И (&&)");
		printf("\n1. Логическое ИЛИ (||)\n");
		do filter_result = int_input(&logic_result);
		while (filter_result > 1 || (logic_result != 0 && logic_result != 1));
	}

	// Сохраняем фильтр, если до этого всё прошло успешно
	if (!filter_result) {
			 if (field == 0) p_filter->fnum = holder.fnum;
		else if (field == 1) strcpy(p_filter->name, holder.name);
		else if (field == 2) strcpy(p_filter->dest, holder.dest);
		else if (field == 3) for (int i = 0; i < 7; i++) p_filter->days[i] = holder.days[i];
		else if (field == 4) p_filter->dep_time = holder.dep_time;
		else if (field == 5) p_filter->arr_time = holder.arr_time;
		else if (field == 6) p_filter->price = holder.price;
		p_filter->apply[field] = apply_result;
		p_filter->logic[field] = logic_result;
		printf("\nФильтр успешно добавлен.");
	}
	else printf("\nФильтр не был добавлен");
	return filter_result;
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

// Изменение всех записей по фильтру
int edit_all_filtered(char *file_path, Flight_filter filters[]) {
	/*
	Возвращает:
		-2: Ошибка чтения
		-1: Недостаток прав
		0: Успешное изменение
		1: Отмена изменения
	*/
	char new_file_path[FILE_NAME_LEN];
	FILE *new_table, *old_table;
	if (open_dable(file_path, new_file_path, &new_table, &old_table) == -1) return -1;

	const char* info = "Введите номера столбцов, которые вы хотите изменить, через запятую";
	printf("\n%s:\n", info);
	const char* cols_names[FIELDS_NUM];  // Названия колонок
	cols_names[0] = "Номер рейса";
	cols_names[1] = "Тип самолёта";
	cols_names[2] = "Пункт назначения";
	cols_names[3] = "Дни отправления";
	cols_names[4] = "Время вылета";
	cols_names[5] = "Время прилёта";
	cols_names[6] = "Цена билета";
	for (int col = 0; col < FIELDS_NUM; col++)
		printf("%d - %s\n", col + 1, cols_names[col]);
	printf("Ваш выбор: ");
	
	// Какие столбцы нужно поменять
	int cols[FIELDS_NUM];	// Массив номеров столбцов
	int last_ind = 0;		// Индекс последнего элемента массива
	int cols_res = 0;		// Результат ввода массива столбцов
	do {
		if (cols_res == 3) printf("Некорректный ввод.\n%s: ", info);
		cols_res = number_array_input(cols, &last_ind);
	} while (cols_res > 1);
	if (cols_res == 1) return 1;  // Отмена изменения
	
	// Создаём шаблон изменения
	int change_res = 0;	// Результат ввода новых значений
	Flight new_data;	// Тут будем хранить введённые данные
	for (int i = 0; i < last_ind && !change_res; i++)
		if (cols[i] == 1) change_res = input_fnum(&new_data);
		else if (cols[i] == 2) change_res = input_name(&new_data);
		else if (cols[i] == 3) change_res = input_dest(&new_data);
		else if (cols[i] == 4) change_res = input_days(&new_data);
		else if (cols[i] == 5) change_res = input_dep_time(&new_data);
		else if (cols[i] == 6) change_res = input_arr_time(&new_data);
		else if (cols[i] == 7) change_res = input_price(&new_data);

	// Если строка не подходит под фильтр, то переписываем её
	// Иначе изменяем её по шаблону и записываем
	int is_error = 0;	// Ошибка чтения
	Flight buffer;		// Буфер для чтения полёта
	int len, fil_len;	// Количество записей в файле
	count_lines(old_table, filters, &len, &fil_len);
	rewind(old_table);

	for (int cur_line = 0; cur_line < len && !is_error; cur_line++)
		if (read_line(old_table, &buffer) != FIELDS_NUM) is_error = 1;
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

	if (is_error) return -2;
	return change_res;
}

// Изменить все записи, чьи номера есть в массиве
int edit_from_array(char *file_path, int len, int *to_edit, int edit_len) {
	/*
	Возвращает:
		-2: Ошибка чтения
		-1: Недостаток прав
		0: Успешное изменение
		1: Отмена изменения
	*/
	char new_file_path[FILE_NAME_LEN];
	FILE* new_table, * old_table;
	if (open_dable(file_path, new_file_path, &new_table, &old_table) == -1) return -1;

	const char* info = "Введите номера столбцов, которые вы хотите изменить, через запятую";
	printf("\n%s:\n", info);
	const char* cols_names[FIELDS_NUM];  // Названия колонок
	cols_names[0] = "Номер рейса";
	cols_names[1] = "Тип самолёта";
	cols_names[2] = "Пункт назначения";
	cols_names[3] = "Дни отправления";
	cols_names[4] = "Время вылета";
	cols_names[5] = "Время прилёта";
	cols_names[6] = "Цена билета";
	for (int col = 0; col < FIELDS_NUM; col++)
		printf("%d - %s\n", col + 1, cols_names[col]);
	printf("Ваш выбор: ");

	// Какие столбцы нужно поменять
	int cols[FIELDS_NUM];		// Массив номеров столбцов
	int last_ind = 0;	// Индекс последнего элемента массива
	int cols_res = 0;	// Результат ввода массива столбцов
	do {
		if (cols_res == 3) printf("Некорректный ввод.\n%s: ", info);
		cols_res = number_array_input(cols, &last_ind);
	} while (cols_res > 1);
	if (cols_res == 1) return 1;  // Отмена изменения

	// Создаём шаблон изменения
	int change_res = 0;	// Результат ввода новых значений
	Flight new_data;	// Тут будем хранить введённые данные
	for (int i = 0; i < last_ind && !change_res; i++)
		if (cols[i] == 1) change_res = input_fnum(&new_data);
		else if (cols[i] == 2) change_res = input_name(&new_data);
		else if (cols[i] == 3) change_res = input_dest(&new_data);
		else if (cols[i] == 4) change_res = input_days(&new_data);
		else if (cols[i] == 5) change_res = input_dep_time(&new_data);
		else if (cols[i] == 6) change_res = input_arr_time(&new_data);
		else if (cols[i] == 7) change_res = input_price(&new_data);

	// Изменяем нужные строчки
	int is_error = 0;	// Ошибка чтения
	Flight buffer;		// Буфер для чтения полёта
	int last_edit = 0;	// Для прохода по массиву to_edit
	int cur_line = 0;	// Для прохода по файлу

	printf("\n");
	for (; cur_line < len && last_edit < edit_len && !is_error; cur_line++)
		if (read_line(old_table, &buffer) != FIELDS_NUM) is_error = 1;
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
		if (read_line(old_table, &buffer) != FIELDS_NUM) is_error = 1;
		else write_line(new_table, buffer);

	// Удаляем прошлый файл и переименовываем новый
	fclose(new_table);
	fclose(old_table);
	remove(file_path);
	rename(new_file_path, file_path);

	if (is_error) return -2;
	return change_res;
}

// Удалить все подходящие под фильтр записи
int delete_all_filtered(char *file_path, Flight_filter filters[]) {
	/*
	Возвращает:
		-2: Ошибка чтения
		-1: Недостаток прав
		0: Успешное изменение
	*/
	char new_file_path[FILE_NAME_LEN];
	FILE* new_table, * old_table;
	if (open_dable(file_path, new_file_path, &new_table, &old_table) == -1) return -1;

	// Если строка не подходит под фильтр, то переписываем её
	int is_error = 0;	// Ошибка чтения
	Flight buffer;		// Буфер для чтения полёта
	int len, fil_len;	// Количество записей в файле
	count_lines(old_table, filters, &len, &fil_len);
	rewind(old_table);

	for (int cur_line = 0; cur_line < len && !is_error; cur_line++)
		if (read_line(old_table, &buffer) != FIELDS_NUM) is_error = 1;
		else if (!compare_flight(buffer, filters)) write_line(new_table, buffer);

	// Удаляем прошлый файл и переименовываем новый
	fclose(new_table);
	fclose(old_table);
	remove(file_path);
	rename(new_file_path, file_path);

	if (is_error) return -2;
	return 0;
}

// Удалить все записи, чьи номера есть в массиве
int delete_from_array(char *file_path, int len, int *to_del, int del_len) {
	/*
	Возвращает:
		-2: Ошибка чтения
		-1: Недостаток прав
		0: Успешное изменение
	*/
	char new_file_path[FILE_NAME_LEN];
	FILE* new_table, * old_table;
	if (open_dable(file_path, new_file_path, &new_table, &old_table) == -1) return -1;

	// Удаление будем совершать следующим образом:
	// Если номер строки в массиве - пропускаем её
	int is_error = 0;  // Ошибка чтения
	Flight buffer;  // Буфер для чтения полёта
	int last_del = 0;  // Для прохода по массиву to_del
	int cur_line = 0;  // Для прохода по файлу

	printf("\n");
	for (; cur_line < len && last_del < del_len && !is_error; cur_line++)
		if (read_line(old_table, &buffer) != FIELDS_NUM) is_error = 1;
		else if (cur_line + 1 < to_del[last_del]) write_line(new_table, buffer);
		else { printf("Строка %d успешно удалена\n", cur_line + 1); last_del++; }
	for (; cur_line < len && !is_error; cur_line++)
		if (read_line(old_table, &buffer) != FIELDS_NUM) is_error = 1;
		else write_line(new_table, buffer);

	// Удаляем прошлый файл и переименовываем новый
	fclose(new_table);
	fclose(old_table);
	remove(file_path);
	rename(new_file_path, file_path);

	if (is_error) return -2;
	return 0;
}