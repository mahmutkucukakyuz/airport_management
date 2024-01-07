#include "libft.h"
#include "stdio.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] == s2[i] && (s1[i] != '\0' || s2[i] != '\0'))
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

int ft_strcmp2(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;

	while (ft_tolower(s1[i]) == ft_tolower(s2[i]) && (s1[i] != '\0' || s2[i] != '\0')) {
        i++;
    }
    if ((s1[i] == '\0' || s2[i] == '\0') && (s1[i] == '\n' || s2[i] == '\n')) {
        return 0;
    }
    return ft_tolower(s1[i]) - ft_tolower(s2[i]);
}
