#ifndef COLORS_H
#define COLORS_H

#include <iostream>
#include <string>

// ANSI escape codes for colors
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLD    "\033[1m"       /* Bold */

#define	ULINE	"\033[4m"


// Brighter versions
#define BRIGHT_BLACK   "\033[30;1m"      /* Bright Black */
#define BRIGHT_RED     "\033[31;1m"      /* Bright Red */
#define BRIGHT_GREEN   "\033[32;1m"      /* Bright Green */
#define BRIGHT_YELLOW  "\033[33;1m"      /* Bright Yellow */
#define BRIGHT_BLUE    "\033[34;1m"      /* Bright Blue */
#define BRIGHT_MAGENTA "\033[35;1m"      /* Bright Magenta */
#define BRIGHT_CYAN    "\033[36;1m"      /* Bright Cyan */
#define BRIGHT_WHITE   "\033[37;1m"      /* Bright White */

#ifndef PRINT_TEST
#define PRINT_TEST
void	print_test(std::string test)
{
	std::cout << std::endl << BRIGHT_BLUE << ULINE << "TEST:\t" << test << RESET << std::endl;
}
#endif


#endif // COLORS_H

