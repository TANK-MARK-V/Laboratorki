import csv


TABLES = {  # Структура таблиц
    "ДеньНедели": ["id", "Название"],
    "Дисциплина": ["id", "Название", "ID_дня_недели", "ID_номера_пары"],
    "Пара": ["id", "№_пары", "Время_начала", "Время_конца"]
}

# Классы таблиц
class WeekDay:
    def __init__(self, name) -> None:
        self.name = name
    
    def __str__(self) -> str:
        return self.name

    def get_list(self) -> list:
        return [self.name]


class Lesson:
    def __init__(self, name: str, week_day_id: int | str, num: int | str) -> None:
        self.name = name
        self.week_day_id = int(week_day_id)
        self.num = int(num)
    
    def __str__(self) -> str:
        return f"{self.name}: {self.week_day_id} -> {self.num}"

    def get_list(self) -> list:
        return [self.name, self.week_day_id, self.num]


class Time:
    def __init__(self, num: int | str, start: str, end: str) -> None:
        self.num = int(num)
        self.start = start
        self.end = end

    def __str__(self) -> str:
        return f"{self.num}: {self.start} - {self.end}"

    def get_list(self) -> list:
        return [self.num, self.start, self.end]


# Действия с таблицами
def table_print(data: dict, table_name: str):
    """
    Вывести через print нужную таблицу
    data: словарь - таблица
    table_name: название таблицы
    """
    print(f"Таблица {table_name}:")
    for i in range(len(data[table_name])):
        # print(type())
        print(f"\t{i} ~ " + str(data[table_name][i]))


def add_row(data: dict, table_name: str, info: list):
    """
    Добавление в таблицу записи
    data: словарь - таблица
    table_name: название таблицы
    info: что нужно добавить
    """
    if table_name == "ДеньНедели":
       row = WeekDay(*info)
    if table_name == "Дисциплина":
       row = Lesson(*info)
    if table_name == "Пара":
       row = Time(*info)
    data[table_name].append(row)


def can_safe_delete(data: dict, table_name: str, ind: int) -> tuple:
    """
    Функция для проверки на возможность "безопасного" удаления записи
    "безопасное" удаление означает, что после удаления записи из таблицы
    не возникнет проблем с внешними ключами, ссылающимися на эту таблицу

    data: словарь - таблица
    table_name: название таблицы
    ind: индекс нужной записи
    
    Возвращает (True,), если возможно "безопасное" удаление
    Возвращает (False, indexes), если нет и список индексов,
    которые припятствуют удалению
    """
    check_column = []  # Все значения нужной колонки
    if table_name == "ДеньНедели":
        check_column = list(map(lambda x: x.week_day_id, data["Дисциплина"]))
    elif table_name == "Пара":
        check_column = list(map(lambda x: x.num, data["Дисциплина"]))
    
    indexes = []  # Индексы записей, которые препятствуют удалению
    for i in range(len(check_column)):
        if ind == check_column[i]:
            indexes.append(i)
    
    if not indexes:  # Можно "безопасно" удалить запись
        return (True,)
    return (False, indexes)


def delete_row(data: dict, table_name: str, ind: int) -> tuple:
    """
    Удаление из таблицы записи
    data: словарь - таблица
    table_name: название таблицы
    ind: индекс нужной записи

    Возвращает результат удаления (текст, список удалённых записей)
    """
    response = ""  # Текст для ответа
    deleted_elements = []  # Список удалённых записей

    try:
        safe_del = can_safe_delete(data, table_name, ind)
        if safe_del[0]:  # Если можно "безопасно" удалить
            response = "Элемент успешно удалён"
        else:  # Нет возможности удалить "безопасно"
            for i in safe_del[1][::-1]:
                deleted_elements.append(data["Дисциплина"].pop(i))
            deleted_elements = deleted_elements[::-1]
            response = "Элементы успешно удалены"
        deleted_elements.append(data[table_name].pop(ind))

    except Exception as e:
        response = f"В ходе удаления произошла ошибка:\n{e}"
    
    return (response, deleted_elements)


def edit_row(data: dict, table_name: str, ind: int, new_info: list):
    """
    Изменение записи из таблицы
    data: словарь - таблица
    table_name: название таблицы
    ind: индекс нужной записи

    Возвращает результат удаления (True/False, текст результата, старые данные)
    """
    if table_name == "ДеньНедели":
        new_info = WeekDay(*new_info)
    elif table_name == "Дисциплина":
        new_info = Lesson(*new_info)
    elif table_name == "Пара":
        new_info = Time(*new_info)

    if not table_name in ("ДеньНедели", "Пара"):  # В этих таблицах можно изменять данные без проверок
        # Проверим колонку "ID_дня_недели"
        week_day_id = new_info.week_day_id
        if week_day_id >= len(data["ДеньНедели"]):
            return (False, "Неверно указан ID_дня_недели")
        # Проверим колонку "ID_номера_пары"
        num = new_info.num
        if num >= len(data["Пара"]):
            return (False, "Неверно указан ID_номера_пары")
    
    old = data[table_name][ind]
    data[table_name][ind] = new_info
    return (True, "Данные успешно изменены", old)

# Работа с файлами
def write_table(data: dict, table_name: str):
    """
    Запись в .csv файл
    data: словарь - таблица
    table_name: название таблицы
    """
    with open(f"{table_name}.csv", 'w', newline='', encoding="UTF-8") as file:
        writer = csv.writer(file, delimiter=';')
        writer.writerow(TABLES[table_name])  # Шапка
        for ind in range(len(data[table_name])):
            writer.writerow([ind] + data[table_name][ind].get_list())


def read_file(data: dict, table_name: str) -> list:
    """
    Чтение .csv файла
    data: словарь - таблица
    table_name: название таблицы
    """
    table = []  # Конечная таблица
    try:
        with open(f"{table_name}.csv", 'r', newline='', encoding="UTF-8") as file:
            data = list(csv.reader(file, delimiter=';'))
            for line in data[1:]:
                if table_name == "ДеньНедели":
                    table.append(WeekDay(*line[1:]))
                elif table_name == "Дисциплина":
                    table.append(Lesson(*line[1:]))
                elif table_name == "Пара":
                    table.append(Time(*line[1:]))
    except Exception:
        table = []
    
    return table