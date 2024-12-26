#include "../colors.h"
#include <fstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include "grid.hpp"
using namespace std;


void	instatiateMap(string file, grid<char> &map)
{
	std::ifstream input;
	input.open(file);
	if (!input.is_open())
		throw runtime_error("file didnt open");
	string str;
	vector<string> lines;
	while (getline(input, str))
		lines.push_back(str);
	int maxY = lines.size();
	int maxX = lines[0].size();
	for (int y = 0; y < maxY; ++y)
		for (int x = 0; x < maxX; ++x)
			map.at(y, x) = lines[y][x];
}

void	part1singleSolve(grid<char> & map, grid<bool> & sol, pair<int, int> c)
{
	const char s = map.at(c);	
}

void	part1solve(grid<char> & map, grid<bool> & sol)
{
	for (int y = 0; y < map.getSizeY(); y++)
		for (int x = 0; x < map.getSizeX(); x++)
			if (map.at(y, x) != '.')
				part1singleSolve(map, sol, {y, x});
}

int	part1(string file = "input", int n = 2)
{
	grid<char> map(50, 50);
	grid<bool> sol(50, 50);
	instatiateMap(file, map);
	part1solve(map,sol);

	return (0);
}
int	main(void)
{
	part1();
	return (0);
}
