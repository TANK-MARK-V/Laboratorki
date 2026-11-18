from flask import Flask, render_template, request, redirect, url_for
import taylor_calculations as calc
import taylor_tables as tables

app = Flask(__name__)

# Возможные действия пользователя (по аналогии с task_11.py)
ACTIONS = [
    "Выход из программы",
    "Выполнить расчёт",
    "Показать справку",
]

SPACE = [0]  # Отступы для удобства пользователя


def get_default_form() -> dict:
    """
    Получить стартовые значения для формы.
    """
    return {
        "x1": "0.5",
        "x2": "1.5",
        "h": "0.1",
        "e": "0.0001",
    }


def action_calculate(form: dict) -> dict:
    """
    Действие "Выполнить расчёт".

    form: данные формы (строки)

    Возвращает словарь с результатом и/или ошибкой
    """
    try:
        x1 = float(form.get("x1", ""))
        x2 = float(form.get("x2", ""))
        h = float(form.get("h", ""))
        e = float(form.get("e", ""))
    except (TypeError, ValueError):
        return {"error": "Неверный ввод: все поля должны быть числами"}

    checks = [
        calc.check_bounds(x1, x2),
        calc.check_step(x1, x2, h),
        calc.check_accuracy(e),
    ]
    for ok, message in checks:
        if not ok:
            return {"error": message}

    right = calc.get_right_digits(e, h)
    rows = calc.make_rows(x1, x2, h, e)

    return {
        "error": "",
        "rows": rows,
        "right": right,
        "form": {"x1": x1, "x2": x2, "h": h, "e": e},
    }


@app.route("/", methods=["GET", "POST"])
def index():
    """
    Главная страница: форма ввода и таблица результатов.
    """
    form_data = get_default_form()
    result = None

    if request.method == "POST":
        action = request.form.get("action", "1")
        form_data = {key: request.form.get(key, "") for key in ("x1", "x2", "h", "e")}

        match action:
            case "0":  # Выход из программы
                return redirect(url_for("index"))
            case "1":  # Выполнить расчёт
                result = action_calculate(form_data)
            case "2":  # Показать справку
                result = {"info": (
                    "Функция раскладывается в ряд Тейлора относительно x = 1. "
                    "Рекомендуется x1 > 0 и x2 < 2. "
                    "Точность e должна лежать в интервале (0, 1). "
                    "Если ряд расходится, вместо y выводится прочерк."
                )}
            case _:
                result = {"error": "Неверный ввод"}

    return render_template(
        "index.html",
        actions=ACTIONS,
        space=SPACE,
        form=form_data,
        result=result,
        table_headers=tables.TABLES["Результаты"],
    )


if __name__ == "__main__":
    app.run(debug=True)