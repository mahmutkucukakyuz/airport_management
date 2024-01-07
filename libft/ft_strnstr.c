#include "libft.h"
#include "stdio.h"

char	*ft_strnstr(char *str, char *find, size_t len)
{
	size_t	hayint;
	size_t	needint;

	hayint = 0;
	if (*find == 0)
		return ((char *)str);
	while (str[hayint] != 0 && hayint < len)
	{
		needint = 0;
		while (str[hayint + needint] == find[needint]
			&& find[needint] != 0 && needint + hayint < len)
			needint++;
		if (!find[needint])
			return ((char *)&str[hayint]);
		hayint++;
	}
	return (NULL);
}
