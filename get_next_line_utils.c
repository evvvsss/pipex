#include "get_next_line.h"
#include "pipex_bonus.h"

int	check_line(char *buf)
{
	int	i;

	i = 0;
	if (!buf)
		return (-1);
	while (buf[i] != '\0')
	{
		if (buf[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*join(char *s1, char *s2, int n)
{
	int		i;
	int		j;
	char	*d;

	i = 0;
	j = 0;
	if (n == 1 && !s1)
		return (ft_strdup_g(s2));
	d = (char *)malloc(sizeof(char) * (ft_strlen_g(s1) + ft_strlen_g(s2) + 1));
	if (!d)
		return (NULL);
	while (s1 && s1[i] != '\0')
	{
		d[i] = s1[i];
		i++;
	}
	while (s2 && s2[j] != '\0')
		d[i++] = s2[j++];
	d[i] = '\0';
	if (s1)
		free((char *)s1);
	return (d);
}

int	check_eof(int k, char **linebuf, char *buf, char **line)
{
	if (k == 0 && (ft_strlen_g(*linebuf) == 0 || !*linebuf))
	{
		free(*linebuf);
		*linebuf = NULL;
		free(buf);
		*line = ft_strdup_g("");
		return (0);
	}
	return (1);
}

int	make_line_and_linebuf(char **line, char **linebuf, char **buf, int k)
{
	free(*buf);
	*buf = NULL;
	*line = ft_substr_g(*linebuf, check_line(*linebuf));
	if (!*line)
	{
		free(*linebuf);
		*linebuf = NULL;
		return (-1);
	}
	if (k != 0)
		*linebuf = cut_linebuf(*linebuf);
	if (!*linebuf)
		return (-1);
	if (k == 0)
	{
		free(*linebuf);
		*linebuf = NULL;
		return (0);
	}
	return (1);
}

int	read_and_join(char **buf, char **linebuf, int *k, int n)
{
	if (*k == -1)
	{
		free(*buf);
		return (-1);
	}
	(*buf)[*k] = '\0';
	*linebuf = join(*linebuf, *buf, n);
	if (!*linebuf)
	{
		free(*buf);
		return (-1);
	}
	return (1);
}
