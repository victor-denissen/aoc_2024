#include <cstdio>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>


int	multiply(std::string str)
{
	return (0);
}

void	part1()
{
	int result = 0;

	std::regex pattern(R"(mul\(([0-9]+),([0-9]+)\))");

	std::ifstream input;
	input.open("input");
	if (!input.is_open())
		return ;
	std::string line;
	while (getline(input, line))
	{
		std::sregex_iterator begin(line.begin(), line.end(), pattern);
		std::sregex_iterator end;
		for (std::sregex_iterator i = begin; i != end; i++)
		{
			std::smatch match = *i;
			std::string str = match[0];
			std::cout << str << std::endl;
			int num1 = std::stoi(match[1].str());;
			int num2 = std::stoi(match[2].str());
			std::cout << "num1: " << num1 << ",\tnum2: " << num2 << std::endl << std::endl;
			result += num1 * num2;
		}
	}
	std::cout << "result: " << result << std::endl;
	input.close();
}

int	main(void)
{
	part1();
	return (0);
}

