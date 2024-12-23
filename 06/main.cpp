#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include "../colors.h"
using namespace std;
char ** readFile(int * size, string file)
{
	ifstream input;
	input.open(file);
	if (!input.is_open())
		return NULL;
	vector<string> vec_result{istream_iterator<string>(input), 
                                    istream_iterator<string>()};
	input.close();
	*size = vec_result.size();	
	char ** result = (char **)calloc(*size + 1, sizeof(char *));
	if (!result)
		return NULL;
	int i = 0;
	for (string str : vec_result)
	{
		result[i] = strdup(str.c_str());
		if (!result[i]) {
			while (i >= 0)
				free(result[i--]);
			free(result);
			return NULL;
		}
		i++;
	}
	result[*size] = NULL;
	return (result);
}

void	findGuard(char ** map, pair<int, int> & coords, int size)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < strlen(map[i]); j++)
			if (map[i][j] == '^')
				coords = {i,j};
}

int	moveGuard(char ** map, pair<int, int> & coords, int size)
{
	pair<int, int> move;
	switch (map[coords.first][coords.second])
	{
		case '>':
			move = {0, 1};
			break;
		case '<':
			move = {0, -1};
			break;
		case '^':
			move = {-1, 0};
			break;
		case 'v':
			move = {1, 0};
			break;
		default:
			throw runtime_error("what is my guard");
	}
	pair<int, int> newCoords = {coords.first + move.first, coords.second + move.second};
	if (		newCoords.second == strlen(map[newCoords.second]) ||	// Guard moves of right side 
			newCoords.second < 0 ||					// Guard moves of left side
			newCoords.first == size ||				// Guard moves of bottom side
			newCoords.first < 0)					// Guard moves of top side
	{
		map[coords.first][coords.second] = 'X'; // Mark map for final time
		return 1;
	}
	if (map[newCoords.first][newCoords.second] == '#') // Update the guards direction
	{
		if (map[coords.first][coords.second] == '^')
			map[coords.first][coords.second] = '>';
		else if (map[coords.first][coords.second] == '>')
			map[coords.first][coords.second] = 'v';
		else if (map[coords.first][coords.second] == 'v')
			map[coords.first][coords.second] = '<';
		else if (map[coords.first][coords.second] == '<')
			map[coords.first][coords.second] = '^';
	}
	else
	{
		map[newCoords.first][newCoords.second] = map[coords.first][coords.second]; // update guard pos
		map[coords.first][coords.second] = 'X'; // Mark map
		coords = newCoords;
	}
	return (0);
}

void	printMap(char ** map, int size)
{
	for (int i = 0; i < size; i ++)
	{
		for (int j = 0; j < strlen(map[i]); j++)
		{
			cout << RED;
			if (map[i][j] == 'X')
				cout << GREEN;
			if (map[i][j] == '.')
				cout << BLACK;
			if (map[i][j] == '#')
				cout << YELLOW;
			cout << map[i][j] << RESET;
		}
		cout << endl;
	}
	cout << RESET << endl;
}

void	part1(string file = "input")
{
	int size;
	int result = 0;
	char ** map = readFile(&size, file);
	if (!map)
		return ;
	pair<int, int> coords(-1, -1);
	findGuard(map, coords, size);
	if (coords.first == -1)
		return (void(cout << RED << "No guard found" << endl << RESET));
	try {
		while (!moveGuard(map, coords, size))
			// printMap(map, size)
			;
	}
	catch (runtime_error e)
	{
		cout << BRIGHT_RED << e.what() << RESET << endl;
		printMap(map, size);
	}
	for (int i = 0; i < size; i ++)
		for (int j = 0; j < strlen(map[i]); j++)
			if (map[i][j] == 'X')
				result++;
	printMap(map, size);
	cout << BRIGHT_GREEN << result << RESET << endl;
}

int	main(int argc, char **argv)
{
	if (argc == 2)
		part1(argv[1]);
	else
		part1();
	return (0);
}

