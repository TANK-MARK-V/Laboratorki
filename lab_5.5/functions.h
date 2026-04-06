#pragma once


// Сохранение ввода в переменную и первичная обработка
int input(char** buffer, int len = 15, int dynamic = 0);

// Безопасный ввод int
int int_input(int* buffer);

// Безопасный ввод double
int double_input(double* buffer);

// Безопасный ввод массива цифр
int input_number_list(int list[], int *len, int start = 1, int end = 7);