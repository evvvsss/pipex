#include "pipex_bonus.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*d1;
	unsigned char	*d2;

	i = 0;
	d1 = (unsigned char *)s1;
	d2 = (unsigned char *)s2;
	while (i < n)
	{
		if (d1[i] != d2[i] || d1[i] == '\0' || d2[i] == '\0')
			return (d1[i] - d2[i]);
		else
			i++;
	}
	return (0);
}
