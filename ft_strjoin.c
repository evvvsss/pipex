#include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*d;
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	d = malloc((len + 1) * sizeof(char));
	if (!d)
		return (NULL);
	while (s1[i] != '\0')
	{
		d[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		d[i++] = s2[j++];
	d[i] = '\0';
	return (d);
}
