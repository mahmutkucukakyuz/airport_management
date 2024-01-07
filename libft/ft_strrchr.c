#include "libft.h"
#include "stdio.h"

char	*ft_strrchr(char *s, int c)
{
	int	coun;

	coun = 0;
	while (s[coun])
		coun++;
	while (coun >= 0)
	{
		if (s[coun] == (char)c)
			return ((char *)(s + coun));
		coun--;
	}
	return (NULL);
}
