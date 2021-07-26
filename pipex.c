#include "pipex.h"

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
	if (d->pid[i - 1] == -1)
	{
		write(2, "Fork error\n", 11);
		exit (1);
	}
	if (d->pid[i - 1] == 0)
	{
		dup2(d->in_out[i - 1], i - 1);
		close(d->in_out[i - 1]);
		if (i == 1)
			dup2(d->fd[1], 1);
		else
			dup2(d->fd[0], 0);
		close(d->fd[1]);
		close(d->fd[0]);
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

int	open_files(t_p *d, char *argv_out, char *argv_in)
{
	d->in_out[1] = open(argv_out, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (d->in_out[1] == -1)
	{
		write(2, "Cannot open output file\n", 24);
		return (1);
	}
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

	if (argc != 5)
	{
		write(2, "Write 5 arguments\n", 18);
		return (1);
	}
	d.p = path(envp);
	if (pipe(d.fd) == -1)
	{
		write(2, "Pipe error\n", 11);
		return (1);
	}
	if (open_files(&d, argv[4], argv[1]) == 1)
		return (1);
	d.pid[0] = fork();
	child(&d, argv[2], 1, envp);
	d.pid[1] = fork();
	child(&d, argv[3], 2, envp);
	close(d.fd[0]);
	waitpid (d.pid[0], NULL, 0);
	close(d.fd[1]);
	waitpid (d.pid[1], NULL, 0);
	return (0);
}
