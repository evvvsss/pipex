NAME		= 	pipex

SRCS		=  	ft_split.c 		\
				ft_strdup.c 	\
				ft_strjoin.c 	\
				ft_strlen.c 	\
				ft_strnstr.c 	\
				ft_substr.c 	\
				pipex.c 		\
				
BONUS_SRCS	= 	ft_split.c 		\
				ft_strdup.c 	\
				ft_strjoin.c 	\
				ft_strlen.c 	\
				ft_strnstr.c 	\
				ft_substr.c 	\
				ft_strncmp.c	\
				pipex_bonus.c 	\
				pipex_bonus_add.c \
				get_next_line.c	\
				get_next_line_utils.c \

INCLUDES	=	./


OBJS		= 	${SRCS:.c=.o}

BONUS_OBJS	= 	${BONUS_SRCS:.c=.o}

CC			= 	gcc -g
RM			= 	rm -f

CFLAGS		= 	-Wall -Werror -Wextra 

.c.o:
				${CC} ${CFLAGS} -I ${INCLUDES} -c $< -o ${<:.c=.o}

${NAME}:		${OBJS}
				gcc -o $(NAME) $(OBJS)

all:			${NAME}

bonus:			${BONUS_OBJS}
				gcc -o ${NAME} $(BONUS_OBJS)

clean:			
				${RM} ${OBJS} $(BONUS_OBJS)

fclean:			clean 
				rm -rf ${NAME}

re:				fclean all

.PHONY:			all clean fclean 

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

#TESTS

TESTS = test1 test2 test3 test4

test1: all
	@./$(NAME) infile "ls -l" "wc -l" outfile
	@< infile ls -l | wc -l
	@echo "$(GREEN) test1 - [ok] $(RESET)"

test2: all
	@./$(NAME) infile "pwd" "wc" outfile
	@< infile pwd | wc 
	@echo "$(GREEN) test2 - [ok] $(RESET)"

test3: all
	@./$(NAME) infile "grep g" "wc" outfile
	@< infile grep g | wc
	@echo "$(GREEN) test3 - [ok] $(RESET)"

test4: all
	@./$(NAME) infile "grep a1" "ls" outfile | true
	@< infile grep a1 | ls
	@echo "$(GREEN) test4 - [ok] $(RESET)"

main_tests: $(TESTS)

BONUS_TESTS = bonus_test1 bonus_test2 bonus_test3 bonus_test5 bonus_test6

bonus_test1: bonus
	@./$(NAME) infile "grep a1" "wc -c" "wc -l" outfile
	@< infile grep a1 | wc -c | wc -l
	@echo "$(GREEN) bonus_test1 - [ok] $(RESET)"

bonus_test2: bonus
	@./$(NAME) here_doc a cat "wc -c" outfile
	@cat << a | wc -c
	@echo "$(GREEN) bonus_test2 - [ok] $(RESET)"

bonus_test3: bonus
	@./$(NAME) here_doc a cat "wc -c" "head -n 1" outfile
	@echo "$(GREEN) bonus_test3 - [ok] $(RESET)"

bonus_test4: bonus
	@./$(NAME) here_doc a cat "wc -c" "head -n 1" outfile1
	@cat << a | wc -c | head -n 1
	@echo "$(GREEN) bonus_test4 - [ok] $(RESET)"

bonus_test5: bonus
	@./$(NAME) infile "grep a1" "wc -c" "wc -l" outfile | true
	@< infil grep a1 | wc - c | wc -l
	@echo "$(GREEN) bonus_test5 - [ok] $(RESET)"

bonus_test6: bonus
	@./$(NAME) infile "ls -la" "grep 1" "head -n 5" "wc -l" outfile
	@< infile ls -la | grep 1 | head -n 5 | wc -l
	@echo "$(GREEN) bonus_test6 - [ok] $(RESET)"

bonus_tests: $(BONUS_TESTS)