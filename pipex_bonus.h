#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "get_next_line.h"
# include <stdio.h> 
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>

typedef struct s_p
{
	char		**str_args;
	char		**p;
	int			fd[2];
	int			pid[2];
	int			in_out[2];
	int			i;
	int			*fd_bonus;
	int			doc;
}		t_p;

char	*ft_strnstr(const char *big, const char *little, size_t h);
char	**ft_split(char const *s, char c);
char	**path(char **envp);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
void	child(t_p *d, char *argv, int i, char **envp);
int		find_cmd(char **str_args, char **p, char **envp);
int		open_files(t_p *d, char *argv_out, char *argv_in, char *stop);
int		create_pipes(t_p *d, int argc, char **envp);
void	dup_close(t_p *d, int fd1, int fd2, int j);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		get_next_line(int fd, char **line);
int		check_argc(int argc, char *argv);
void	here_doc(t_p *d, char *stop);

#endif