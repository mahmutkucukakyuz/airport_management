#include "libft.h"
#include "stdio.h"

void	*ft_memchr(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n-- != 0)
	{
		if ((unsigned char)c == *p)
			return ((void *)p);
		p++;
	}
	return (NULL);
}
