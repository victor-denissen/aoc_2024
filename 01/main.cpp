#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
int	part1(void)
{
	std::ifstream input;
	input.open("input");
	if (!input.is_open())
		return (1);

	std::string str;
	std::list<int> left;
	std::list<int> right;
	while (getline(input, str))
	{
		std::cout << "Original:\t" << str << std::endl;
		std::string left_str = str.substr(0, str.find(' '));
		std::cout << "Mine:\t\t" << left_str << " ";
		left.push_back(std::stoi(left_str.c_str()));
		std::string right_Str = str.substr(str.find_last_of(' ') + 1, std::string::npos);
		std::cout << right_Str << std::endl << std::endl;
		right.push_back(std::stoi(right_Str.c_str()));
	}
	left.sort();
	right.sort();


	int result = 0;

	std::list<int>::iterator it_left = left.begin();
	std::list<int>::iterator it_right = right.begin();

	while (it_left != left.end() && it_right != right.end())
	{
		result += abs(*it_left - *it_right);
		it_right++;
		it_left++;
	}
	std::cout << "result: " << result << std::endl;
	return (0);
}


void	part2(void)
{
	std::ifstream input;
	input.open("input");
	if (!input.is_open())
		return ;
	
	std::string str;
	std::list<int> left;
	std::list<int> right;
	while (getline(input, str))
	{
		std::string left_str = str.substr(0, str.find(' '));
		left.push_back(std::stoi(left_str.c_str()));
		std::string right_Str = str.substr(str.find_last_of(' ') + 1, std::string::npos);
		right.push_back(std::stoi(right_Str.c_str()));
	}
	left.sort();
	right.sort();


	int result = 0;

	for (std::list<int>::iterator it_left = left.begin(); it_left != left.end(); it_left++)
	{
		int score = 0;
		for (std::list<int>::iterator it_right = right.begin(); it_right != right.end(); it_right++)
		{
			if (*it_left == *it_right)
				score++;
		}
		result += score * *it_left;

	}
	std::cout << "result: " << result << std::endl;
}

int main(void)
{
	part1();
	part2();
}
