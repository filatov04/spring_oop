#include <include/SysCalculator.hpp>
#include <iostream>

std::ostream& operator<<(std::ostream& ostr, const SysCalculator& rhs) {
	return rhs.WriteTo(ostr);
}

std::ostream& SysCalculator::WriteTo(std::ostream& ostr) const noexcept {
	for (int32_t i = 0; i < num.size(); i++) {
		ostr << num[i];
	}
	return ostr;
}

void SysCalculator::LaTex_preamble() {
	if (output.is_open()) {
		output << "\\documentclass[a4paper, 9pt]{article}" << std::endl;
		output << "\\usepackage{amsmath}" << std::endl;
		output << "\\usepackage[document]{ragged2e}" << std::endl;
		output << "\\usepackage[utf8x]{inputenc}" << std::endl;
		output << "\\usepackage[russian]{babel}" << std::endl;
		output << "\\usepackage{mathtools}" << std::endl;
		output << "\\begin{document}" << std::endl;
	}
	else {
		std::cout << "Mistake";
	}
}

void SysCalculator::LaTeX_SysCalculator() {
	if (output.is_open()) {
		output << "\\normalsize 1) \\begin{normalsize}\\(";
		for (int32_t i = 0; i < num.size(); i++) {
			if (num[i + 1] == '{') {
				output << num[i] << "_";
			}
			else if (num[i] == ' ' && isdigit(num[i + 1]) && isdigit(num[i - 1])) {
				output << "\\;";
			}
			else {
				output << num[i];
			}
		}
		output << " = " << "?_{" << system << "}" << "\\)" << " \\end{normalsize}" << std::endl;
		output << "\\\\" << std::endl;
		output << "\\normalsize Схема перевода чисел в десятичную систему счисления:" << std::endl << "\\\\" << std::endl;
	}
	else {
		std::cout << "Mistake";
	}
}


void SysCalculator::setExample(std::string& temp_num) {
	if (Format_check(temp_num) == false) {
		std::cout << "Нарушен формат входных данных, проверьте введенный пример!";
		throw std::invalid_argument("Incorrect format");
	}
	else {
		num = temp_num;
	}
}

void SysCalculator::openFile(const std::string& filename) {
	output.open(filename);
}

void SysCalculator::closeFile() {
	if (output.is_open()) {
		output.close();
	}
}

bool SysCalculator::File_is_open() {
	if (!output.is_open()) {
		return false;
	}
	else {
		return true;
	}
}

int64_t SysCalculator::getSystem() {
	if (system <= 0) throw std::invalid_argument("System can not be less zero or equal zero");
	return system;
}

void SysCalculator::setSystem(int64_t& s) {
	LaTex_preamble();
	system = s;
	LaTeX_SysCalculator();
}

std::string SysCalculator::ToSystem(double& value) {
	std::string number_values = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int64_t divisible = 1; // делимое
	std::vector<int64_t> number;
	bool negative = 0;
	if (value < 0) {
		value = -value;
		negative = 1;
	}
	std::string str = std::to_string(value);
	str.erase(str.find_last_not_of('0') + 1, std::string::npos);
	str.erase(str.find_last_not_of('.') + 1, std::string::npos);
	output << "\\normalsize Схема перевода числа " << str << " из десятичной системы счисления в " << system << "-ричную:" << "\n";
	output << "\\[" << "\n" << "\\begin{array}{c|c}" << "\n" << "\\text{Десятичное число } & \\text{Остаток от деления} \\\\" << "\n";
	int64_t ivalue = (int64_t)value;
	while (ivalue / system != 0) {
		divisible = ivalue % system;
		std::string str = std::to_string(ivalue);
		output << str << " \\div " << system << " & " << divisible << " \\\\" << "\n";
		number.push_back(divisible);
		ivalue /= system;
	}
	output << " & " << ivalue << " \\\\" << "\n";
	number.push_back(ivalue);
	std::string answer;
	for (int32_t i = 0; i < number.size(); i++) {
		if (number[number.size() - 1 - i] > (int64_t)number_values.size()) {
			answer.append(std::to_string(number[number.size() - 1 - i]));
			answer.insert(answer.size() - 1, " ");
			continue;
		}
		for (int64_t j = 0; j < system; j++) {
			if (j == number[number.size() - 1 - i]) {
				answer.push_back(number_values[j]);
				break;
			}
		}
	}
	if (fmod(value, 1) != 0) {
		answer.append(".");
		double decimal_part = fmod(value, 1);
		std::vector<int> decimal_answer;
		for (int32_t i = 0; i < 10; i++) {
			decimal_part *= system;
			decimal_answer.push_back((int)decimal_part);
			decimal_part = decimal_part - (int)decimal_part;
		}
		for (int32_t i = 0; i < decimal_answer.size(); i++) {
			if (decimal_answer[i] > number_values.size()) {
				answer.append(std::to_string(decimal_answer[i]));
				answer.insert(answer.size() - 1, " ");
				continue;
			}
			for (int64_t j = 0; j < system; j++) {
				if (j == decimal_answer[i]) {
					answer.push_back(number_values[j]);
					break;
				}
			}
		}
	}
	output << "\\end{array}" << "\n" << "\\]" << "\n" << "\\\\" << "\n" << "\\normalsize Правильный ответ:" << "\n" << "\\\\" << "\n";
	output << "\\(";
	for (int32_t i = 0; i < num.size(); i++) {
		if (num[i + 1] == '{') {
			output << num[i] << "_";
		}
		else if (num[i] == ' ' && isdigit(num[i + 1]) && isdigit(num[i - 1])) {
			output << "\\;";
		}
		else {
			output << num[i];
		}
	}
	output << " = ";
	if (negative == 1) {
		answer.erase(answer.find_last_not_of('0') + 1, std::string::npos);
		answer.erase(answer.find_last_not_of('.') + 1, std::string::npos);
		output << "-" << answer << "_{" << system << "}" << "\\)\n" << "\\vspace{5mm}\n" << "\\hline\n" << "\\end{document}";
		return answer.insert(0, "-");
	}
	else {
		answer.erase(answer.find_last_not_of('0') + 1, std::string::npos);
		answer.erase(answer.find_last_not_of('.') + 1, std::string::npos);
		output << answer << "_{" << system << "}" << "\\)\n" << "\\vspace{5mm}\n" << "\\hline\n" << "\\end{document}";
		return answer;
	}
}

bool SysCalculator::Format_check(std::string temp_string) {
	const std::string number_values = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const std::string incorrect_values = { "!@#$%^&~`'<>:[],;" };
	int32_t i = 0;
	while (i < temp_string.size()) {
		if (temp_string[i] == ' ') {
			i++;
			continue;
		}
		if (temp_string[i] == '.' && (temp_string[i + 1] >= '0' && temp_string[i + 1] <= '9') && ((int)temp_string[i + 1] >= 65 && (int)temp_string[i + 1] <= 90) && (temp_string[i - 1] == ' ' || temp_string[i] == '-' || temp_string[i] == '+' || temp_string[i] == '*' || temp_string[i] == '/')) {
			return false;
		}
		if (temp_string[i] == '@' || temp_string[i] == '!' || temp_string[i] == '#' || temp_string[i] == '$' || temp_string[i] == '%' || temp_string[i] == '^' || temp_string[i] == '&' ||
			temp_string[i] == ',' || temp_string[i] == '>' || temp_string[i] == '<' || temp_string[i] == '?' || temp_string[i] == ';' || temp_string[i] == ':' || temp_string[i] == '"' ||
			temp_string[i] == '№' || temp_string[i] == '~' || temp_string[i] == '`' || temp_string[i] == '[' || temp_string[i] == ']') {
			return false;
		}
		if ((temp_string[i] >= '0' && temp_string[i] <= '9') || ((int)temp_string[i] >= 65 && (int)temp_string[i] <= 90)) {
			int32_t j = i;
			while (1) {
				if (temp_string[j] == '{' && temp_string[j + 3] != '}' && temp_string[j + 2] != '}') {
					return false;
				}
				if (temp_string[j] == '@' || temp_string[j] == '!' || temp_string[j] == '#' || temp_string[j] == '$' || temp_string[j] == '%' || temp_string[j] == '^' || temp_string[j] == '&' ||
					temp_string[j] == ',' || temp_string[j] == '>' || temp_string[j] == '<' || temp_string[j] == '?' || temp_string[j] == ';' || temp_string[j] == ':' || temp_string[j] == '"' ||
					temp_string[j] == '№' || temp_string[j] == '~' || temp_string[j] == '`' || temp_string[j] == '[' || temp_string[j] == ']') {
					return false;
				}
				if ((int)temp_string[j] >= 113 && (int)temp_string[j] <= 122) {
					return false;
				}
				if (temp_string[j] == '}') {
					break;
				}
				j++;
			}
			std::string temp = temp_string.substr(i, j - i + 1); // функция получает подстроку
			int32_t temp_system = Find_System(temp);
			for (int32_t k = 0; k < temp.find("{"); k++) {
				if (IsRussian(temp[k]) == true) {
					return false;
				}
				if (isdigit(temp[k]) && temp[k + 1] == ' ' && isdigit(temp[k + 2])) {
					std::string s = temp.substr(k, 3);
					IsSpace(s);
					int32_t two_digits = std::stoi(s);
					if (two_digits < temp_system) {
						k += 2;
						continue;
					}
					else {
						return false;
					}
				}
				for (int32_t l = 0; l < number_values.size(); l++) {
					if (number_values[l] == temp[k]) {
						if (l > temp_system) {
							return false;
						}
					}
				}

			}
			i = j;
			i++;
			continue;
		}
		if (temp_string[i] == '-' || temp_string[i] == '+' || temp_string[i] == '*' || temp_string[i] == '/' || temp_string[i] == '(' || temp_string[i] == ')') {
			i++;
			continue;
		}
		else {
			return false;
		}
	}
	return true;
}

bool SysCalculator::IsRussian(char& symbol) {
	std::string russian{ "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ" };
	for (int32_t i = 0; i < russian.size(); i++) {
		if (symbol == russian[i]) {
			return true;
		}
	}
	return false;
}

void SysCalculator::IsSpace(std::string& s) {
	s.erase(std::remove_if(s.begin(), s.end(), std::isspace), s.end());
}

double SysCalculator::ToDecimal(std::string s) {
	output << "\\begin{normalsize} \\(";
	std::string number_values = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::string staples{ "{}" };
	std::string a = s.substr(s.find_first_of(staples) + 1, s.find_last_of(staples) - s.find_first_of(staples) - 1);
	int32_t this_system = std::stoi(a);
	double res = 0;
	if (s.find(" ") == std::string::npos) {
		if (this_system != 10) {
			for (int32_t i = 0; i < s.size(); i++) {
				if (s[i + 1] == '{') {
					output << s[i] << "_";
				}
				else if (s[i] == ' ' && isdigit(s[i + 1]) && isdigit(s[i - 1])) {
					output << "\\;";
				}
				else {
					output << s[i];
				}
			}
			output << " = ";
			if (s.find(".") == std::string::npos) {
				for (int32_t i = 0; i < s.find("{"); i++) {
					if (i >= 1) {
						output << " + ";
					}
					for (int32_t j = 0; j < number_values.size(); j++) {
						if (number_values[j] == s[i]) {
							output << j << " * " << this_system << "^" << s.find("{") - 1 - i;
							res += j * pow(this_system, s.find("{") - 1 - i);
							break;
						}
					}
				}
				std::string str = std::to_string(res);
				str.erase(str.find_last_not_of('0') + 1, std::string::npos);
				str.erase(str.find_last_not_of('.') + 1, std::string::npos);
				output << " = " << str << "_{10}\\) \\end{normalsize}" << std::endl << "\\\\" << std::endl;
				return res;
			}
			else {
				int32_t count = static_cast<int32_t>(s.find(".") - 1);
				for (int32_t i = 0; i < s.find("{"); i++) {
					if (s[i] == '.') {
						continue;
					}
					if (i >= 1) {
						output << " + ";
					}
					for (int32_t j = 0; j < number_values.size(); j++) {
						if (number_values[j] == s[i]) {
							if (count < 0) {
								output << j << " * " << this_system << "^" << "{" << count << "}";
							}
							else {
								output << j << " * " << this_system << "^" << count;
							}
							res += j * pow(this_system, count);
							count--;
							break;
						}

					}
				}
				std::string str = std::to_string(res);
				str.erase(str.find_last_not_of('0') + 1, std::string::npos);
				str.erase(str.find_last_not_of('.') + 1, std::string::npos);
				output << " = " << str << "_{10}\\) \\end{normalsize}" << std::endl << "\\\\" << std::endl;
				return res;
			}
		}
		else {
			for (int32_t i = 0; i < 2; i++) {
				if (i >= 1) {
					output << " = ";
				}
				for (int32_t j = 0; j < s.size(); j++) {
					if (s[j + 1] == '{') {
						output << s[j] << "_";
					}
					else if (s[j] == ' ' && isdigit(s[j + 1]) && isdigit(s[j - 1])) {
						output << "\\;";
					}
					else {
						output << s[j];
					}
				}
			}
			output << "\\) " << "\\end{normalsize}" << std::endl << "\\\\" << std::endl;
			return std::stod(s.substr(0, s.find("{")));
		}
	}
	else {
		if (s.find(".") != std::string::npos) {
			int32_t count = (int32_t)s.find(".") - 2;
			if (this_system != 10) {
				for (int32_t i = 0; i < s.size(); i++) {
					if (s[i + 1] == '{') {
						output << s[i] << "_";
					}
					else if (s[i] == ' ' && isdigit(s[i + 1]) && isdigit(s[i - 1])) {
						output << "\\;";
					}
					else {
						output << s[i];
					}
				}
				output << " = ";
				for (int32_t i = 0; i < s.find("{"); i++) {
					if (isdigit(s[i]) && s[i + 1] == ' ' && isdigit(s[i + 2])) {
						std::string temp = s.substr(i, 3);
						IsSpace(temp);
						int32_t two_digits = std::stoi(temp);
						output << " + ";
						if (count < 0) {
							output << two_digits << " * " << this_system << "^" << "{" << count << "}";
						}
						else {
							output << two_digits << " * " << this_system << "^" << count;
						}
						res += two_digits * pow(this_system, count);
						i += 2;
						count--;
						continue;
					}
					if (s[i] == '.') {
						continue;
					}
					if (i >= 1) {
						output << " + ";
					}
					for (int32_t j = 0; j < number_values.size(); j++) {
						if (number_values[j] == s[i]) {
							if (count < 0) {
								output << j << " * " << this_system << "^" << "{" << count << "}";
							}
							else {
								output << j << " * " << this_system << "^" << count;
							}
							res += j * pow(this_system, count);
							count--;
							break;
						}
					}
				}
				std::string str = std::to_string(res);
				str.erase(str.find_last_not_of('0') + 1, std::string::npos);
				str.erase(str.find_last_not_of('.') + 1, std::string::npos);
				output << " = " << str << "_{10}\\) \\end{normalsize}" << std::endl << "\\\\" << std::endl;
				return res;
			}
			else {
				for (int32_t i = 0; i < 2; i++) {
					if (i >= 1) {
						output << " = ";
					}
					for (int32_t j = 0; j < s.size(); j++) {
						if (s[j + 1] == '{') {
							output << s[j] << "_";
						}
						else if (s[j] == ' ' && isdigit(s[j + 1]) && isdigit(s[j - 1])) {
							output << "\\;";
						}
						else {
							output << s[j];
						}
					}
				}
				output << "\\) " << "\\end{normalsize}" << std::endl << "\\\\" << std::endl;
				return std::stod(s.substr(0, s.find("{")));
			}
		}
		else {
			int32_t k = (int32_t)s.find("{") - 3;
			if (this_system != 10) {
				for (int32_t i = 0; i < s.size(); i++) {
					if (s[i + 1] == '{') {
						output << s[i] << "_";
					}
					else if (s[i] == ' ' && isdigit(s[i + 1]) && isdigit(s[i - 1])) {
						output << "\\;";
					}
					else {
						output << s[i];
					}
				}
				output << " = ";
				for (int32_t i = 0; i < s.find("{"); i++) {
					if (isdigit(s[i]) && s[i + 1] == ' ' && isdigit(s[i + 2])) {
						std::string temp = s.substr(i, 3);
						IsSpace(temp);
						int32_t two_digits = std::stoi(temp);
						output << " + ";
						output << two_digits << " * " << this_system << "^" << k;
						res += two_digits * pow(this_system, k);
						i += 2;
						k--;
						continue;
					}
					if (i >= 1) {
						output << " + ";
					}
					for (int32_t j = 0; j < number_values.size(); j++) {
						if (number_values[j] == s[i]) {
							output << j << " * " << this_system << "^" << k;
							res += j * pow(this_system, k);
							k--;
							break;
						}
					}
				}
				std::string str = std::to_string(res);
				str.erase(str.find_last_not_of('0') + 1, std::string::npos);
				str.erase(str.find_last_not_of('.') + 1, std::string::npos);
				output << " = " << str << "_{10}\\) \\end{normalsize}" << std::endl << "\\\\" << std::endl;
				return res;
			}
			else {
				for (int32_t i = 0; i < 2; i++) {
					if (i >= 1) {
						output << " = ";
					}
					for (int32_t j = 0; j < s.size(); j++) {
						if (s[j + 1] == '{') {
							output << s[j] << "_";
						}
						else if (s[j] == ' ' && isdigit(s[j + 1]) && isdigit(s[j - 1])) {
							output << "\\;";
						}
						else {
							output << s[j];
						}
					}
				}
				output << "\\) " << "\\end{normalsize}" << std::endl << "\\\\" << std::endl;
				return std::stod(s.substr(0, s.find("{")));
			}
		}
	}
}

int32_t SysCalculator::Find_System(std::string s) {
	std::string staples{ "{}" };
	std::string a = s.substr(s.find_first_of(staples) + 1, s.find_last_of(staples) - s.find_first_of(staples) - 1);
	return std::stoi(a);
}

int getRang(char temp) {
	if (temp == '+' || temp == '-') {
		return 1;
	}
	if (temp == '*' || temp == '/') {
		return 2;
	}
	else {
		return 0;
	}
}

bool Maths(std::stack <Leksema>& Stack_N, std::stack <Leksema>& Stack_O, Leksema& Item) {
	double b = 0, a = Stack_N.top().value;
	Stack_N.pop();
	switch (Stack_O.top().type)
	{
	case '+':
		b = Stack_N.top().value;
		Stack_N.pop();
		Item.value = a + b;
		Item.type = '0';
		Stack_N.push(Item);
		Stack_O.pop();
		break;
	case '-':
		b = Stack_N.top().value;
		Stack_N.pop();
		Item.value = b - a;
		Item.type = '0';
		Stack_N.push(Item);
		Stack_O.pop();
		break;
	case '*':
		b = Stack_N.top().value;
		Stack_N.pop();
		Item.value = a * b;
		Item.type = '0';
		Stack_N.push(Item);
		Stack_O.pop();
		break;
	case '/':
		if (a == 0) {
			std::cout << "На ноль делить нельзя, попробуйте ввести пример заново" << std::endl;
			return 0;
		}
		b = Stack_N.top().value;
		Stack_N.pop();
		Item.value = b / a;
		Item.type = '0';
		Stack_N.push(Item);
		Stack_O.pop();
		break;
	default:
		std::cout << "Mistake\n";
		return false;
		break;
	}
	return true;
}

double SysCalculator::Value() {
	std::stack <Leksema> Stack_n;
	std::stack <Leksema> Stack_o;
	Leksema item = { 0,'+' };
	for (int32_t i = 0; i < num.size(); i++) {
		if (num[i] == ' ') {
			continue;
		}
		if (i == 0 && num[i] == '-') {
			item.type = 0;
			item.value = -ToDecimal(num.substr(i + 1, num.find("}")));
			Stack_n.push(item);
			i = static_cast<int32_t>(num.find("}"));
			continue;
		}
		if ((num[i] >= '0' && num[i] <= '9') || ((int)num[i] >= 65 && (int)num[i] <= 90)) {
			int32_t j = i;
			while (1) {
				if (num[j] == '}') {
					break;
				}
				j++;
			}
			item.type = 0;
			item.value = ToDecimal(num.substr(i, j - i + 1));
			Stack_n.push(item);
			i = j;
			continue;
		}
		if (num[i] == '+' || num[i] == '-' || num[i] == '*' || num[i] == '/') {
			if (Stack_o.size() != 0 && getRang(num[i]) <= getRang(Stack_o.top().type)) {
				if (Maths(Stack_n, Stack_o, item) == false) {
					std::system("Pause");
					return 0;
				}
				item.type = num[i];
				item.value = 0;
				Stack_o.push(item);
				continue;
			}
			if (Stack_o.size() != 0 && getRang(num[i]) > getRang(Stack_o.top().type)) {
				item.type = num[i];
				item.value = 0;
				Stack_o.push(item);
				continue;
			}
			if (Stack_o.size() == 0) {
				item.type = num[i];
				item.value = 0;
				Stack_o.push(item);
				continue;
			}
		}
		if (num[i] == '(') {
			if (num[i + 1] == '-') {
				item.type = 0;
				item.value = -ToDecimal(num.substr(i + 2, num.find("}", i + 2) - i - 1));
				Stack_n.push(item);
				i = static_cast<int32_t>(num.find(")", i + 2));
				continue;
			}
			else {
				item.type = num[i];
				item.value = 0;
				Stack_o.push(item);
				continue;
			}
		}
		if (num[i] == ')') {
			while (Stack_o.top().type != '(') {
				if (Maths(Stack_n, Stack_o, item) == false) {
					std::system("Pause");
					return 0;
				}
				else continue;
			}
			Stack_o.pop();
			continue;
		}
	}
	while (Stack_o.size() != 0) {
		if (Maths(Stack_n, Stack_o, item) == false) {
			std::system("Pause");
			return 0;
		}
		else continue;
	}
	return Stack_n.top().value;
}
