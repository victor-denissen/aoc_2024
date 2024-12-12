#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <string.h>
char ** readFile(int * size)
{
	std::ifstream input;
	std::vector<std::string> vec_result;
	input.open("input");
	if (!input.is_open())
		return NULL;
	std::string line;
	while (getline(input, line))
		vec_result.push_back(line);
	input.close();
	*size = vec_result.size();	
	char ** result = (char **)malloc(vec_result.size() + 1);
	if (!result)
		return NULL;
	for (int i = 0; i < vec_result.size(); i++)
	{
		result[i] = strdup(vec_result[i].c_str());
		if (!result[i])
		{
			while (--i > 0)
				free(result[i]);
			free(result);
			return NULL;
		}
	}
	return result;
}

enum type{
	N,
	NE,
	E,
	SE,
	S,
	SW,
	W,
	NW
};

int	check(char **lines, int i, int j, int size)
{
	int dirX[] = {0, 1, 0, -1, 1, 1, -1, -1};
	int dirY[] = {1, 0, -1, 0, 1, -1, 1, -1};


	return (0);
}

void	part1()
{
	int size;
	int result = 0;
	char ** lines = readFile(&size);
	for (int i = 0; i < size; i++)
		for (int j = 0; j < strlen(lines[i]); j++)
			result += check(lines, i, j, size);
	
}

int main(void)
{
	return (0);
}
