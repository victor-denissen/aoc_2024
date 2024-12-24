#include "equation.hpp"
#include <cmath>
#include <iostream>
#include <regex>
#include <string>

using namespace std;
// Constructor
equation::equation(string line)
{
	regex pattern(R"([0-9]+)");

	sregex_iterator begin(line.begin(), line.end(), pattern);
	sregex_iterator end;

	for (auto it = begin; it != end; ++it)
	{
		long i = stol((*it).str());
		if (result == -1)
			result = i;
		else
			numbers.push_back(i);
	}
	size = numbers.size();
	posibilities = 2 << (size - 2 > 0? size - 2 : 0);
	posibilities_b = pow(3.0, static_cast<double>(size -1));
}

// Destructor
equation::~equation(void)
{

}

void	equation::solve(int n)
{
	int tries = 0;

	for (int i = 0, j = 0; i < (n == 2 ? posibilities : posibilities_b); i++, j = 0, tries++)
	{
		int copy = tries;
		long long current_result = numbers[0];
		while (++j < size)
		{
			if (copy % n == 0)
				current_result *= numbers[j];
			else if (copy % n == 1)
				current_result += numbers[j];
			else
				current_result = stoll(to_string(current_result).append(to_string(numbers[j])));
			copy /= n;
		}
		if (current_result == result)
		{
			solveable = true;
		}
	}
}
int	inverseDecimalByBinary(int nToChange, int size)
{
	int result = 0;;
	int maxBinary = 2 << size;

	for (;maxBinary > 0; maxBinary /= 2, nToChange /= 2)
		if (nToChange % 2 == 1)
			result += maxBinary;
	return result;
}
