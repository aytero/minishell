#include "libft.h"

void	*malloc_ptr(void **ptr, size_t size)
{
	*ptr = malloc(size);
	return (*ptr);
}
