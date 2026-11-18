import math


def taylor(x: float, e: float) -> float | None:
    """
    Разложение функции в ряд Тейлора.

    Идея сохранения n-го члена для домножения до n + 1:
    каждый n домножается на (x - 1);
    член n <= 2 домножается на 1/3;
    член n > 2 домножается на (5 + 3*(n-3)) и делится на (9 + 3*(n-3));
    члены n > 1 меняют знаки.

    x: значение аргумента
    e: точность

    Возвращает сумму ряда или None, если ряд не сходится
    (в оригинале возвращалось x + 1 как признак расходимости)
    """
    total = 0.0  # Сумма членов ряда
    previous_mem: float  # Предыдущий член ряда
    current_mem = 1.0  # Текущий член ряда
    n = 0  # Номер члена в ряду

    do_continue = True
    while do_continue:
        # Сохраняем последний член, добавляем его к сумме, увеличиваем номер на 1
        previous_mem = current_mem
        total += current_mem
        n += 1
        if n > 1:
            current_mem *= -1
        if n <= 2:
            current_mem *= 1.0 / 3
        else:
            current_mem *= (5 + 3 * (n - 3)) / (9 + 3 * (n - 3))
        current_mem *= x - 1

        do_continue = (abs(current_mem) > e) and (abs(previous_mem) > abs(current_mem))

    # Признак расходимости ряда
    if abs(previous_mem) > abs(current_mem):
        return total
    return None


def check_bounds(x1: float, x2: float) -> tuple[bool, str]:
    """
    Проверка границ диапазона.

    Возвращает (True, "") если всё в порядке,
    иначе (False, текст ошибки)
    """
    if x1 > x2:
        return (False, "Левая граница не может быть больше правой")
    return (True, "")


def check_step(x1: float, x2: float, h: float) -> tuple[bool, str]:
    """
    Проверка шага аргумента.

    Возвращает (True, "") если всё в порядке,
    иначе (False, текст ошибки)
    """
    if h <= 0:
        return (False, "Шаг должен быть положительным")
    if h > x2 - x1:
        return (False, "Шаг не может превышать длину диапазона")
    return (True, "")


def check_accuracy(e: float) -> tuple[bool, str]:
    """
    Проверка точности.

    Возвращает (True, "") если всё в порядке,
    иначе (False, текст ошибки)
    """
    if e <= 0:
        return (False, "Точность должна быть больше 0")
    if e >= 1:
        return (False, "Точность должна быть меньше 1")
    return (True, "")


def get_right_digits(e: float, h: float) -> int:
    """
    Подсчёт количества цифр после запятой для вывода.
    Выбираем наименьшее среди h и e, считаем его знаки.

    Возвращает число цифр после запятой (не меньше 6)
    """
    prec = min(e, h)

    right = 1
    while prec > 0:
        prec *= 10
        right += 1
        prec -= int(prec)

    if right < 6:
        right = 6
    return right


def make_rows(x1: float, x2: float, h: float, e: float) -> list[dict]:
    """
    Формирование строк результата: x, y (ряд), cbrt(x).

    Возвращает список словарей с полями:
    "x" - аргумент,
    "y" - значение ряда (None, если не сходится),
    "root" - кубический корень
    """
    rows = []
    x = x1
    while x <= x2 + h / 2:
        y = taylor(x, e)
        rows.append({
            "x": x,
            "y": y,
            "root": math.cbrt(x),
        })
        x += h
    return rows