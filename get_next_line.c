#include "get_next_line.h"
#include "pipex_bonus.h"

int	ft_strlen_g(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_substr_g(char *s, int len)
{
	char	*b;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	if ((ft_strlen_g(s) == 0) || (len <= 0))
		return (ft_strdup_g(""));
	b = (char *)malloc((len + 1) * sizeof(char));
	if (!b)
		return (NULL);
	while (s[i] != '\0' && len > 0)
	{
		b[i] = s[i];
		i++;
		len--;
	}
	b[i] = '\0';
	return (b);
}

char	*ft_strdup_g(char *s)
{
	int			len;
	int			i;
	char		*d;

	i = 0;
	len = ft_strlen_g(s);
	d = malloc(sizeof(char) * (len + 1));
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

char	*cut_linebuf(char *linebuf)
{
	int		i;
	int		j;
	char	*new_linebuf;

	i = 0;
	j = 0;
	while (linebuf[i] != '\n' && linebuf[i] != '\0')
		i++;
	if (linebuf[i] != '\n')
		return (ft_strdup_g(""));
	new_linebuf = malloc(sizeof(char) * (ft_strlen_g(linebuf) - \
		check_line(linebuf) + 1));
	if (!new_linebuf)
		return (NULL);
	i++;
	while (linebuf[i] != '\0')
		new_linebuf[j++] = linebuf[i++];
	new_linebuf[j] = '\0';
	free(linebuf);
	return (new_linebuf);
}

int	get_next_line(int fd, char **line)
{
	char		*buf;
	static char	*linebuf;
	int			n;
	int			k;

	n = 0;
	k = 1;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (-1);
	while (check_line(linebuf) == -1 && k != 0 && ++n)
	{
		k = read(fd, buf, BUFFER_SIZE);
		if (read_and_join(&buf, &linebuf, &k, n) == -1)
			return (-1);
		if (check_eof(k, &linebuf, buf, &(*line)) == 0)
			return (0);
	}
	if (k < BUFFER_SIZE && check_line(linebuf) == -1)
		linebuf[ft_strlen_g(linebuf)] = '\n';
	return (make_line_and_linebuf(&(*line), &linebuf, &buf, k));
}
