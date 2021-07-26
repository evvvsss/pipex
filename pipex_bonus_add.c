#include "pipex_bonus.h"

int	create_pipes(t_p *d, int argc, char **envp)
{
	int	j;

	j = 0;
	d->p = path(envp);
	while (argc - d->doc - j > 0)
	{	
		if (pipe(d->fd_bonus + 2 * j) == -1)
		{
			write(2, "Pipe error\n", 11);
			return (1);
		}
		j++;
	}
	return (0);
}

void	dup_close(t_p *d, int fd1, int fd2, int j)
{
	dup2(fd1, 0);
	dup2(fd2, 1);
	while (j >= 0)
		close(d->fd_bonus[j--]);
}

int	check_argc(int argc, char *argv)
{
	if (argc < 5)
	{
		write(2, "Write 5 or more arguments\n", 26);
		return (1);
	}
	if (argc < 6 && ft_strncmp(argv, "here_doc", ft_strlen(argv)) == 0)
	{
		write(2, "Write 6 arguments\n", 18);
		return (1);
	}
	return (0);
}

void	here_doc(t_p *d, char *stop)
{
	char	*line;

	d->in_out[0] = open("del.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
	while (get_next_line(0, &line) > 0
		&&ft_strncmp(line, stop, ft_strlen(stop) + 1) != 0)
	{	
		write(d->in_out[0], line, ft_strlen(line));
		write(d->in_out[0], "\n", 1);
	}
	free(line);
	d->doc = 4;
	close(d->in_out[0]);
	d->in_out[0] = open("del.txt", O_RDONLY);
}
