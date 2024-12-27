#include "../colors.h"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include "../../grid/include/grid.hpp"
using namespace std;
#define PART 1

grid<char> *	instatiateMap(string file)
{
	ifstream input;
	input.open(file);
	if (!input.is_open())
		throw runtime_error("file didnt open");
	string str;
	vector<string> lines;
	while (getline(input, str))
		lines.push_back(str);
	int maxY = lines.size();
	int maxX = lines[0].size();
	grid<char> * map = new grid<char>(lines.size(), lines[0].size());
	for (int y = 0; y < maxY; ++y)
		for (int x = 0; x < maxX; ++x)
			map->at(y, x) = lines[y][x];
	return map;
}

const	pair<int, int>	subtract(pair<int, int> thit, pair<int, int> that)
{
	return {thit.first - that.first, thit.second - that.second};
}
const	pair<int, int>	add(pair<int, int> thit, pair<int, int> that)
{
	return {thit.first + that.first, thit.second + that.second};
}

void	insertSol(grid<bool> & sol, const pair<int, int> c1, const pair<int, int> c2)
{
	bool part2 = true;
	auto dir = subtract(c1, c2);
	auto a1 = subtract(c1, dir);
	auto a2 = add(c2, dir);
	try
	{
		while (part2){
		cout << "Trying to place antinode at ";
		cout << a1.first << ":" << a1.second << endl;
		sol.at(a1) = '#';
		cout << GREEN << "Successfull" << endl;
		cout << a1.first << ":" << a1.second << endl;
		a1 = subtract(a1, dir);
		}
	}
	catch(out_of_range & e)
	{
		cout << YELLOW << "Couldn't place antinode at" << endl;
		cout << a1.first << ":" << a1.second << endl;
	}
	cout << RESET << endl;
	try{
		while (part2){
		cout << "Trying to place antinode at ";
		cout << a2.first << ":" << a2.second << endl;
		sol.at(a2) = '#';
		cout << GREEN << "Successfull" << endl;
		cout << a2.first << ":" << a2.second << endl;
		a2 = add(a2, dir);
		}
	}
	catch(out_of_range & e)
	{
		cout << YELLOW << "Couldn't place antinode at" << endl;
		cout << a2.first << ":" << a2.second << endl;
	}
	cout << RESET << endl;
}

void	part1singleSolve(grid<char> & map, grid<bool> & sol, grid<char>::iterator & it)
{
	pair<int, int> c = it.getCoords();
	const char s = map.at(c);
	for (grid<char>::iterator iter = it; iter != map.end(); ++iter)
	{
		if (iter == it)
			continue ;
		if (*iter == s)
			insertSol(sol, c, iter.getCoords());
	}
}

void	prettyPrintGrid(grid<char> & map, pair<int, int> coords)
{
	for (auto it = map.begin(); it != map.end(); ++it)
	{
		if (it.getCoords() == coords)
			cout << BRIGHT_GREEN;
		cout << *it << RESET;
		if (it.getCoords().second == map.getSizeX() - 1)
			cout << endl;
	}
}
void	part1solve(grid<char> & map, grid<bool> & sol)
{
	for (auto it = map.begin(); it != map.end(); it++)
		if (*it != '.')
		{
			int x = it.getCoords().second;
			int y = it.getCoords().first;
			cout << BRIGHT_CYAN << "-------------------" << RESET << endl;
			// cout << "Solving for: " << y << ":" << x << endl;
			prettyPrintGrid(map, {y, x});
			part1singleSolve(map, sol, it);
			// cout << BRIGHT_CYAN << "-------------------" << RESET << endl;
		}
}

int	part1(string file = "input")
{
	grid<char> * map = instatiateMap(file);
	grid<bool> sol(map->getSizeY(), map->getSizeX());
	part1solve(*map,sol);
	cout << sol;
	cout << BRIGHT_GREEN << count(sol.begin(), sol.end(), true) << endl << RESET;
	delete map;
	return (0);
}
int	main(int argc, char **argv)
{
	if (argc == 2)
		part1(argv[1]);
	else
		part1();
	return (0);
}
