//#include <string.h>  // Работа со строками


// Функции для сложения двух строк (т.е. связывание или конкатенация)
char* mystrcat(char* destination, const char* source) {
    // Добавить копию строки sourse в конец строки destination
    // destination: строка, в которую произойдёт запись
    // source: строка, которую запишем

    // Найдём индекс символа '\0' в строке destination, т.е. её конец
    int start;
    for (start = 0; destination[start]; start++);
    // Найдём длину строки source
    int len;
    for (len = 0; source[len]; len++);
    // Теперь добавим sourse в конец destination
    for (int i = 0; i < len; i++)
        destination[start + i] = source[i];
    // Добавим в конец '\0'
    destination[start + len] = '\0';

    return destination;
}


char* mystrncat(char* destination, const char* source, int n) {
    // Добавить копию первых n символов строки sourse в конец строки destination
    // destination: строка, в которую произойдёт запись
    // source: строка, которую запишем
    // n: сколько символов нужно записать

    // Найдём индекс символа '\0' в строке destination, т.е. её конец
    int start;
    for (start = 0; destination[start]; start++);
    // Найдём длину строки source, чтобы не выйти за её границы
    int len;
    for (len = 0; source[len]; len++);
    if (len > n) len = n;  // Т.е. len = min(len, n)
    // Теперь добавим sourse в конец destination
    for (int i = 0; i < len; i++)
        destination[start + i] = source[i];
    // Добавим в конец '\0'
    destination[start + len] = '\0';

    return destination;
}


// Функции для сравнения двух строк
int mystrcmp(const char* string1, const char* string2) {
    // Сравнение двух строк с учётом регистра
    // *string1, *string2: строки, которые нужно сравнить

    int result = 0;
    for (int i = 0; (string1[i] || string2[i]) && !result; i++)
        result = string1[i] - string2[i];
    // Конечный ответ может быть только одним из чисел {-1, 0, 1}
    if (result < 0) result = -1;
    else if (result < 0) result = 1;

    return result;
}


int mystricmp(const char* string1, const char* string2) {
    // Сравнение двух строк без учёта регистра
    // *string1, *string2: строки, которые нужно сравнить

    int result = 0;
    for (int i = 0; (string1[i] || string2[i]) && !result; i++) {
        char char1 = string1[i], char2 = string2[i];
        // Преобразуем оба символа в верхний регистр, если они в нижнем (на обоих языках
        if (('a' <= char1) && (char1 <= 'z')) char1 -= 'a' - 'A';
        else if (('а' <= char1) && (char1 <= 'я')) char1 -= 'а' - 'А';
        if (('a' <= char2) && (char2 <= 'z')) char2 -= 'a' - 'A';
        else if (('а' <= char2) && (char2 <= 'я')) char2 -= 'а' - 'А';
        // Теперь сравним символы
        result = char1 - char2;
    }
    // Конечный ответ может быть только одним из чисел {-1, 0, 1}
    if (result < 0) result = -1;
    else if (result < 0) result = 1;

    return result;
}


int mystrncmp(const char* string1, const char* string2, int n) {
    // Сравнение первых n символов двух строк с учётом регистра
    // *string1, *string2: строки, которые нужно сравнить
    // n: сколько символов нужно сравнить

    int result = 0;
    for (int i = 0; (string1[i] || string2[i]) && !result && i < n; i++)
        result = string1[i] - string2[i];
    // Конечный ответ может быть только одним из чисел {-1, 0, 1}
    if (result < 0) result = -1;
    else if (result < 0) result = 1;

    return result;
}


int mystrnicmp(const char* string1, const char* string2, int n) {
    // Сравнение первых n символов двух строк без учёта регистра
    // *string1, *string2: строки, которые нужно сравнить
    // n: сколько символов нужно сравнить

    int result = 0;
    for (int i = 0; (string1[i] || string2[i]) && !result && i < n; i++) {
        char char1 = string1[i], char2 = string2[i];
        // Преобразуем оба символа в верхний регистр, если они в нижнем (на обоих языках
        if (('a' <= char1) && (char1 <= 'z')) char1 -= 'a' - 'A';
        else if (('а' <= char1) && (char1 <= 'я')) char1 -= 'а' - 'А';
        if (('a' <= char2) && (char2 <= 'z')) char2 -= 'a' - 'A';
        else if (('а' <= char2) && (char2 <= 'я')) char2 -= 'а' - 'А';
        // Теперь сравним символы
        result = char1 - char2;
    }
    // Конечный ответ может быть только одним из чисел {-1, 0, 1}
    if (result < 0) result = -1;
    else if (result < 0) result = 1;

    return result;
}


// Функции для копирования строк
char* mystrcpy(char* destination, const char* source) {
    // Скопировать строку source в строку destination
    // destination: строка, в которую произойдёт запись
    // source: строка, которую запишем

    int i;
    for (i = 0; source[i]; i++)
        destination[i] = source[i];
    // Добавим в конец '\0'
    destination[i] = '\0';

    return destination;
}


char* mystrncpy(char* destination, const char* source, int n) {
    // Скопировать строку source в строку destination
    // destination: строка, в которую произойдёт запись
    // source: строка, которую запишем
    // n: сколько символов нужно сравнить

    int i;
    for (i = 0; source[i] && i < n; i++)
        destination[i] = source[i];
    for (; i < n; i++)
        destination[i] = '\0';

    return destination;
}


// Функции для поиска в строке
int mystrlen(const char* string) {
    // Найти длину указанной строки
    // string: строка, длину которой нужно найти
    int len;
    for (len = 0; string[len]; len++);
    return len;
}


char* mystrchr(char* string, const char symbol) {
    // Найти первое вхождение символа symbol в строке string
    // string: строка, в которой ищем символ
    // symbol: символ, который ищем в строке

    char* point = NULL;
    for (int i = 0; string[i] && !point; i++)
        if (string[i] == symbol) point = string + i;

    return point;
}


char* mystrrchr(char* string, const char symbol) {
    // Найти последнее вхождение символа symbol в строке string
    // string: строка, в которой ищем символ
    // symbol: символ, который ищем в строке

    char* point = NULL;
    for (int i = 0; string[i]; i++)
        if (string[i] == symbol) point = string + i;

    return point;
}


char* mystrpbrk(char* string, const char* find) {
    // Найти первый встретившийся в строке string символ, который есть в строке find
    // string: строка, в которой ищем символы
    // find: строка, символы которой мы ищем

    char* point = NULL;
    for (int i = 0; string[i] && !point; i++)
        for (int j = 0; find[j] && !point; j++)
            if (string[i] == find[j]) point = string + i;

    return point;
}


int mystrspn(const char* string, const char* find) {
    // Находит в строке string первый сегмент,
    // состоящий только из символов строки find, и находит его длину
    // string: строка, в которой ищем сегмент
    // find: строка, из символов которой должен состоять сегмент

    int count_mode = 1;
    // 1 - сегмент пока не найден или уже считаем его длину, 0 - сегмент кончился
    int len = 0;  // Длина сегмента
    for (int i = 0; string[i] && count_mode; i++) {
        int is_good = 0;  // Подходит ли символ строки string условию
        for (int j = 0; find[j] && !is_good; j++)
            if (string[i] == find[j]) { is_good = 1; len += 1; }
        if (!is_good && len) count_mode = 0;
    }
    return len;
}


int mystrсspn(const char* string, const char* find) {
    // Находит в строке string первый сегмент,
    // состоящий только из символов, отсутствующих в строке find, и находит его длину
    // string: строка, в которой ищем сегмент
    // find: строка, из символов которой должен состоять сегмент

    int count_mode = 1;
    // 1 - сегмент пока не найден или уже считаем его длину, 0 - сегмент кончился
    int len = 0;  // Длина сегмента
    for (int i = 0; string[i] && count_mode; i++) {
        int is_good = 1;  // Подходит ли символ строки string условию
        for (int j = 0; find[j] && !is_good; j++)
            if (string[i] == find[j]) is_good = 0;
        if (is_good) len += 1;
        else if (!is_good && len) count_mode = 0;
    }
    return len;
}


char* mystrstr(char* string, const char* find) {
    // Найти первое вхождение строки find в строку string
    // string: строка, в которой производим поиск
    // find: строка, которую ищем

    char* point = NULL;
    for (int i = 0; string[i] && !point; i++)
        if (string[i] == find[0]) {
            int equals = 1;  // На данный момент все символы совпадают
            for (int j = 1; (string[i + j] || find[j]) && equals; j++)
                if (string[i + j] != find[j]) equals = 0;
            if (equals) point = string + i;
        }
    return point;
}


// Функции для изменения строк
char* mystrlwr(char* string) {
    // Преобразовать буквы верхнего регистра строки string в буквы нижнего регистра
    // string: изменяемая строка
    for (int i = 0; string[i]; i++)
        if (('A' <= string[i]) && (string[i] <= 'Z')) string[i] += 'a' - 'A';
        else if (('А' <= string[i]) && (string[i] <= 'Я')) string[i] += 'а' - 'А';
    return string;
}


char* mystrupr(char* string) {
    // Преобразовать буквы нижнего регистра строки string в буквы верхнего регистра
    // string: изменяемая строка
    for (int i = 0; string[i]; i++)
        if (('a' <= string[i]) && (string[i] <= 'z')) string[i] -= 'a' - 'A';
        else if (('а' <= string[i]) && (string[i] <= 'я')) string[i] -= 'а' - 'А';
    return string;
}


char* mystrset(char* string, const char symbol) {
    // Установить все символы строки string в символы symbol
    // string: изменяемая строка
    // symbol: нужный символ
    for (int i = 0; string[i]; i++) string[i] = symbol;
    return string;
}


char* mystrnset(char* string, const char symbol, int n) {
    // Установить все символы строки string в символы symbol
    // string: изменяемая строка
    // symbol: нужный символ
    // n: сколько символов нужно установить
    for (int i = 0; string[i] && i < n; i++) string[i] = symbol;
    return string;
}


char* mystrrev(char* string) {
    // Перезаписать строчку задом наперёд, не считая последний символ ('\n')
    // string: изменяемая строка
    // Сначала найдём длину строки
    int len;
    for (len = 0; string[len]; len++);
    for (int i = 0; i < len / 2; i++) {
        char symbol;  // Хранилище для символа
        symbol = string[i];
        string[i] = string[len - i - 1];
        string[len - i - 1] = symbol;
    }
    return string;
}


// Свои функции
void mystrview(const char* string, int n = 0) {
    // Функция для просмотра содержимого строки
    // string: строчка, которую нужно просмотреть
    // n: число символов, которые мы хотим посмотреть.
    // Значение по умолчанию n=0 означает просмотр строчки целиком
    if (n) printf("Строка: %.*s\n", n, string);
    else printf("Строка: %s\n", string);
    if (string != NULL) {
        int i;
        for (i = 0; (string[i] && ((n == 0) || (n > 0 && i < n - 1))); i++)
            printf("\ti = %d: %c ~ %d\n", i, string[i], string[i]);
        printf("\ti = %d: %c ~ %d\n", i, string[i], string[i]);
    }
}

int mystrcount(const char* string, const char symbol) {
    // Функция для подсчёта количества символов symbol в строке string
    // string: строка, в которой считаем символы
    // symbol: символ, количество которого нужно посчитать
    int counter = 0;
    for (int i = 0; string[i]; i++) counter += string[i] == symbol;
    return counter;
}