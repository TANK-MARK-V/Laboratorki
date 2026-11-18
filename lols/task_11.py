from task_11_tables import *


def get_start_values() -> tuple:
    "Получить стартовые значения для тестов"
    # ДеньНедели
    days = [WeekDay("Понедельник"), WeekDay("Вторник"), WeekDay("Среда"),
            WeekDay("Четверг"), WeekDay("Пятница"), WeekDay("Суббота")]
    # Пара
    times = [
       Time(1, "8:15", "9:45"),
       Time(2, "9:55", "11:25"),
       Time(3, "11:35", "13:05"),
       Time(4, "13:35", "15:05"),
       Time(5, "15:15", "16:45"),
       Time(6, "17:05", "18:35"),
       Time(7, "18:45", "20:15")
    ]
    # Дисциплина
    lessons = [
        # Понедельник (day_id=1)
        Lesson("Линейная алгебра", 0, 0),
        Lesson("Дискретная математика", 0, 1),
        Lesson("Высшая математика", 0, 2),
        Lesson("Математический анализ", 0, 3),
        Lesson("Дифференицальные уравнения", 0, 4),
        # Вторник (day_id=2)
        Lesson("Химия", 1, 0),
        Lesson("Биология", 1, 1),
        Lesson("Английский язык", 1, 2),
        Lesson("Физкультура", 1, 3),
        Lesson("Обществознание", 1, 4),
        # Среда (day_id=3)
        Lesson("Алгебра", 2, 0),
        Lesson("Геометрия", 2, 1),
        Lesson("Физика", 2, 2),
        Lesson("Русский язык", 2, 3),
        Lesson("Программирование", 2, 4),
        # Четверг (day_id=4)
        Lesson("Базы данных", 3, 0),
        Lesson("Web-технологии", 3, 1),
        Lesson("Компьютерные сети", 3, 2),
        Lesson("Алгоритмы", 3, 3),
        Lesson("Дискретная математика-2", 3, 4),
        # Пятница (day_id=5)
        Lesson("Теоретические Основы Информатики", 4, 0),
        Lesson("Основы Программной Инжерении", 4, 1),
        Lesson("ООП", 4, 2),
        Lesson("Основы Электроники", 4, 3),
        Lesson("Основы Интернет Технологий", 4, 4),
        # Суббота (day_id=6)
        Lesson("Иностранный язык", 5, 0),
        Lesson("Деловой английский", 5, 1),
        Lesson("Риторика", 5, 2),
        Lesson("Этика", 5, 3),
        Lesson("Эстетика",5, 4)
    ]
    return (days, lessons, times)


def make_task_db(start_values: bool = True) -> dict:
    """
    Создание структуры для хранения таблицы
    start_values: нужно ли добавить начальные значения в таблицу
    """
    data = {
        "ДеньНедели": [],
        "Дисциплина": [],
        "Пара": []
        }
    
    if start_values:
        values = get_start_values()
        data["ДеньНедели"] = values[0]
        data["Дисциплина"] = values[1]
        data["Пара"] = values[2]
    
    return data


ACTIONS = [  # Возможные действия пользователя
    "Выход из программы",
    "Добавить данные в таблицу",
    "Изменить данные в таблицы",
    "Удалить данные из таблицы",
    "Вывести данные на экран",
    "Вывести результаты запроса",
    "Записать данные в .csv файл",
    "Загрузить данные из .csv файла",
]
SPACE = [0, 3, 5]  # Отступы для удобства пользователя


def action_1(data_base: dict):  # Добавить данные в таблицу
    names = list(TABLES.keys())
    print("\nВ какую таблицу нужно добавить запись:")
    for i in range(len(names)):
        print(f"{i} - {names[i]}")
    need_table = input()

    if need_table not in ('0', '1', '2'):
        print("Неверный ввод")
        return
    
    need_table = names[int(need_table)]
    print(f"Введите данные в виде {';'.join(TABLES[need_table][1:])}")
    try:
        add_row(data_base, need_table, input().split(';'))
    except Exception:
        print("Неверный ввод")
    else:
        print(f"Данные успешно добавлены в таблицу {need_table}")


def action_2(data_base: dict):  # Изменение данных в таблице
    names = list(TABLES.keys())
    print("\nВ какой таблице нужно изменить данные:")
    for i in range(len(names)):
        print(f"{i} - {names[i]}")
    need_table = input()

    if need_table not in ('0', '1', '2'):
        print("Неверный ввод")
        return

    need_table = names[int(need_table)]
    print(f"Введите номер нужной записи (< {len(data_base[need_table])})")
    ind = input()
    if not ind.isnumeric() or (ind := int(ind)) >= len(data_base[need_table]):
        print("Неверный ввод")
        return
    
    print(f"Введите данные в виде {';'.join(TABLES[need_table][1:])}")
    try:
        result = edit_row(data_base, need_table, ind, input().split(';'))
    except Exception:
        print("Неверный ввод")
    else:
        print(result[1])


def action_3(data_base: dict):  # Удалить данные из таблицы
    names = list(TABLES.keys())
    print("\nВ какой таблице нужно удалить данные:")
    for i in range(len(names)):
        print(f"{i} - {names[i]}")
    need_table = input()

    if need_table not in ('0', '1', '2'):
        print("Неверный ввод")
        return

    need_table = names[int(need_table)]
    print(f"Введите номер нужной записи (< {len(data_base[need_table])})")
    ind = input()
    if not ind.isnumeric() or (ind := int(ind)) >= len(data_base[need_table]):
        print("Неверный ввод")
        return
    
    result = can_safe_delete(data_base, need_table, ind)
    if not result[0]:
        print("Удаление данной записи затронет другие данные")
        print("Вы уверены, что хотите удалить её? (д/н)")
        answer = input()
    else:
        answer = 'д'
    if answer == 'д':
        result = delete_row(data_base, need_table, ind)
        print(result[0])
    else:
        print("Удаление отменено")


def action_4(data_base: dict):  # Вывести данные на экран
    names = list(TABLES.keys())
    print("\nКакую таблицу нужно вывести:")
    print("0 - всю базу данных целиком")
    for i in range(len(names)):
        print(f"{i + 1} - {names[i]}")
    need_table = input()

    match need_table:
        case '0' | '':
            for key in names:
                table_print(data_base, key)
                print("\n")
        case '1' | '2' | '3':
            table_print(data_base, names[int(need_table) - 1])
        case _: print("Неверный ввод")


def action_5(data_base: dict):  # Вывести результаты запроса
    print("\nДоступен запрос:")
    print('"' + "Для каждого дня недели: сколько всего пар предусмотрено в этот день." + '"')
    days = data_base["ДеньНедели"]
    for i in range(len(days)):   
        day_lessons = list(filter(lambda x: x.week_day_id == i, data_base["Дисциплина"]))
        print(f"\nВ день недели {i} ~ {days[i].name} предусмотрено {len(day_lessons)} пар:")
        for lesson in day_lessons:
            print('\t' + str(lesson))
        


def action_6(data_base: dict):  # Записать данные в .csv файл
    names = list(TABLES.keys())
    print("\nКакую таблицу нужно записать в .csv файл:")
    print("0 - всю базу данных целиком")
    for i in range(len(names)):
        print(f"{i + 1} - {names[i]}")
    need_table = input()

    match need_table:
        case '0' | '':
            print(1)
            for key in names:
                write_table(data_base, key)
            print("Успешно!")
        case '1' | '2' | '3':
            print(2)
            write_table(data_base, names[int(need_table) - 1])
            print("Успешно!")
        case _: print("Неверный ввод")


def action_7(data_base: dict):  # Загрузить данные из .csv файла
    names = list(TABLES.keys())
    print("\nКакую таблицу нужно загрузить из .csv файла:")
    print("0 - всю базу данных целиком")
    for i in range(len(names)):
        print(f"{i + 1} - {names[i]}")
    need_table = input()

    match need_table:
        case '0' | '':
            for key in names:
                data_base[key] = read_file(data_base, key)
            print("Успешно!")
        case '1' | '2' | '3':
            table = names[int(need_table) - 1]
            data_base[table] = read_file(data_base, table)
            print("Успешно!")
        case _: print("Неверный ввод")


def task_11_main():
    print("Программа 11:")
    print("Программа работы с базой данных")
    print("\"Расписание группы\"")
    print("Таблицы:")
    names = list(TABLES.keys())
    for name in names:
        print(f"\t\"{name}\"")
    print("Хотите ли вы заполнить таблицу")
    print("начальными занчениями (д/н)?")
    data_base = make_task_db(start_values=(input() == 'д'))
    print("\nБаза данных успешно создана!")

    to_run = True
    while to_run:
        print("\n\nВыберите действие:")
        for i in range(len(ACTIONS)):
            print(f"{i} - {ACTIONS[i]}")
            if i in SPACE:
                print("-" * 40)
        num = input()
        match num:
            case '0': to_run = False; break  # Выход из программы
            case '1': action_1(data_base)  # Добавить данные в таблицу
            case '2': action_2(data_base)  # Изменение данных в таблице
            case '3': action_3(data_base)  # Удалить данные из таблицы
            case '4': action_4(data_base)  # Вывести данные на экран
            case '5': action_5(data_base)  # Вывести результаты запроса
            case '6': action_6(data_base)  # Записать данные в .csv файл
            case '7': action_7(data_base)  # Загрузить данные из .csv файла
            case _: print("Неверный ввод")


if __name__ == "__main__":
    task_11_main()