#include "pipex.h"

char	*ft_strdup(const char *s)
{
	size_t		len;
	size_t		i;
	char		*d;

	i = 0;
	len = ft_strlen(s);
	d = malloc(sizeof(*s) * (len + 1));
	if (!d)
		return (NULL);
	while (s[i] != '\0')
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}
