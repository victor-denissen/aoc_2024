#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

std::vector<int> splitIntoWords(const std::string& sentence) {
    std::vector<int> words;
    std::istringstream stream(sentence);
    std::string word;
    
    while (stream >> word) {
        words.push_back(std::stoi(word.c_str()));
    }
    
    return words;
}

enum	type
{
	ASCENDING,
	DESCENDING,
	NA
};


int checkSafe(std::vector<int> numbers)
{
	type t = NA;
	int pre = -1;
	for (std::vector<int>::iterator it = numbers.begin(); it != numbers.end(); it++)
	{
		if (pre == -1)
		{
			pre = *it;
			continue;
		}
		if (pre == *it)
			return 0;
		if (t == NA)
		{
			if (*it > pre)
				t = ASCENDING;
			else if (*it < pre)
				t = DESCENDING;
			else
				return 0;
		}
		if (t == ASCENDING)
			if (*it < pre)
				return 0;
		if (t == DESCENDING)
			if (*it > pre)
				return 0;
		if (abs(pre - *it) > 3)
			return 0;
		pre = *it;
	}
	return (1);
}

void	part1()
{
	std::ifstream input;
	input.open("input");
	if (!input.is_open())
		return ;
	std::string line;
	int result = 0;
	while (getline(input, line))
	{
		std::vector<int> numbers = splitIntoWords(line);
		result += checkSafe(numbers);
	}
	std::cout << result;
}

int	checkSafe2(std::vector<int> numbers)
{
	if (checkSafe(numbers))
		return 1;
	for (int i = 0; i < numbers.size(); i++)
	{
		std::vector<int> copy(numbers);
		copy.erase(copy.begin() + i);
		if (checkSafe(copy))
			return (1);
	}
	return 0;
}

void	part2()
{
	std::ifstream input;
	input.open("input");
	if (!input.is_open())
		return ;
	std::string line;
	int result = 0;
	while (getline(input, line))
	{
		std::vector<int> numbers = splitIntoWords(line);
		result += checkSafe2(numbers);
	}
	std::cout << result;

}

int	main(void)
{
	// part1();
	part2();
	return (0);
}

