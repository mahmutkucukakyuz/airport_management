#include "libft.h"
#include <stdio.h>

char	*ft_strdup(char *s1)
{
	char	*temp;
	size_t	coun;

	coun = 0;
	temp = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (temp == NULL)
		return (NULL);
	while (*s1)
	{
		temp[coun] = *s1;
		s1++;
		coun++;
	}
	temp[coun] = '\0';
	return (temp);
}
