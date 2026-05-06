#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>  // Стандартный вход/выход
#include <locale.h>  // Вывод на русском языке
#include <conio.h>  // Задержка экрана

#include <string.h>  // Работа со строками
#include <math.h>  // Математические функции

#include <stdlib.h>  // Создание динамических массивов, использования рандома и преобразования строк
#include <windows.h>  // Очистка консоли и установка кодировки
#include <time.h>    // Для обновления рандома


#define SETIO SetConsoleCP(1251); SetConsoleOutputCP(1251);  // Ввод и вывод на русском
#define UTF SetConsoleCP(65001); SetConsoleOutputCP(65001);  // Ввод и вывод на русском

#define FRUIT_NAME_LEN 10


// Класс корзины с фруктами
class FruitsBasket {
	// Атрибуты по условию задания
	char name[FRUIT_NAME_LEN];	// Название фруктов
	char color;					// Цвет фруктов
	int ccal_of_one;			// Калорийность каждого фрукта
	// Атрибут, добавленный для реализации функций
	int num;					// Количество фруктов в корзине

public:
	// Установить название фруктов name
	int set_name(const char *new_name);
	// Установить цвет фруктов color
	int set_color(char new_color);
	// Установить калорийность каждого фрукта ccal_of_one
	int set_ccal_of_one(int new_ccal_of_one);
	// Установить количество фруктов в корзине num
	int set_num(int new_num);

	// Получить название фруктов name
	char *get_name();
	// Получить цвет фруктов color
	char get_color();
	// Получить калорийность каждого фрукта ccal_of_one
	int get_ccal_of_one();
	// Получить количество фруктов в корзине num
	int get_num();

	// Печать объекта
	void print();

	// Конструктор без параметров
	FruitsBasket();
	// Конструктор с параметрами
	FruitsBasket(const char *name, char color, int ccal_of_one, int num);
	// Конструктор копирования
	FruitsBasket(const FruitsBasket &basket);
	// Деструктор
	~FruitsBasket();

	// Подсчитать общую калорийность фруктов
	int count_full_ccal();
	// Положить фрукт в корзину
	int put_one();
	// Взять фрукт из корзины
	int take_one();
	// Сравнить две корзины
	int compare_baskets(const FruitsBasket& basket);
};
// Установить название фруктов name
int FruitsBasket::set_name(const char *new_name) {
	if (strlen(new_name) > FRUIT_NAME_LEN - 1)
		return 0;
	strcpy(name, new_name);
	return 1;
}
// Установить цвет фруктов color
int FruitsBasket::set_color(char new_color) {
	if (new_color != 'к' &&		// Не красный
		new_color != 'ж' &&		// Не жёлтый
		new_color != 'о' &&		// Не оранжевый
		new_color != 'з' &&		// Не зелёный
		new_color != 'р' &&		// Не розовый
		new_color != 'ф')		// Не фиолетовый
		return 0;
	color = new_color;
	return 1;
}
// Установить калорийность каждого фрукта ccal_of_one
int FruitsBasket::set_ccal_of_one(int new_ccal_of_one) {
	if (new_ccal_of_one <= 0)
		return 0;
	ccal_of_one = new_ccal_of_one;
	return 1;
}
// Установить количество фруктов в корзине num
int FruitsBasket::set_num(int new_num) {
	if (new_num < 0)
		return 0;
	num = new_num;
	return 1;
}

// Получить название фруктов name
char* FruitsBasket::get_name() {
	return name;
}
// Получить цвет фруктов color
char FruitsBasket::get_color() {
	return color;
}
// Получить калорийность каждого фрукта ccal_of_one
int FruitsBasket::get_ccal_of_one() {
	return ccal_of_one;
}
// Получить количество фруктов в корзине num
int FruitsBasket::get_num() {
	return num;
}

// Печать объекта
void FruitsBasket::print() {
	const char *full_color;
		 if (color == 'к') full_color = "красный";
	else if (color == 'ж') full_color = "жёлтый";
	else if (color == 'о') full_color = "оранжевый";
	else if (color == 'з') full_color = "зелёный";
	else if (color == 'р') full_color = "розовый";
	else if (color == 'ф') full_color = "фиолетовый";
	else full_color = "прозрачный";
	printf("Корзина \"%s\": %s цвет, в одном %d кКал., всего %d шт.\n",
					name, full_color, ccal_of_one, num);
}

// Конструктор без параметров
FruitsBasket::FruitsBasket() {
	strcpy(name, "*пусто*");
	color = 0;
	ccal_of_one = 0;
	num = 0;
	printf("Создана пустая корзина для фруктов\n");
}
// Конструктор с параметрами
FruitsBasket::FruitsBasket(const char *name, char color, int ccal_of_one, int num) {
	strcpy(this->name, name);
	this->color = color;
	this->ccal_of_one = ccal_of_one;
	this->num = num;
	printf("Создана корзина с фруктами:\n");
	print();
}
// Конструктор копирования
FruitsBasket::FruitsBasket(const FruitsBasket& basket) {
	strcpy(this->name, basket.name);
	this->color = basket.color;
	this->ccal_of_one = basket.ccal_of_one;
	this->num = basket.num;
	printf("Создана корзина с фруктами по подобию другой:\n");
	print();
}
// Деструктор
FruitsBasket::~FruitsBasket() {
	printf("Корзина с фруктами удалена\n");
}

// Подсчитать общую калорийность фруктов
int FruitsBasket::count_full_ccal() {
	return ccal_of_one * num;
}
// Подсчитать общую калорийность фруктов
// Положить фрукт в корзину
int FruitsBasket::put_one() {
	return ++num;
}
// Взять фрукт из корзины
int FruitsBasket::take_one() {
	if (num == 0)
		return 0;
	return --num;
}
// Сравнить две корзины
int FruitsBasket::compare_baskets(const FruitsBasket& basket) {
	if (!strcmp(this->name, basket.name) &&
		this->color == basket.color &&
		this->ccal_of_one == basket.ccal_of_one)
		return 1;  // Если всё совпадает, возвращаем 1
	return 0;
}

int main() {
	SETIO;
	printf("Создаём разные корзинки:\n");
	FruitsBasket first;
	FruitsBasket second("яблоко", 'к', 50, 5);
	FruitsBasket third(second);

	printf("\nРаботаем с корзиной second:\n");
	second.print();

	printf("\nПоменяем данные на 3 апельсина по 12 кКал.:\n");
	second.set_name("апельсин");
	second.set_color('о');
	second.set_ccal_of_one(12);
	second.set_num(3);
	second.print();

	printf("\nПроверим получение данных через get:\n");
	printf("second.name = %s\n", second.get_name());
	printf("second.color = %c\n", second.get_color());
	printf("second.ccal_of_one = %d\n", second.get_ccal_of_one());
	printf("second.num = %d\n", second.get_num());

	printf("\nПроверим методы, которые просят по заданию:\n");
	printf("Общая калорийность фруктов = %d\n", second.count_full_ccal());
	printf("Положили фрукт в корзину, теперь там %d апельсинов\n", second.put_one());
	printf("Взяли фрукт из корзины, теперь там %d апельсинов\n", second.take_one());
	printf("second == third >> %d\n", second.compare_baskets(third));
	printf("second == second >> %d\n", second.compare_baskets(second));
	printf("\nНажмите любую кнопку, чтобы продолжить");
	_getch();
	return 0;
}