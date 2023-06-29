#include <include/SysCalculator.hpp>
#include <rapidjson/document.h>
#include <iostream>
#include <filesystem>
#include <Windows.h>

int main(int argc, char* argv[]) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	SysCalculator a;
	rapidjson::Document document;
	if (argc < 3) {
		std::cout << "������� � ��������� ��������� ������ ���������� � ������ ��� ������� � ������ ������!";
		return 0;
	}
	std::string inputs = argv[1];
	std::string outputs = argv[2];
	if (outputs != "out" && inputs != "config") {
		std::cout << "����������� ������� ��������� ��������� ������, ���������� ������ � �������� ������� ��������� \"config\" � \"out\" � �������� ������� (��� �������)";
		return 0;
	}
	if (inputs != "config") {
		std::cout << "����������� ������ ������ �������� ��������� ������ ��� ������ ������ �� �����, ���������� ������ \"config\" (��� �������) ������ " << inputs;
		return 0;
	}
	if (outputs != "out") {
		std::cout << "����������� ������ ������ �������� ��������� ������ ��� ������ ������ � ����, ���������� ������ \"out\" (��� �������) ������ " << outputs;
		return 0;
	}
	const std::string folderPath = inputs;
	int fileCount = 0;
	for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
		if (std::filesystem::is_regular_file(entry)) {
			fileCount++;
		}
	}
	std::string expr;
	int64_t sys;
	std::ifstream datajson;
	double temp;
	for (int count = 1; count <= fileCount; count++) {
		datajson.open(inputs + "/" + std::to_string(count) + ".json");
		a.openFile(outputs + "/" + std::to_string(count) + ".txt");
		if (a.File_is_open() && datajson.is_open()) {
			std::string jsonString((std::istreambuf_iterator<char>(datajson)), std::istreambuf_iterator<char>());
			document.Parse(jsonString.c_str());
			if (document.HasMember("expression") && document["expression"].IsString()) {
				expr = document["expression"].GetString();
				if (a.Format_check(expr) == false) {
					std::cout << "����������� ������� ������ ������� ������, ��������� ��������� � ���������� �����\n";
					throw std::invalid_argument("Incorrect format");
				}
				else {
					a.setExample(expr);
				}
				if (expr == "" || expr == " ") {
					std::cout << "��������� " << count << ".json ����, � ����� \"expression\" �� �������� ������ ��������\n";
					datajson.close();
					a.closeFile();
					continue;
				}
			}
			if (document.HasMember("system") && document["system"].IsInt()) {
				sys = static_cast<int64_t>(document["system"].GetInt());
				if (sys <= 0) {
					std::cout << "�������� ������� ��������� �� ����� ���� ������ ��� ����� 0\n";
					throw std::invalid_argument("System can not be less zero or equal zero");
				}
				else {
					a.setSystem(sys);
				}
			}
			temp = a.Value();
			expr = a.ToSystem(temp);
		}
		datajson.close();
		a.closeFile();
	}
}
