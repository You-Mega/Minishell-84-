NAME = minishell

CC = gcc

CF = -Wall -Wextra -Werror

SRC = 	utils.c		print_staff.c  Lexer_new.c lexer_utils.c	parse.c

OBJ = $(SRC:.c=.o)

# FG = -lreadline -L/Users/ysouhail/.brew/opt/readline/lib

# HEADER = minishell.h -I/Users/adbouras/.brew/opt/readline/include

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CF)  -o $(NAME) $(OBJ) -lreadline

%.o : %.c $(HEADER)
	$(CC) $(CF) -c $< -o $@

clean :
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re : fclean all

.PHONY: clean fclean re