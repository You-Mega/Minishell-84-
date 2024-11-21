#ifndef MINISHELL_H
#define MINISHELL_H

#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <readline/history.h>

# define BBLK "\e[1;30m"
# define BRED "\e[1;31m"
# define BGRN "\e[1;32m"
# define BYEL "\e[1;33m"
# define BBLU "\e[1;34m"
# define BMAG "\e[1;35m"
# define BCYN "\e[1;36m"
# define RSET "\e[0m"

// # define prompt "Miini "

typedef struct s_elem t_elem;

typedef enum e_token
{
	WORD = 0,
	WHITE_SPACE = ' ',
	NEW_LINE = '\n',
	SING_Q = '\'',
	DOBL_Q = '\"',
	ESCAPE = '\\',
	ENV = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	HERE_DOC,
	//<<//
	APEND,
	//>>
}	t_token;

typedef enum e_state
{
	IN_DQUOTE,
	IN_SIQUOTE,
	GENERAL,
}	t_state;



typedef	struct	s_redi
{
	t_token	type;// in or out
	char	*file; // file name
	int		fd;
	struct	s_redi	*next;
}					t_redir;
typedef	struct	s_herdoc
{
	t_token	type;// in or out
	char	*delimiter;
	// char	*file; // file name
	int		fd;
	struct	s_redi	*next;
}					t_herdo;


typedef struct s_cmd
{
	char *cmd; // command "ls pr cd .."
	char **args; // argument "-a ...."
	int pip;
	t_herdo		*herdoc;
	t_redir		*redirect;
	struct s_cmd	*next;

}t_cmd;

struct s_elem
{
	char			    *content;
	int				    len;
	enum e_token	type;
	enum e_state	state;
	t_elem			  *next;
	// t_elem			  *prev;
};

typedef struct t_list
{
	t_elem	*head;
	t_elem	*end;
	int		  size;
}	t_list;


int		str_cmp(char *s1, char *s2);
bool	is_space(char *s);
int		is_operator(char c);
t_list	*init_list(t_list *list);
t_elem	*new_elem(char *content, int len, enum e_token type, enum e_state state);
// int		is_empty_(t_cmd **list);
int		is_empty(t_list *list);
void	add_tail(t_list *list, t_elem *new);
char	*sub_str(char *str, int start, int len);
int		str_len(char *str);
char	*print_state(int type);
void	print_list(t_list *list);
char	*get_state(int x);
void	handle_word(char *str, int *i, t_list *list, t_state x);
void	handle_env(char *str, int *i, t_list *list, t_state x);
void	handle_redirections(char *str, int *i, t_list *list, t_state x);
void	handle_quotes(t_list *list, char *str, int *i, t_state *state);
void	print_list(t_list *list);
void	sysntax_error(t_list *list);
void	free_list(t_list *list);
char	*str_dup(char *str);
void 	struct_full(t_list *list);
char 	*str_join(char *s1, char *s2);
char	**big_join(char **args, char* arg);
char	*cut_string(t_elem **list);

#endif