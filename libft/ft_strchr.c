#include "libft.h"
#include <stdio.h>

char	*ft_strchr(char *s, int c)
{
	return (ft_memchr(s, c, ft_strlen(s) + 1));
}
