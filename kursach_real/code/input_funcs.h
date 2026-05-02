#pragma once

#define CANCEL "###"  // Отмена ввода

// Сохранение ввода в переменную и первичная обработка
int input(char buffer[], int mem, int *overflow = NULL);

// Безопасный ввод int
int int_input(int *buffer);

// Безопасный ввод double
int double_input(double *buffer);

// Безопасный ввод массива цифр
int number_array_input(int array[], int *len, int start = 1, int end = 7);

// Безопасный ввод массива натуральных чисел без повторений
int int_array_input(int **p_array, int len);

// Ввод времени в формате xx.xx или xx:xx и преобразование в int
int input_time(int *buffer);