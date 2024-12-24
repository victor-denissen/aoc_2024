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

void	freeArray(char ** map, int size)
{
	for (int i = 0; i < size; i++)
		free(map[i]);
	free(map);
}

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
		if (!result[i]) 
		{
			freeArray(result, i-1);
			return NULL;
		}
		i++;
	}
	result[*size] = NULL;
	return (result);
}

void	findGuard(char ** map, pair<int, int> & coords, int size)
{
	string guards = "<>^v";
	for (int i = 0; i < size; i++)
		for (int j = 0; j < strlen(map[i]); j++)
			if (guards.find(map[i][j]) != string::npos)
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
	if (		
			newCoords.first == size ||				// Guard moves of bottom side
			newCoords.first < 0	||					// Guard moves of top side
			newCoords.second == strlen(map[newCoords.first]) ||	// Guard moves of right side 
			newCoords.second < 0					// Guard moves of left side
			)
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

char **	part1(string file = "input")
{
	int size;
	int result = 0;
	char ** map = readFile(&size, file);
	if (!map)
		return NULL;
	pair<int, int> coords(-1, -1);
	findGuard(map, coords, size);
	if (coords.first == -1)
	{
		return (NULL);
			cout << RED << "No guard found" << endl << RESET;
	}
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
	/* printMap(map, size); */
	cout << BRIGHT_GREEN << result << RESET << endl;
	return map;
}

char **	copyMap(char **map, int size)
{
	char **	copy = (char **)malloc(size * sizeof(char *));
	if (!copy)
		return NULL;
	for (int i = 0; i < size; i++)
	{
		copy[i] = strdup(map[i]);
		if (!copy[i])
		{
			freeArray(copy, i-1);
			return NULL;
		}
	}
	return copy;
}

void	createPosition(int positions[130][130], int size, char ** map, pair<int, int> coords)
{
	positions[coords.first][coords.second] *= map[coords.first][coords.second];
}

bool	checkDuplicatePosition(int check[130][130], char ** map, pair<int, int> coords)
{
	if (check[coords.first][coords.second] % map[coords.first][coords.second] == 0)
		return true;
	return false;
}

int	checkIfLoop(char ** map, int size, pair<int, int> guard)
{
	int	check[130][130];
	for (int i = 0; i < 130; i++)
		for (int j = 0; j < 130; j++)
			check[i][j] = 1;
	createPosition(check, size, map, guard);
	while (!moveGuard(map, guard , size))
	{
		if (checkDuplicatePosition(check, map, guard))
		{
			printMap(map, size);
			return 1;
		}
	createPosition(check, size, map, guard);
	}
	return 0;
}

int	part2solution(char ** map, int size, pair<int,int> guard)
{
	int result = 0;
	pair<int, int> obs(0, 0);
	/* char ** baseCompletion = part1(); */
	char ** copy = copyMap(map, size);
	for (int i = 0; i < size; i++)
	{
		obs.second = 0;
		for (int j = 0; j < strlen(map[i]); j++, obs.second++)
		{
			for (int i = 0; i < 130; i++)
				for (int j = 0; j < 130; j++)
					copy[i][j] = map[i][j];

			if (copy[obs.first][obs.second] == '.')
				copy[obs.first][obs.second] = '#';
			else
			{
				continue ;
			}
			cout << "Testing: " << obs.first << ", " << obs.second << endl;
			result += checkIfLoop(copy, size, guard);
		}
		obs.first++;
	}
	freeArray(copy, size);
	return (result);
}

void	part2(string file = "input")
{
	int size;
	char ** map = readFile(&size, file);
	if (!map)
		return ;
	pair<int, int> guard(-1, -1);
	findGuard(map, guard, size);
	if (guard.first == -1)
		return (void(cout << RED << "No guard found" << endl << RESET));

	cout << BRIGHT_GREEN << part2solution(map, size, guard) << RESET << endl;
}

int	main(int argc, char **argv)
{
	if (argc == 2)
		part2(argv[1]);
	else
		part2();
	return (0);
}

