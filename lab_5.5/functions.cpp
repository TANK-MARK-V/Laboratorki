#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "functions.h"


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
    return 0;
}
