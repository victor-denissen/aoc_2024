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

void	part1()
{
	std::ifstream input;
	input.open("input");
	if (!input.is_open())
		return ;
	std::string line;
	int result = 0;
start:
	while (getline(input, line))
	{
		type t = NA;
		int pre = -1;
		std::vector<int> numbers = splitIntoWords(line);
		std::cout << "line:\t" << line << std::endl;
		std::cout << "numb:\t";
		for (int i: numbers)
			std::cout << i << " ";
		std::cout << std::endl;
		for (std::vector<int>::iterator it = numbers.begin(); it != numbers.end(); it++)
		{
			if (pre == -1)
			{
				pre = *it;
				continue;
			}
			if (pre == *it)
				goto start;
			if (t == NA)
			{
				if (*it > pre)
					t = ASCENDING;
				else if (*it < pre)
					t = DESCENDING;
				else
					goto start;
			}
			if (t == ASCENDING)
				if (*it < pre)
					goto start;
			if (t == DESCENDING)
				if (*it > pre)
					goto start;
			if (abs(pre - *it) > 3)
				goto start;
			pre = *it;
		}
		std::cout << "Upping result\n";
		result++;
	}
	std::cout << result;

}

int	main(void)
{
	return (0);
}

