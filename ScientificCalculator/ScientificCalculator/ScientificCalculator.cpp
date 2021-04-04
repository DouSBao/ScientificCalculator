#include "ScientificCalculator.h"

template <class T>
StringNumber<T>::StringNumber()
{
	number = 0;
	operas.push_back('+');
}

template <class T>
StringNumber<T>::StringNumber(std::string myString, int& index) {
	T number = 0;
	int decimalDigit = 0;
	int negaSignIndex = 0;
	char opera = '0';
	bool isNegative = false;
	bool isDeciamlNow = false;

	for (int i = index; i < (int)myString.size(); i++) {
		int key = myString[i] - '0';
		
		if (key >= 0 && key <= 9) {
			int j;
			for (j = i - 1; j >= 0; j--) {
				if (myString[j] == '-') {
					isNegative = true;
					negaSignIndex = i;
					break;
				}
				else if (myString[j] != ' ') {
					break;
				}
			}

			if (isNegative) {
				for (int k = j - 1; k >= 0; k--) {
					if (myString[k] == '(') {
						break;
					}
					else if (myString[k] == '-') {
						isNegative = ~isNegative;
					}
					else if (negaSignIndex > k && myString[k] - '0' >= 0 && myString[k] - '0' <= 9) {
						isNegative = false;
						break;
					}
				}
			}

			if (isDeciamlNow) {
				decimalDigit++;
			}
			number *= 10;
			number += key;
			index++;
		}
		else if (myString[i] == '.') {
			isDeciamlNow = true;
			index++;
		}
		else if (myString[i] == '+' || myString[i] == '-' || myString[i] == '*' || myString[i] == '/' || myString[i] == '(' || myString[i] == ')'|| myString[i] == 'R' || myString[i] == '^') {
			
			operas.push_back(myString[i]);
			index++;

			bool hasNextLegalOpera = true;
			for (int j = i + 1; j < (int)myString.size(); j++) {
				if (myString[j] == '+' || myString[j] == '-' || myString[j] == '*' || myString[j] == '/' || myString[j] == '(' || myString[j] == ')' || myString[j] == 'R' || myString[j] == '^') {
					break;
				}
				else if (myString[j] - '0' >= 0 && myString[j] - '0' <= 9) {
					hasNextLegalOpera = false;
					break;
				}
			}

			if (!hasNextLegalOpera) {
				index = i + 1;
				break;
			}
		}
		else if (myString[i] == ' ') {
			index++;
		}
		else if (myString[i] != ' ') {
			index = i + 1;
			break;
		}
	}

	if (isNegative) {
		number = 0 - number;
	}
	if (isDeciamlNow) {
		for (int i = 0; i < decimalDigit; i++) {
			number /= 10;
		}
	}

	operas.push_back(opera);
	this->number = number;
}

template <class T>
void StringNumber<T>::DetectNumber(std::vector<StringNumber>& numbers, std::string line)
{
	for (int i = 0; i < (int)line.size(); ) {
		if (line[i] - '0' >= 0 && line[i] - '0' <= 9) {
			numbers.push_back(StringNumber(line, i));
		}
		else {
			i++;
		}
	}
}

template <class T>
void StringNumber<T>::FirstLevelCal(std::vector<StringNumber>& numbers, int startIndex, int endIndex)
{
	for (int i = startIndex; i < endIndex - 1; i++) {
		for (int j = 0; j < (int)numbers[i].operas.size(); j++) {
			if (numbers[i].operas[j] == '+') {
				if (numbers[i].isCount == false) {
					numbers[i].number += numbers[i + 1].number;
					numbers[i + 1].number = 0;
					numbers[i].operas[j] = '0';
					numbers[i + 1].isCount = true;
				}
				else {
					for (int k = i - 1; k >= startIndex; k--) {
						if (numbers[k].isCount == false) {
							numbers[k].number += numbers[i + 1].number;
							numbers[i + 1].number = 0;
							numbers[i].operas[j] = '0';
							numbers[i + 1].isCount = true;
						}
					}
				}
			}
			else if (numbers[i].operas[j] == '-') {
				if (numbers[i].isCount == false) {
					numbers[i].number -= numbers[i + 1].number;
					numbers[i + 1].number = 0;
					numbers[i].operas[j] = '0';
					numbers[i + 1].isCount = true;
				}
				else {
					for (int k = i - 1; k >= startIndex; k--) {
						if (numbers[k].isCount == false) {
							numbers[k].number -= numbers[i + 1].number;
							numbers[i + 1].number = 0;
							numbers[i].operas[j] = '0';
							numbers[i + 1].isCount = true;
						}
					}
				}
			}
		}
	}
}

template <class T>
void StringNumber<T>::SecondLevelCal(std::vector<StringNumber>& numbers, int startIndex, int endIndex)
{
	for (int i = startIndex; i < endIndex - 1; i++) {
		for (int j = 0; j < (int)numbers[i].operas.size(); j++) {
			if (numbers[i].operas[j] == '*') {
				if (numbers[i].isCount == false) {
					numbers[i].number *= numbers[i + 1].number;
					numbers[i + 1].number = 0;
					numbers[i].operas[j] = '0';
					numbers[i + 1].isCount = true;
				}
				else {
					for (int k = i - 1; k >= startIndex; k--) {
						if (numbers[k].isCount == false) {
							numbers[k].number *= numbers[i + 1].number;
							numbers[i + 1].number = 0;
							numbers[i].operas[j] = '0';
							numbers[i + 1].isCount = true;
							break;
						}
					}
				}
			}
			else if (numbers[i].operas[j] == '/') {
				if (numbers[i].isCount == false) {
					numbers[i].number /= numbers[i + 1].number;
					numbers[i + 1].number = 0;
					numbers[i].operas[j] = '0';
					numbers[i + 1].isCount = true;
				}
				else {
					for (int k = i - 1; k >= startIndex; k--) {
						if (numbers[k].isCount == false) {
							numbers[k].number /= numbers[i + 1].number;
							numbers[i + 1].number = 0;
							numbers[i].operas[j] = '0';
							numbers[i + 1].isCount = true;
							break;
						}
					}
				}
			}
		}
	}
}

template <class T>
void StringNumber<T>::ThirdLevelCal(std::vector<StringNumber>& numbers, int startIndex, int endIndex)
{
	bool findPow = false;
	bool braLeft = false;
	for (int i = startIndex; i < endIndex; i++) {
		for (int j = 0; j < (int)numbers[i].operas.size(); j++) {
			
			if (numbers[i].operas[j] == ')' && findPow == false) {
				braLeft = true;
			}
			else if (numbers[i].operas[j] == '^' && braLeft == false) {
				findPow = true;
				if (numbers[i].isCount == false) {
					numbers[i].number = std::pow(numbers[i].number, numbers[i + 1].number);
					numbers[i + 1].number = 0;
					numbers[i].operas[j] = '0';
					numbers[i + 1].isCount = true;
				}
				else {
					for (int k = i - 1; k >= startIndex; k--) {
						
						if (numbers[k].isCount == false) {
							numbers[k].number = std::pow(numbers[k].number, numbers[i + 1].number);
							numbers[i + 1].number = 0;
							numbers[i].operas[j] = '0';
							numbers[i + 1].isCount = true; 
							break;
						}
					}
				}
			}
		}
	}
}

template <class T>
void StringNumber<T>::SolveBrac(std::vector<StringNumber>& numbers, int startIndex, int endIndex)
{
	for (int i = startIndex; i < endIndex; i++) {
		for (int j = 0; j < (int)numbers[i].operas.size(); j++) {
			if (numbers[i].operas[j] == '(') {
				for (int k = i + 1; k < endIndex; k++) {
					for (int m = 0; m < (int)numbers[k].operas.size(); m++) {
						if (numbers[k].operas[m] == '(') {
							SolveBrac(numbers, k, endIndex);
							numbers[i].operas[j] = '0';
							break;
						}
						else if (numbers[k].operas[m] == ')') {
							ThirdLevelCal(numbers, i + 1, k);
							SecondLevelCal(numbers, i + 1, k + 1);
							FirstLevelCal(numbers, i + 1, k + 1);
							numbers[i].operas[j] = '0';
							numbers[k].operas[m] = '0';
							return;
						}
					}
				}
			}
		}
	}
}

template <class T>
void StringNumber<T>::text(std::vector<StringNumber> numbers)
{
	for (int i = 0; i < numbers.size(); i++) {
		std::cout << "No." << i << " StringNumber in the vector has number " << numbers[i].number << " and operator ";

		for (int j = 0; j < numbers[i].operas.size(); j++) {
			std::cout << numbers[i].operas[j] << " ";
		}

		std::cout << std::endl;
	}
}
