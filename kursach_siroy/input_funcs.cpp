#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "input_funcs.h"


// Сохранение ввода в переменную и первичная обработка
int input(char** buffer, int len, int dynamic) {
    /*
    buffer: указатель на строку, в которую нужно записать ввод
    len: длина ввода (без учёта '\0', т.е. выделяется len + 1 памяти)
    dynamic: нужно ли выделить память на строку (0, если для buffer уже выделена память - 1, если память не выделена)

    Возвращает:
        1: пустая строка (сразу же нажат "Enter")
        0: успешное чтение
        -1: ошибка выделения памяти
    */
    if (dynamic) {  // Выделение памяти, если нужно
        *buffer = (char*)calloc(len + 1, sizeof(char));
        if (*buffer == NULL) return -1;  // Не хватило памяти
    }

    fgets(*buffer, len + 1, stdin);
    // Передаём len + 1, чтобы fgets получал len символов и после ставил '\0'

    if ((*buffer)[0] == '\n') {  // Если пользователь сразу закончил ввод
        if (dynamic) free(*buffer);
        return 1;
    }

    // Очищаем вводной поток, если строчка не влезла
    if ((*buffer)[strlen(*buffer) - 1] != '\n')
        while (getchar() != '\n');
    else  // Удаляем '\n' с конца
        (*buffer)[strlen(*buffer) - 1] = '\0';

    return 0;
}

// Безопасный ввод int
int int_input(int* buffer) {
    /*
    buffer: указатель на int, в который нужно записать ввод

    Возвращает:
        0: успешное чтение
        1: выход из ввода по "###"
        2: введена пустая строка
        3: есть непрочитанный символ
        4: значение ввода выходит за границы int
    */
    char user_input[33];  // Буфер для ввода пользователя
    fgets(user_input, 33, stdin);  // Ввод пользователя
    // Очищаем вводной поток, если строчка не влезла
    if (user_input[strlen(user_input) - 1] != '\n')
        while (getchar() != '\n');
    else  // Удаляем '\n' с конца
        user_input[strlen(user_input) - 1] = '\0';

    int result = 0;  // Результат выполнения функции
    long num;  // Число пользователя
    // Проверяем на выход из ввода "###" - результат 1
    if (!strcmp(user_input, "###")) result = 1;
    else {
        // Переводим в int
        char* endptr;  // Указатель на первый непрочитанный символ
        num = strtol(user_input, &endptr, 10);
        // Если есть непрочитанный символ - результат 3
        if (*endptr != '\0') result = 3;
        // Если строка пустая - результат 2
        else if (endptr == user_input) result = 2;
        // Если значение выходит за границы - результат 4
        else if (num <= INT_MIN || INT_MAX <= num) result = 4;
    }
    if (!result) *buffer = (int)num;
    return result;
}

// Безопасный ввод double
int double_input(double* buffer) {
    /*
    buffer: указатель на double, в который нужно записать ввод

    Возвращает:
        0: успешное чтение
        1: выход из ввода по "###"
        2: введена пустая строка
        3: есть непрочитанный символ
        4: значение ввода выходит за границы double
    */
    char user_input[33];  // Буфер для ввода пользователя
    fgets(user_input, 33, stdin);  // Ввод пользователя
    // Очищаем вводной поток, если строчка не влезла
    if (user_input[strlen(user_input) - 1] != '\n')
        while (getchar() != '\n');
    else  // Удаляем '\n' с конца
        user_input[strlen(user_input) - 1] = '\0';

    int result = 0;  // Результат выполнения функции
    double num;  // Число пользователя
    // Проверяем на выход из ввода "###" - результат 1
    if (!strcmp(user_input, "###")) result = 1;
    else {
        // Переводим в double
        char* endptr;  // Указатель на первый непрочитанный символ
        num = strtod(user_input, &endptr);
        // Если есть непрочитанный символ - результат 3
        if (*endptr != '\0') result = 3;
        // Если строка пустая - результат 2
        else if (endptr == user_input) result = 2;
        // Если значение выходит за границы - результат 4
        else if (num == HUGE_VAL || num == -HUGE_VAL) result = 4;
    }
    if (!result) *buffer = num;
    return result;
}

// Безопасный ввод массива цифр
int input_number_list(int list[], int *len, int start, int end) {
    /*
    list: список для хранения цифр
    len: указатель на переменную, в которую сохраним длину массива
    start: минимальная цифра массива
    end: максимальная цифра массива

    Возвращает:
        0: успешное чтение
        1: выход из ввода по "###"
        2: введена пустая строка
        3: некорректный ввод
    */
    char user_input[20];  // Буфер для ввода
    char* p_input = user_input;  // Указатель на буфер

    // Если строка пустая - результат 2
    if (input(&p_input, 19)) return 2;
    // Проверяем на выход из ввода "###" - результат 1
    if (!strcmp(user_input, "###")) return 1;  // Закончить ввод

    // Сохраним все допустимые цифры
    char symbols[13];  // Массив всех допустимых цифр
    int last_ind = 0;  // Индекс последнего элемента массива
    for (int i = start; i <= end && last_ind < 10; i++)
        symbols[last_ind++] = '0' + i;
    symbols[last_ind++] = ' '; symbols[last_ind++] = ','; symbols[last_ind++] = '\0';
    last_ind = 0;  // Используем этот счётчик ещё раз в будущем
    
    // Проверка на лишние символы - результат 3
    if (strspn(user_input, symbols) != strlen(user_input)) return 3;
    char* number;  // Указатель на цифру для strtok
    number = strtok(user_input, " ,");
    if ((number == NULL) || (strlen(number) > 1)) return 3;
    list[last_ind++] = *number - '0';
    while ((number = strtok(NULL, " ,")) != NULL) {
        if (strlen(number) > 1) return 3;
        int cur_number = *number - '0';
        // Проверим, есть ли эта цифра в списке
        int in_list = 0;
        for (int i = 0; i < last_ind; i++)
            if (list[i] == cur_number) in_list = 1;
        if (!in_list) list[last_ind++] = cur_number;
    }
    *len = last_ind;  // Сохраняем длину

    // Сортируем пузырьком
    for (int k = 1; k < last_ind; k++)
        for (int i = 0; i < last_ind - k; i++)
            if (list[i] > list[i + 1]) {
                int buffer = list[i];
                list[i] = list[i + 1];
                list[i + 1] = buffer;
            }

    return 0;
}


// Безопасный ввод массива натуральных чисел без повторений
int int_array_input(int **pp_array, int len) {
    /*
    p_array: указатель на указатель на массив для чисел (память выделяется внутри функции)
    len: сколько всего может быть чисел (т.е. максимально возможное число)

    После работы функции получается массив (n1, n2, ..., 0).
    0 есть всегда и служит концом массива (т.к. числа только натуральные).
    
    Если 0 стоит первым, то пользователь ввёл "полный массив"
    "Полный массив" эквивалентент массиву [1, 2, ..., len - 1, len, 0]
    При этом "полный массив" выглядит как [0] для экономии памяти

    Возвращает:
        -1: ошибка выделения памяти
        0: успешное чтение массива
        1: выход из ввода по "###"
        2: введена пустая строка
        3: некорректный ввод
    */
    int buffer_len = len * ((int)log10(len) + 3) + 4;  // Выделяем память с расчётом:
    // кол-во чисел * (длина максимального числа + 2 знака на разделение ", ") + 4 запасных символа
    char* user_input = (char*)calloc(buffer_len, sizeof(char));
    if (user_input == NULL) return -1;

    fgets(user_input, buffer_len, stdin);

    // Очищаем вводной поток, если строчка не влезла и завершаем обработку
    if (user_input[strlen(user_input) - 1] != '\n') {
        while (getchar() != '\n');
        free(user_input);
        return 3;
    }
    else  // Удаляем '\n' с конца
        user_input[strlen(user_input) - 1] = '\0';

    // Проведём различные проверки
    // Выход из ввода по "###" - результат 1
    // Введена пустая строка - результат 2
    // Лишние символы - результат 3
    int code = -2;  // Начальное значение -2, т.к. такого кода нет
    if (!strcmp(user_input, "###")) code = 1;
    else if (!strlen(user_input)) code = 2;
    else if (strspn(user_input, " ,0123456789") != strlen(user_input)) code = 3;
    // Проверяем на "0" - "полный массив"
    else if (!strcmp(user_input, "0"))
        if ((*pp_array = (int*)calloc(1, sizeof(int))) == NULL) code = -1;
        else code = **pp_array = 0;  // Ставим 0 в начало массива и код = 0
    else {  // В ином случае сразу создаём новый массив
        *pp_array = (int*)calloc(len + 1, sizeof(int));  // Массив для номеров
        if (*pp_array == NULL) code = -1;
    }
    // Если какая-то проверка прошла
    if (code != -2) {
        free(user_input);
        return code;  // Завершаем выполнение программы
    }

    // Объявляем нужные переменные
    int last_ind = 0;  // Индекс последнего элемента
    char* number;  // Строка-число для strtok
    char* endptr;  // Указатель на символ для strtol

    // Начинаем разбирать строчку на номера записей
    number = strtok(user_input, " ,");
    if (number == NULL) {
        free(user_input);
        free(*pp_array);
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
            if ((*pp_array)[i] == cur_num) in_list = 1;
        if (!in_list) (*pp_array)[last_ind++] = cur_num;
    } while ((number = strtok(NULL, " ,")) != NULL);
    free(user_input);
    
    // Нет ни одного корректного числа - код 3
    if (last_ind == 0) {
        free(*pp_array);
        return 3;
    }

    // Сортируем массив по убыванию пузырьком
    for (int k = 1; k < last_ind; k++)
        for (int i = 0; i < last_ind - k; i++)
            if ((*pp_array)[i] > (*pp_array)[i + 1]) {
                int buffer = (*pp_array)[i];
                (*pp_array)[i] = (*pp_array)[i + 1];
                (*pp_array)[i + 1] = buffer;
            }
    *(*pp_array + last_ind) = 0;  // Ставим в конце 0
    return 0;
}


// Ввод времени в формате xx.xx или xx:xx и преобразование в int
int input_time(int* buffer) {
    /*
    Возвращает:
        0: успешное чтение
        1: выход из ввода по "###"
        2: некорректный ввод
    */
    int time[2];   // Массив для времени (часы и минуты)
    char user_input[6];  // Буфер для ввода
    char* p_input = user_input;  // Указатель на буфер
    int result = 0;  // Результат ввода

    do result = input(&p_input, 5);
    while (result);  // Ввод, пока не получим непустую строку
    if (!strcmp(user_input, "###")) return 1;  // Закончить ввод

    // Проверим на лишние символы
    if (strspn(user_input, " .:0123456789") != strlen(user_input)) return 2;
    char* parts[2];  // Разделим ввод на несколько частей
    parts[0] = strtok(user_input, " .:");
    parts[1] = strtok(NULL, " .:");

    // Строка должна поделиться на две части, а третьей быть NULL
    if ((parts[1] == NULL) || (strtok(NULL, " .:") != NULL)) return 2;
    // Длина первой части должна быть 1 или 2
    switch (strlen(parts[0])) {
    case 1: { time[0] = parts[0][0] - '0'; break; }
    case 2: { time[0] = (parts[0][0] - '0') * 10 + parts[0][1] - '0'; break; }
    default: return 2;
    }
    // Длина второй всегда 2
    if (strlen(parts[1]) != 2) return 2;
    time[1] = (parts[1][0] - '0') * 10 + parts[1][1] - '0';

    // Проверим на корректные значения
    if (time[0] > 23 || time[1] > 59) return 2;

    *buffer = time[0] * 60 + time[1];
    return 0;
}