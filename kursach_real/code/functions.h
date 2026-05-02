#pragma once

#include "structure.h"	// Для Flight_filter

// Подготовка пользователя
int user_prepare(char *file_path);

// Выбор первичного действия
int get_first_action(Flight_filter filters[]);

// Выбор действия по вводу и корректировке списка
int get_edit_action(Flight_filter filters[]);

// Меню "Изменение записей"
int edit_menu(char *file_path, Flight_filter filters[]);

// Меню "Удаление записей"
int delete_menu(char *file_path, Flight_filter filters[]);

// Меню "Установка фильтров"
int filters_menu(Flight_filter filters[]);
