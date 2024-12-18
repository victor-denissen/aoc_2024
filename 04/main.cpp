#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <string.h>
#include <stdlib.h>
char ** readFile(int * size, std::string file)
{
	std::ifstream input;
	input.open(file);
	if (!input.is_open())
		return NULL;
	std::vector<std::string> vec_result{std::istream_iterator<std::string>(input), 
                                    std::istream_iterator<std::string>()};
	input.close();
	*size = vec_result.size();	
	char ** result = (char **)calloc(*size + 1, sizeof(char *));
	if (!result)
		return NULL;
	int i = 0;
	// for (std::string str : vec_result)
	// 	std::cout << str << std::endl;
	for (std::string str : vec_result)
	{
		std::string wow(str);
		std::cout << wow << std::endl;
		result[i] = strdup(str.c_str());
		// result[i] = (char *)calloc(wow.size() + 1);
		if (!result[i]) {
			while (i >= 0)
				free(result[i--]);
			free(result);
			return NULL;
		}
		// strcpy(result[i], wow.c_str());
		i++;
	}
	result[*size] = NULL;
	return (result);
}

int	checkDir(char **lines, int i, int j, int size, int dirX, int dirY)
{
	int start_i = i;
	int start_j = j;
	std::string XMAS("XMAS");
	int x_iter = 0;
	while (lines[i][j] == XMAS[x_iter])
	{
		if (XMAS[x_iter] == 'S')
		{
			std::cout << "XMAS found at y:" << start_i << ", x:" << start_j << std::endl;
			std::cout << "x dir: " << dirX << ", y dir: " << dirY << std::endl << std::endl;
			return 1;
		}
		i += dirY;
		j += dirX;
		if (!lines[i] || i < 0 || j < 0 || j > strlen(lines[i]))
			return (0);
		x_iter++;
	}
	return (0);
}

int	check(char **lines, int i, int j, int size)
{
	int dirX[] = {0, 1, 0, -1, 1, 1, -1, -1};
	int dirY[] = {1, 0, -1, 0, 1, -1, 1, -1};

	int result = 0;
	for (int dirs = 0; dirs < 8; dirs++)
		result += checkDir(lines, i, j, size, dirX[dirs], dirY[dirs]);
	return (result);
}

void	part1(std::string file = "input")
{
	int size;
	int result = 0;
	char ** lines = readFile(&size, file);
	if (!lines)
		return ;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < strlen(lines[i]); j++)
			result += check(lines, i, j, size);
	std::cout << "Result: " << result << std::endl;
}

int	checkCross(char **lines, int i, int j, int size)
{
	if (lines[i][j] != 'A')
		return (0);
	if (i == 0 || j == 0 || i == size - 1 || j >= strlen(lines[i]))
		return (0);
	if (((lines[i - 1][j - 1] == 'M' && lines[i + 1][j + 1] == 'S') || (lines[i - 1][j - 1] == 'S' && lines[i + 1][j + 1] == 'M')) &&
		((lines[i + 1][j - 1] == 'M' && lines[i - 1][j + 1] == 'S') || (lines[i + 1][j - 1] == 'S' && lines[i - 1][j + 1] == 'M')))
	{
		return (1);
	}
	return (0);
}

void	part2(std::string file = "input")
{
	int size;
	int result = 0;
	char ** lines = readFile(&size, file);
	if (!lines)
		return ;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < strlen(lines[i]); j++)
			result += checkCross(lines, i, j, size);
	std::cout << "Result: " << result << std::endl;
}

int main(int argc, char **argv)
{
	if (argc == 2)
		part2(argv[1]);
	else
		part2();
	return (0);
}
