#define COLUMNS_NUM 7  // Количество столбцов
#define COLUMNS_SIZE 11  // Ширина строки в символах


void make_table(const char** row, char mode = 'a') {
    // Функция для отрисовки строки таблицы
    // row: массив указателей на слова, которые нужно вывести
    // mode: какие границы таблички использовать:
    // 'h' - (head) сейчас самый верх таблицы;
    // 'e' - (extra) нужно добавить строку, не отделяя от предыдущей;
    // 'a' - (add) нужно добавить отдельную строчку;
    // 'f' - (final) сейчас самый конец таблицы;
    // 's' - (space) нужно сделать отступ сверху или снизу;

    const char* edge = "-+|";
    switch (mode) {
    case 'h': {
        // Верх таблицы
        printf("%c", edge[1]);
        for (int i = 1; i < COLUMNS_NUM * (COLUMNS_SIZE + 1); i++)
            if (i % (COLUMNS_SIZE + 1)) printf("%c", edge[0]); else printf("%c", edge[1]);
        printf("%c\n", edge[1]);
        // make_table(row, 's');  // Делаем отступ сверху
        
        // Теперь выводим слова
        printf("%c", edge[2]);
        for (int w = 0; w < COLUMNS_NUM; w++) {
            const char* cur_word = row[w];    // Текущее слово
            int word_len = strlen(cur_word);  // Его длина
            if (word_len >= COLUMNS_SIZE)  // Если слово не помещается в столбик
                for (int i = 0; i < COLUMNS_SIZE; i++)
                    printf("%c", cur_word[i]);  // Выводим его посимвольно
            else {
                // Расстояние слева
                int left_space = (COLUMNS_SIZE - word_len) / 2;
                for (int i = 0; i < left_space; i++) printf(" ");
                // Вывод слова
                printf("%s", cur_word);
                // Расстояние справа
                int right_space = COLUMNS_SIZE - word_len - left_space;
                for (int i = 0; i < right_space; i++) printf(" ");
            }
            printf("%c", edge[2]);
        }
        printf("\n");
        // make_table(row, 's');  // Делаем отступ снизу
        break;
    }
    case 'e': {
        // Добавляем слова
        printf("%c", edge[2]);
        for (int w = 0; w < COLUMNS_NUM; w++) {
            const char* cur_word = row[w];    // Текущее слово
            int word_len = strlen(cur_word);  // Его длина
            if (word_len >= COLUMNS_SIZE)  // Если слово не помещается в столбик
                for (int i = 0; i < COLUMNS_SIZE; i++)
                    printf("%c", cur_word[i]);  // Выводим его посимвольно
            else {
                // Расстояние слева
                int left_space = (COLUMNS_SIZE - word_len) / 2;
                for (int i = 0; i < left_space; i++) printf(" ");
                // Вывод слова
                printf("%s", cur_word);
                // Расстояние справа
                int right_space = COLUMNS_SIZE - word_len - left_space;
                for (int i = 0; i < right_space; i++) printf(" ");
            }
            printf("%c", edge[2]);
        }
        printf("\n");
        // make_table(row, 's');  // Делаем отступ снизу
        break;
    }
    case 'a': {
        // Верх таблицы
        printf("%c", edge[1]);
        for (int i = 1; i < COLUMNS_NUM * (COLUMNS_SIZE + 1); i++)
            if (i % (COLUMNS_SIZE + 1)) printf("%c", edge[0]); else printf("%c", edge[1]);
        printf("%c\n", edge[1]);
        // Отступ один символ сверху от края
        /*printf("%c", edge[2]);
        for (int i = 1; i < COLUMNS_NUM * (COLUMNS_SIZE + 1); i++)
            if (i % (COLUMNS_SIZE + 1)) printf(" "); else printf("%c", edge[2]);
        printf("%c\n", edge[2]);*/
        // Теперь выводим слова
        printf("%c", edge[2]);
        for (int w = 0; w < COLUMNS_NUM; w++) {
            const char* cur_word = row[w];    // Текущее слово
            int word_len = strlen(cur_word);  // Его длина
            if (word_len >= COLUMNS_SIZE)  // Если слово не помещается в столбик
                for (int i = 0; i < COLUMNS_SIZE; i++)
                    printf("%c", cur_word[i]);  // Выводим его посимвольно
            else {
                // Расстояние слева
                int left_space = (COLUMNS_SIZE - word_len) / 2;
                for (int i = 0; i < left_space; i++) printf(" ");
                // Вывод слова
                printf("%s", cur_word);
                // Расстояние справа
                int right_space = COLUMNS_SIZE - word_len - left_space;
                for (int i = 0; i < right_space; i++) printf(" ");
            }
            printf("%c", edge[2]);
        }
        printf("\n");
        // Отступ один символ от слов
        /*printf("%c", edge[2]);
        for (int i = 1; i < COLUMNS_NUM * (COLUMNS_SIZE + 1); i++)
            if (i % (COLUMNS_SIZE + 1)) printf(" "); else printf("%c", edge[2]);
        printf("%c\n", edge[2]);*/
        break;
    }
    case 'f': {
        make_table(row);  // Отрисовываем слова как обычно
        // Низ таблицы
        printf("%c", edge[1]);
        for (int i = 1; i < COLUMNS_NUM * (COLUMNS_SIZE + 1); i++)
            if (i % (COLUMNS_SIZE + 1)) printf("%c", edge[0]); else printf("%c", edge[1]);
        printf("%c\n", edge[1]);
        break;
    }
    case 's': {
        printf("%c", edge[2]);
        for (int i = 1; i < COLUMNS_NUM * (COLUMNS_SIZE + 1); i++)
            if (i % (COLUMNS_SIZE + 1)) printf(" "); else printf("%c", edge[2]);
        printf("%c\n", edge[2]);
        break;
    }
    }
}
