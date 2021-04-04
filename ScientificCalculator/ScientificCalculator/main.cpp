#include <iostream>
#include <vector>
#include <string>
#include "ScientificCalculator.h"
#include "ScientificCalculator.cpp"

void introduction();
bool detectDecimal(std::string line);
bool checkLegal(std::string line);

int main(void)
{
#if(1)
	introduction();
	std::string line;
	std::cout << "Input:\t";
	std::getline(std::cin, line);
	//line.insert(0, "0+");

	while (checkLegal(line)) {
		if (detectDecimal(line)) {
			std::vector<StringNumber<double>> numbers;
			StringNumber<double> stringNumber;

			stringNumber.DetectNumber(numbers, line);

			//stringNumber.text(numbers);

			stringNumber.SolveBrac(numbers, 0, numbers.size());
			stringNumber.ThirdLevelCal(numbers, 0, numbers.size());
			stringNumber.SecondLevelCal(numbers, 0, numbers.size());
			stringNumber.FirstLevelCal(numbers, 0, numbers.size());
		
			//stringNumber.text(numbers);

			std::cout << numbers;
		}
		else {
			std::vector<StringNumber<int>> numbers;
			StringNumber<int> stringNumber;

			stringNumber.DetectNumber(numbers, line);

			//stringNumber.text(numbers);

			stringNumber.SolveBrac(numbers, 0, numbers.size());
			stringNumber.ThirdLevelCal(numbers, 0, numbers.size());
			stringNumber.SecondLevelCal(numbers, 0, numbers.size());
			stringNumber.FirstLevelCal(numbers, 0, numbers.size());

			//stringNumber.text(numbers);

			std::cout << numbers;
		}
		std::cout << "Input:\t";
		std::getline(std::cin, line);
		//line.insert(0, "0+");
	}

	return 0;
#endif

#if(0)
	std::string line;
	std::cout << "Input:\t";
	std::getline(std::cin, line);
	std::vector<StringNumber<double>> numbers;
	StringNumber<double> stringNumber;

	stringNumber.DetectNumber(numbers, line);

	stringNumber.text(numbers);
	stringNumber.ThirdLevelCal(numbers, 0, numbers.size());
	stringNumber.text(numbers);

	return 0;

#endif
}

void introduction()
{
	std::cout << "This is a scientific calculator achieved by c++. Coder: DouSBao." << std::endl;
	std::cout << "Current functions: add \"+\", mins \"-\", mul \"*\", div \"/\", bra \"(\" and \")\", power \"^\" " << std::endl;
	std::cout << "Note: Input the calculated string in an single line.\n" << std::endl;
}

bool detectDecimal(std::string line)
{
	bool isDeciaml = false;

	for (int i = 0; i < (int)line.size(); i++) {
		if (line[i] == '.') {
			isDeciaml = true;
		}
	}

	return isDeciaml;
}

bool checkLegal(std::string line)
{
	bool isLegal = true;
	bool hasBra = false;
	int key = 0;

	for (int i = 0; i < (int)line.size(); i++) {
		if (line[i] != ' ' && line[i] != '.' && line[i] != '+' && line[i] != '-' && line[i] != '*' && line[i] != '/' && line[i] != '(' && line[i] != ')' && line[i] != 'R' && !(line[i] - '0' >= 0 && line[i] - '0' <= 9) && line[i] != '^') {
			isLegal = false;
			std::cout << "Illegal input!!!" << std::endl;
			break;
		}
		else if (line[i] == '(' || line[i] == ')') {
			hasBra = true;
		}
	}

	if (hasBra) {
		for (int i = 0; i < (int)line.size(); i++) {
			bool hasFound = false;
			if (line[i] == '(') {
				static int j = i + 1;
				if (key == 0) {
					j = i + 1;
					key++;
				}
				for ( ; j < (int)line.size(); j++) {
					if (line[j] == ')') {
						hasFound = true;
						j++;
						break;
					}
				}
				if (hasFound == false) {
					isLegal = false;
					std::cout << "Illegal input!!!" << std::endl;
					break;
				}
			}
		}
	}

	for (int i = 0; i < (int)line.size(); i++) {
		if (line[i] == '(') {
			for (int j = i - 1; j >= 0; j--) {
				if (!(line[j] - '0' >= 0 && line[j] - '0' <= 9) && line[j] != ' ') {
					break;
				}
				else if (line[j] - '0' >= 0 && line[j] - '0' <= 9) {
					isLegal = false;
					std::cout << "Illegal input!!!" << std::endl;
					break;
				}
			}
		}
		else if (line[i] == ')') {
			for (int j = i + 1; j < (int)line.size(); j++) {
				if (!(line[j] - '0' >= 0 && line[j] - '0' <= 9) && line[j] != ' ') {
					break;
				}
				else if (line[j] - '0' >= 0 && line[j] - '0' <= 9) {
					isLegal = false;
					std::cout << "Illegal input!!!" << std::endl;
					break;
				}
			}
		}
	}

	for (int i = 0; i < line.size(); i++) {
		if (line[i] == '^') {
			for (int j = i - 1; j >= 0; j--) {
				if (line[j] - '0' >= 0 && line[j] - '0' <= 9) {
					goto end;
				}
				else if (!(line[j] - '0' >= 0 && line[j] - '0' <= 9) && line[j] != ' ' && line[j] != ')') {
					isLegal = false;
					std::cout << "Illegal input!!!" << std::endl;
					break;
				}
			}
		}
	}
end:

	return isLegal;
}