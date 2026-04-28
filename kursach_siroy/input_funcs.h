#pragma once


// Сохранение ввода в переменную и первичная обработка
int input(char** buffer, int len = 15, int dynamic = 0);

// Безопасный ввод int
int int_input(int* buffer);

// Безопасный ввод double
int double_input(double* buffer);

// Безопасный ввод массива цифр
int input_number_list(int list[], int *len, int start = 1, int end = 7);

// Безопасный ввод массива натуральных чисел без повторений
int int_array_input(int** pp_array, int len);

// Ввод времени в формате xx.xx или xx:xx и преобразование в int
int input_time(int* buffer);