#include "../colors.h"
#include "equation.hpp"
#include <fstream>
#include <stdexcept>
#include <string>
using namespace std;

int	part1(string file = "input", int n = 2)
{
	std::ifstream input;
	input.open(file);
	if (!input.is_open())
		return (1);
	string str;
	long long result = 0;
	while (getline(input, str))
	{
		equation eq(str);
		try{
			eq.solve(n);
		}
		catch (out_of_range &e)
		{
			cout << YELLOW << e.what() << endl;
			continue;
		}
		if (eq.solveable)
		{
			cout << GREEN;
			result += eq.result;
		}
		else
		{
			cout << RED;
			cout << str << RESET << endl;
		}

	}
	cout << result << endl;
	return (0);
}

int main(int argc, char **argv)
{
	if (argc == 3)
		part1(argv[1], stoi(argv[2]));
	else
		part1();
	return (0);
}

