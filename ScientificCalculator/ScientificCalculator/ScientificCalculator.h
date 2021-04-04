#ifndef SCIENTIFIC_CALCULATOR_H
#define SCIENTIFIC_CALCULATOR_H

#include <string>
#include <vector>
#include <iostream>
#include <cmath>

template <class T>
class StringNumber {
public:
	StringNumber();
	StringNumber(std::string array, int& index);

	void DetectNumber(std::vector<StringNumber>& numbers, std::string line);
	void FirstLevelCal(std::vector<StringNumber>& numbers, int startIndex, int endIndex);
	void SecondLevelCal(std::vector<StringNumber>& numbers, int startIndex, int endIndex);
	void ThirdLevelCal(std::vector<StringNumber>& numbers, int startIndex, int endIndex);
	void SolveBrac(std::vector<StringNumber>& numbers, int startIndex, int endIndex);
	friend std::ostream& operator << (std::ostream& out, std::vector<StringNumber> numbers)
	{
		out << "result:\t" << numbers[0].number << '\n' << std::endl;
		return out;
	}
	void text(std::vector<StringNumber> numbers);

protected:
	T number;
	std::vector<char> operas;
	bool isCount = false;
};

#endif