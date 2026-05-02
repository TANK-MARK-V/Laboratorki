#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>      // Для fgets, getchar, stdin
#include <string.h>     // Для strlen, strcmp, strspn, strtok
#include <stdlib.h>     // Для strtol, strtod, INT_MIN, INT_MAX, calloc, free
#include <math.h>       // Для HUGE_VAL, log10

#include "input_funcs.h"

// Сохранение ввода в переменную и первичная обработка
int input(char buffer[], int mem, int *overflow) {
    /*
    buffer: указатель на строку, в которую нужно записать ввод
    mem: количество памяти, выделенное на строку (максимум mem - 1 символов)
    overflow: указатель на переменную для подсчёта символов, которые не влезли
    Возвращает:
        0: успешное чтение
        1: выход из ввода по сочетанию CANCEL
        2: пустая строка (сразу же нажат "Enter" иди только пробелы)
    */
    fgets(buffer, mem, stdin);
    // fgets ставит на место buffer[mem - 1] символ '\0'
    int len = strlen(buffer);

    // Очищаем вводной поток, если строчка не влезла
    int counter = 0;  // Для подсчёта лишних символов
    if (buffer[len - 1] != '\n')
        while (getchar() != '\n') counter++;
    else  // Удаляем '\n' с конца
        buffer[--len] = '\0';
    if (overflow != NULL) *overflow = counter;

    // Выход из ввода по сочетанию CANCEL
    if (!strcmp(buffer, CANCEL)) return 1;
    // Пустая строка (сразу же нажат "Enter" иди только пробелы)
    if (len == 0 || strspn(buffer, " ") == strlen(buffer)) return 2;

    return 0;
}

// Безопасный ввод int
int int_input(int *buffer) {
    /*
    buffer: указатель на int, в который нужно записать ввод
    Возвращает:
        0: успешное чтение
        1: выход из ввода по сочетанию CANCEL
        2: пустая строка (сразу же нажат "Enter" иди только пробелы)
        3: есть непрочитанный символ
        4: значение ввода выходит за границы int
    */
    char user_input[33];  // Буфер для ввода пользователя
    int input_res = input(user_input, 33);
    if (input_res) return input_res;  // Выход из ввода или пустая строка

    // Переводим в int
    long num;       // Число пользователя
    char* endptr;   // Указатель на первый непрочитанный символ
    num = strtol(user_input, &endptr, 10);

    // Если есть непрочитанный символ - результат 3
    if (*endptr != '\0') return 3;
    // Если значение выходит за границы - результат 4
    else if (num <= INT_MIN || INT_MAX <= num) return 4;

    *buffer = (int)num;
    return 0;
}

// Безопасный ввод double
int double_input(double *buffer) {
    /*
    buffer: указатель на double, в который нужно записать ввод

    Возвращает:
        0: успешное чтение
        1: выход из ввода по сочетанию CANCEL
        2: пустая строка (сразу же нажат "Enter" иди только пробелы)
        3: есть непрочитанный символ
        4: значение ввода выходит за границы double
    */
    char user_input[33];  // Буфер для ввода пользователя
    int input_res = input(user_input, 33);
    if (input_res) return input_res;  // Выход из ввода или пустая строка

    // Переводим в double
    double num;       // Число пользователя
    char* endptr;   // Указатель на первый непрочитанный символ
    num = strtod(user_input, &endptr);

    // Если есть непрочитанный символ - результат 3
    if (*endptr != '\0') return 3;
    // Если значение выходит за границы - результат 4
    else if (num == HUGE_VAL || num == -HUGE_VAL) return 4;

    *buffer = num;
    return 0;
}

// Безопасный ввод массива цифр
int number_array_input(int array[], int *len, int start, int end) {
    /*
    array: массив для хранения цифр
    len: указатель на переменную, в которую сохраним длину массива
    start: минимальная цифра массива
    end: максимальная цифра массива

    Возвращает:
        0: успешное чтение
        1: выход из ввода по сочетанию CANCEL
        2: пустая строка (сразу же нажат "Enter" иди только пробелы)
        3: некорректный ввод
    */
    char user_input[20];  // Буфер для ввода
    int input_res = input(user_input, 20);
    if (input_res) return input_res;  // Выход из ввода или пустая строка

    // Сохраним все допустимые цифры
    char symbols[30];  // Массив всех допустимых цифр
    int last_ind = 0;  // Индекс последнего элемента массива

    for (int i = start; i <= end && last_ind < 10; i++)
        symbols[last_ind++] = '0' + i;
    symbols[last_ind++] = ' '; symbols[last_ind++] = ','; symbols[last_ind++] = '\0';
    
    // Проверка на лишние символы - результат 3
    if (strspn(user_input, symbols) != strlen(user_input)) return 3;

    char* number;  // Указатель на цифру для strtok
    number = strtok(user_input, " ,");
    last_ind = 0;  // Обнуляем счётчик

    if ((number == NULL) || (strlen(number) > 1)) return 3;
    array[last_ind++] = *number - '0';
    while ((number = strtok(NULL, " ,")) != NULL) {
        if (strlen(number) > 1) return 3;
        int cur_number = *number - '0';
        // Проверим, есть ли эта цифра в списке
        int in_array = 0;
        for (int i = 0; i < last_ind; i++)
            if (array[i] == cur_number) in_array = 1;
        if (!in_array) array[last_ind++] = cur_number;
    }
    *len = last_ind;  // Сохраняем длину

    // Сортируем пузырьком
    for (int k = 1; k < last_ind; k++)
        for (int i = 0; i < last_ind - k; i++)
            if (array[i] > array[i + 1]) {
                int buffer = array[i];
                array[i] = array[i + 1];
                array[i + 1] = buffer;
            }

    return 0;
}

// Безопасный ввод массива натуральных чисел без повторений
int int_array_input(int **p_array, int len) {
    /*
    p_array: указатель на массив для чисел (память выделяется внутри функции)
    len: сколько всего может быть чисел (т.е. максимально возможное число)

    После работы функции получается массив (n1, n2, ..., 0).
    0 есть всегда и служит концом массива (т.к. числа только натуральные).
    
    Если 0 стоит первым, то пользователь ввёл "полный массив"
    "Полный массив" эквивалентен массиву [1, 2, ..., len - 1, len, 0]
    При этом "полный массив" выглядит как [0] для экономии памяти

    Возвращает:
        -1: ошибка выделения памяти
        0: успешное чтение массива
        1: выход из ввода по сочетанию CANCEL
        2: пустая строка (сразу же нажат "Enter" иди только пробелы)
        3: некорректный ввод
        4: строчка не влезла
    */
    int buffer_len = len * ((int)log10(len) + 3) + 4;  // Выделяем память с расчётом:
    // кол-во чисел * (длина максимального числа + 2 знака на разделение ", ") + 4 запасных символа
    char* user_input = (char*)calloc(buffer_len, sizeof(char));
    if (user_input == NULL) return -1;
    int overflow;  // Сколько символов не влезло
    int input_res = input(user_input, buffer_len, &overflow);

    // Строчка не влезла
    if (overflow) {
        free(user_input);
        return 4;
    }
    if (input_res) {  // Выход из ввода или пустая строка
        free(user_input);
        return input_res;
    }
    if (strspn(user_input, " ,0123456789") != strlen(user_input)) {  // лишние символы - результат 3
        free(user_input);
        return 3;
    }
    // Проверяем на "0" - "полный массив"
    if (!strcmp(user_input, "0")) {
        free(user_input);
        if ((*p_array = (int*)calloc(1, sizeof(int))) == NULL) return -1;
        **p_array = 0;  // Ставим 0 в начало массива
        return 0;
    }
    else {  // В ином случае сразу создаём новый массив
        *p_array = (int*)calloc(len + 1, sizeof(int));  // Массив для номеров
        if (*p_array == NULL) {
            free(user_input);
            return -1;
        }
    }
    // Начинаем разбирать строчку на номера записей
    int last_ind = 0;   // Индекс последнего элемента
    char* number;       // Строка-число для strtok
    char* endptr;       // Указатель на символ для strtol

    number = strtok(user_input, " ,");
    if (number == NULL) {
        free(user_input);
        free(*p_array);
        return 3;
    }
    do {
        long cur_num_long = strtol(number, &endptr, 10);
        // Проверяем на корректность числа
        if (cur_num_long < 1 || len < cur_num_long) continue;
        int cur_num = (int)cur_num_long;
        // Проверим, есть ли число в массиве
        int in_list = 0;  
        for (int i = 0; i < last_ind; i++)
            if ((*p_array)[i] == cur_num) in_list = 1;
        if (!in_list) (*p_array)[last_ind++] = cur_num;
    } while ((number = strtok(NULL, " ,")) != NULL);
    free(user_input);
    
    // Нет ни одного корректного числа - код 3
    if (last_ind == 0) {
        free(*p_array);
        return 3;
    }

    // Сортируем массив по убыванию пузырьком
    for (int k = 1; k < last_ind; k++)
        for (int i = 0; i < last_ind - k; i++)
            if ((*p_array)[i] > (*p_array)[i + 1]) {
                int buffer = (*p_array)[i];
                (*p_array)[i] = (*p_array)[i + 1];
                (*p_array)[i + 1] = buffer;
            }
    *(*p_array + last_ind) = 0;  // Ставим в конце 0
    return 0;
}

// Ввод времени в формате xx.xx или xx:xx и преобразование в int
int input_time(int *buffer) {
    /*
    Возвращает:
        0: успешное чтение массива
        1: выход из ввода по сочетанию CANCEL
        3: некорректный ввод
    */
    int time[2];   // Массив для времени (часы и минуты)
    char user_input[6];  // Буфер для ввода
    int input_res;  // Результат ввода

    do input_res = input(user_input, 6);
    while (input_res == 2);  // Пока не получим непустую строку
    if (input_res == 1) return 1;  // Выход из ввода

    // Проверим на лишние символы
    if (strspn(user_input, " .:0123456789") != strlen(user_input)) return 3;
    char* parts[2];  // Разделим ввод на несколько частей
    parts[0] = strtok(user_input, " .:");
    parts[1] = strtok(NULL, " .:");

    // Строка должна поделиться на две части, а третьей быть NULL
    if ((parts[1] == NULL) || (strtok(NULL, " .:") != NULL)) return 3;

    // Длина первой части должна быть 1 или 2
    int part_len = strlen(parts[0]);
    if (part_len == 1)
        time[0] = parts[0][0] - '0';
    else if (part_len == 2)
        time[0] = (parts[0][0] - '0') * 10 + parts[0][1] - '0';
    else return 3;
    // Длина второй всегда 2
    if (strlen(parts[1]) == 2)
        time[1] = (parts[1][0] - '0') * 10 + parts[1][1] - '0';
    else return 3;
    
    // Проверим на корректные значения
    if (time[0] > 23 || time[1] > 59) return 3;

    *buffer = time[0] * 60 + time[1];
    return 0;
}