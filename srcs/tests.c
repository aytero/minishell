#include "execute.h"
#include "parser.h"

#define PRINT_PATH 0

void	test_print_path()
{

}

void	test_print(t_vars *vars)
{
	if (PRINT_PATH)
		test_print_path(vars);
}
