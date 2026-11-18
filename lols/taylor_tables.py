TABLES = {  # Структура таблицы результатов
    "Результаты": ["x", "y", "cbrt(x)"],
}

EXTRA = 5  # Дополнительное место для красоты


def table_print(rows: list[dict], table_name: str, col: int, space: int, wide: int, right: int):
    """
    Вывести через print нужную таблицу в консоль.

    rows: список строк результата
    table_name: название таблицы
    col, space, wide, right: параметры форматирования (как в C-версии)
    """
    print(f"Таблица {table_name}:")
    edge(1, col, wide)
    edge(0, col, wide)
    edge(1, col, wide)

    for row in rows:
        center(col, space, right, row["x"])
        if row["y"] is None:  # Ряд не сходится
            print("*", end="")
            for i in range(col):
                print("-" if (col // 2) == i else " ", end="")
        else:
            center(col, space, right, row["y"])
        center(col, space, right, row["root"])
        print("*")
    edge(1, col, wide)


def edge(line: int, col: int, wide: int):
    """
    Вывод горизонтальных линий и шапки таблицы.

    line: 1 - горизонтальная линия, 0 - шапка
    col: ширина колонки
    wide: ширина всей таблицы
    """
    if line:
        print("*" * wide)
    else:
        # Шапка таблицы
        print("*", end="")
        for i in range(col):
            print("x" if (col // 2) == i else " ", end="")
        print("*", end="")
        for i in range(col):
            print("y" if (col // 2) == i else " ", end="")
        print("*", end="")
        for i in range(col - 6):
            print("cbrt(x)" if (col // 2) == (i + 3) else " ", end="")
        print("*")


def center(col: int, space: int, right: int, num: float):
    """
    Вывод переменных по центру колонки.

    col: ширина колонки
    space: расстояние от колонки до числа
    right: число цифр после запятой
    num: число для вывода
    """
    print("*", end="")
    print(f"{space + right + 1 + (col - space - right - 1):.{right}f}", end="")
    print(" " * space, end="")