#include "libft.h"
#include <stdio.h>

int	ft_atoi(char *str)
{
	long	coun;
	long	np;
	long	number;

	coun = 0;
	np = 1;
	number = 0;
	if (str[0] == '\0')
		return (coun);
	while (str[coun] == ' ' || str[coun] == '\t' || str[coun] == '\f' || \
			str[coun] == '\r' || str[coun] == '\n' || str[coun] == '\v')
		coun++;
	if (str[coun] == '-' || str[coun] == '+')
	{
		if (str[coun] == '-')
			np *= -1;
		coun++;
	}
	while (str[coun] && str[coun] >= '0' && str[coun] <= '9')
	{
		number = number * 10 + (str[coun] - '0');
		coun++;
	}
	number *= np;
	return (number);
}
