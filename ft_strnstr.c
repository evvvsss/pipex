#include "pipex.h"

char	*ft_strnstr(const char *big, const char *little, size_t h)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[j] == '\0')
		return ((char *)big);
	while (big[i] != '\0' && i < h)
	{
		while (big[i + j] == little[j])
		{
			j++;
			if (little[j] == '\0')
				return ((char *)big + i + j + 1);
		}
		i++;
		j = 0;
	}
	return (NULL);
}
