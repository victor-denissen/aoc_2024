#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <utility>
#include <vector>
#include "../colors.h"

using namespace std;

vector<int> splitIntoWords(const string& sentence) {
    vector<int> words;
    istringstream stream(sentence);
    string word;
    
    while (stream >> word) {
        words.push_back(std::stoi(word.c_str()));
    }
    
    return words;
}

int	checkLine(vector<int> & numbers, const vector<pair<int, int>> & pairs, const string & line)
{
	vector<int>::iterator it;
	bool result = false;
	for (it = numbers.begin(); it != numbers.end(); it++)
	{
		int n = *it;
		for (auto p: pairs)
		{
			int second = p.second;
			if (second != n)
				continue ;
			auto copy = it;
			for (; copy != numbers.end(); copy++)
				if (*copy == p.first)
				{
					result = true;
					cout << line << RED << " Failed. Reason: " << p.first << "|" << p.second << RESET << endl;
				}
		}
	}
	return (result);
}

int	insertInstruction(vector<pair<int, int>> & pairs, string line)
{
	if (line.empty())
		return (1);

	regex pattern(R"(([0-9]+)\|([0-9]+))");
	smatch match;
	if (regex_match(line, match, pattern))
	{
		pair<int, int> newPair;
		newPair.first = stoi(match[1].str());
		newPair.second = stoi(match[2].str());
		pairs.push_back(newPair);
	}
	return (0);
}

void	part1(string file = "input")
{
	ifstream input;
	input.open(file);
	if (!input.is_open())
		return ;
	string line;
	int result = 0;
	vector<pair<int, int>> pairs;
	while (getline(input, line))
	{
		if (insertInstruction(pairs, line)) // This indicates that the given line was no longer an instructions
			break;
	}
	while (getline(input, line))
	{
		replace(line.begin(), line.end(), ',', ' ');
		vector<int> numbers = splitIntoWords(line);
		if (!checkLine(numbers, pairs, line))
			result += numbers.at(numbers.size()/2);

	}
	cout << result;
}

void	fixEm(vector<int> & numbers, vector<pair<int, int>> pairs, string & line)
{
again:
	while (checkLine(numbers, pairs, line))
	{
		for (auto it = numbers.begin(); it != numbers.end(); it++)
		{
			int n = *it;
			for (auto p: pairs)
			{
				int second = p.second;
				if (second != n)
					continue ;
				auto copy = it;
				for (; copy != numbers.end(); copy++)
					if (*copy == p.first)
					{
						iter_swap(copy, it);
						goto again;
					}
			}
		}
	}
}

void	part2(string file = "input")
{
	ifstream input;
	input.open(file);
	if (!input.is_open())
		return ;
	string line;
	int result = 0;
	vector<pair<int, int>> pairs;
	while (getline(input, line))
	{
		if (insertInstruction(pairs, line)) // This indicates that the given line was no longer an instructions
			break;
	}
	while (getline(input, line))
	{
		replace(line.begin(), line.end(), ',', ' ');
		vector<int> numbers = splitIntoWords(line);
		if (checkLine(numbers, pairs, line))
		{
			fixEm(numbers, pairs, line);
			result += numbers.at(numbers.size()/2);
		}

	}
	cout << result;
}


int main(int argc, char **argv)
{
	if (argc == 2)
		part2(argv[1]);
	else
		part2();
	return (0);
}
// Read instructions
// How to store a set of instructions
// 	Map ?
