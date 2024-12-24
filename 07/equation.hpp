#ifndef EQUATION_HPP
# define EQUATION_HPP

// Custom class: equation
#include <string>
#include <vector>
class	equation
{
	public:
		// Constructor
		equation	(	std::string	);

		// Destructor
		~equation	(void);

		void	solve(int);

		long	result = -1;
		std::vector<int>	numbers;
		bool solveable = false;
		int size;
		int posibilities;
		int posibilities_b;

};

int	inverseDecimalByBinary(int, int);
#endif

