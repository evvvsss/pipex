#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# define BUFFER_SIZE 1

int		get_next_line(int fd, char **line);
int		check_line(char *linebuf);
char	*join(char *s1, char *s2, int n);
char	*ft_strdup_g(char *s);
int		ft_strlen_g(const char *s);
char	*ft_substr_g(char *s, int len);
char	*cut_linebuf(char *linebuf);
int		check_eof(int k, char **linebuf, char *buf, char **line);
int		make_line_and_linebuf(char **line, char **linebuf, char **buf, int k);
int		read_and_join(char **buf, char **linebuf, int *k, int n);

#endif