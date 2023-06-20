#include <include/SysCalculator.hpp>
#include <rapidjson/document.h>
#include <iostream>
#include <locale>
#include <Windows.h>

int main(int argc, char* argv[]) {
	std::locale::global(std::locale(""));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	SysCalculator a;
	rapidjson::Document document;
	if (argc < 3) {
		std::wcout << L"Введите в параметры командной строки директории к файлам для чтениия и записи данных!";
		return 0;
	}
	std::string inputs = argv[1];
	std::string outputs = argv[2];
	std::string expr;
	int64_t sys;
	std::ifstream datajson;
	double temp;
	for (int count = 1; count < 6; count++) {
		datajson.open(inputs + "/" + std::to_string(count) + ".json");
		a.openFile(outputs + "/" + std::to_string(count) + ".txt");
		if (a.File_is_open() && datajson.is_open()) {
			std::string jsonString((std::istreambuf_iterator<char>(datajson)), std::istreambuf_iterator<char>());
			document.Parse(jsonString.c_str());
			if (document.HasMember("expression") && document["expression"].IsString()) {
				expr = document["expression"].GetString();
				a.setExample(expr);
			}
			if (document.HasMember("system") && document["system"].IsInt()) {
				sys = static_cast<int64_t>(document["system"].GetInt());
				a.setSystem(sys);
			}
			temp = a.Value();
			expr = a.ToSystem(temp);
		}
		datajson.close();
		a.closeFile();
	}
}
