#include "libft.h"
#include <stdio.h>

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	coun;

	if (!dstsize && !dst)
		return (0);
	if (dstsize <= (size_t)ft_strlen(dst))
		return (dstsize + ft_strlen(src));
	i = ft_strlen(dst);
	coun = 0;
	while ((i + 1 < dstsize) && (src[coun] != '\0'))
	{
		dst[i] = src[coun];
		i++;
		coun++;
	}
	dst[i] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[coun]));
}
