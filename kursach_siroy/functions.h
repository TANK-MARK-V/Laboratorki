#pragma once

#include "structure.h"  // Работа со структурой

// Подготовка пользователя
int user_prepare(char file_path[]);

// Выбор первичного действия
int get_first_action(Flight_filter filters[]);

// Выбор действия по вводу и корректировке списка
int get_edit_action(Flight_filter filters[]);
