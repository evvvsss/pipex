#include "pipex_bonus.h"

char	**path(char **envp)
{
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	while (str == NULL && envp[i] != NULL)
	{
		str = ft_strnstr(envp[i], "PATH", 4);
		i++;
	}
	return (ft_split(str, ':'));
}

void	child(t_p *d, char *argv, int i, char **envp)
{
	if (d->pid[0] == 0)
	{
		if (d->i == 0)
		{
			dup_close(d, d->in_out[0], d->fd_bonus[1], 2 * (i - 1));
			close(d->in_out[0]);
		}
		else if (i - d->i == 1)
		{
			dup_close(d, d->fd_bonus[2 * d->i - 2], d->in_out[1], 2 * (i - 1));
			close(d->in_out[1]);
		}
		else
			dup_close(d, d->fd_bonus[2 * d->i - 2],
				d->fd_bonus[2 * d->i + 1], 2 * (i - 1));
		while ((2 * (i - 1)) >= 0)
			close(d->fd_bonus[i--]);
		d->str_args = ft_split(argv, ' ');
		if (find_cmd(d->str_args, d->p, envp) == 1)
			exit (1);
	}
}

int	find_cmd(char **str_args, char **p, char **envp)
{
	char	*tmp;
	char	*str_path;
	int		k;
	int		i;

	i = 0;
	k = 0;
	while (p[i] != NULL && k != 1)
	{
		str_path = ft_strjoin(p[i], "/");
		tmp = str_path;
		str_path = ft_strjoin(tmp, str_args[0]);
		free(tmp);
		if (access(str_path, 0) == 0)
			k = 1;
		i++;
	}
	if (k == 0)
	{	
		write(2, "Command not found\n", 18);
		return (1);
	}
	if (execve(str_path, str_args, envp) == -1)
		write(2, "Сommand execution error\n", 24);
	return (0);
}

int	open_files(t_p *d, char *argv_out, char *argv_in, char *stop)
{
	d->i = -1;
	d->doc = 3;
	d->in_out[1] = open(argv_out, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (d->in_out[1] == -1)
	{
		write(2, "Cannot open output file\n", 24);
		return (1);
	}
	if (ft_strncmp(argv_in, "here_doc", ft_strlen(argv_in)) == 0)
		here_doc(d, stop);
	else
		d->in_out[0] = open(argv_in, O_RDONLY);
	if (d->in_out[0] == -1)
	{
		write(2, "Cannot open input file\n", 24);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_p	d;

	if (check_argc(argc, argv[1]) == 1)
		return (1);
	if (open_files(&d, argv[argc - 1], argv[1], argv[2]) == 1)
		return (1);
	d.fd_bonus = malloc(sizeof(int) * (2 * (argc - 1 - d.doc)));
	if (create_pipes(&d, argc, envp) == 1)
		return (1);
	while (argc - d.doc - ++d.i > 0)
	{
		d.pid[0] = fork();
		if (d.pid[0] == -1)
		{
			write(2, "Fork error\n", 11);
			exit (1);
		}
		child(&d, argv[d.doc - 1 + d.i], argc - d.doc, envp);
	}
	if (d.doc == 4)
		unlink("del.txt");
	wait(0);
	free(d.fd_bonus);
	return (0);
}
