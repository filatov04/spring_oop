#pragma once
#ifndef SYSTEM_CALCULATOR_07062023
#define SYSTEM_CALCULATOR_07062023

#include <iosfwd>
#include <string>
#include <cstdint>
#include <fstream>
#include <stack> 
#include <cstdlib>
#include <vector>
/**
* @brief 
* Описание работы консольного приложения:
* 1. Вводится выражение в формате .json файла, парсится в document класса Document библиотеки rapidJSON
* 2. Из каждой пары ключ-значение выделяются две переменные: арифметическое выражение, система счисления, в которой будет получен ответ 
* 3. С помощью одного из методов проверяется правильность введенного выражения 
* 4. Каждый аргумент переводится в десятичную систему счисления, в которой и происходит вычисление примера.
* Далее число кладется в стек с операндами. Каждая математическая операция кладется в стек с операциями.
* 5. Вычисление значения происходит до того момента пока стек с операциями не будет пуст.
* 6. Полученные данные выводятся в формате кода для LaTEX.
*/
class SysCalculator {
public:
	/*! \brief Конструктор по умолчанию. Используется для присвания закрытым членам класса значения по умолчниаю */
	SysCalculator() = default;
	/*! \brief Сеттер, устанавливающий значение для закрытого члена класса std::string num */
	void setExample(std::string& temp_num);
	/*! \brief Геттер возваращающий значение закрытого члена класса system */
	int64_t getSystem();
	/*! \brief Сеттер, устанавливающий значение для закрытого члена класса int64_t system */
	void setSystem(int64_t& s);
	/*! \brief Открытие файла для записи данных */
	void openFile(const std::string& filename);
	/*! \brief Закрытие файла для записи */
	void closeFile();
	/*! \brief Возвращает true, если файл открыт */
	bool File_is_open();
	/*! \brief Перевод числа из десятичной системы счисления в другую */
	std::string ToSystem(double& value);
	/*! \brief Проверка на наличие пробелов в строке */
	void IsSpace(std::string& s);
	/*! \brief Проверка на формат введенного выражения */
	bool Format_check(std::string temp_string);
	/*! \brief Проверка на наличие символов русского алфавита */
	bool IsRussian(char& symbol);
	/*! \brief Перевод числа в десятичную систему счисления */
	double ToDecimal(std::string s);
	/*! \brief Вычисление значения выражения */
	double Value();
	/*! \brief Определение системы счисления числа*/
	int32_t Find_System(std::string s);
	/*! \brief Вывод ввдененого выражение через оператор << */
	std::ostream& WriteTo(std::ostream& ostr) const noexcept;


private:
	void LaTex_preamble();
	void LaTeX_SysCalculator();
	std::ofstream output;
	std::string num = "001";
	int64_t system = 2;

};
/*! \brief Структура, использующаяся для работы со стеками */
struct Leksema
{
	char type;
	double value;
};

#endif // !SYSTEM_CALCULATOR_07062023
