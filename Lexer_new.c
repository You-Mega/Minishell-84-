/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouhail <ysouhail@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 11:59:19 by ysouhail          #+#    #+#             */
/*   Updated: 2024/11/19 13:45:53 by ysouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list *init_list(t_list *list)
{
    list = malloc(sizeof(t_list));
    if (!list)
    {
        return NULL;
    }
    list->head = NULL;
    list->end = NULL;
    list->size = 0;
    return list;
}

int is_empty(t_list *list)
{
    return (list->head == NULL);
}

t_elem *new_elem(char *content, int len,  enum e_token type,  enum e_state state) 
{
    t_elem *newnode = (t_elem *)malloc(sizeof(t_elem));
    if (!newnode)
        return NULL;
    newnode->content = str_dup(content);
    newnode->len = len;
    newnode->type = type;
    newnode->state = state;
    newnode->next = NULL;
    return (newnode);
}
// Function to handle quotes
void add_tail(t_list *list, t_elem *new) 
{
    if (is_empty(list)) 
    {
        list->head = new;
        list->end = new;
    } 
    else 
    {
        list->end->next = new;
        list->end = new;
    }
    list->size++;
}

// Main lexer function
t_list *ft_lexer(char *str)
{
    t_list  *list = NULL;
    t_state state;
    int     i;

    list = init_list(list);
    state = GENERAL;
    i = 0;
    while (str[i])
    {
        if (str[i] == SING_Q || str[i] == DOBL_Q)
            handle_quotes(list,str, &i, &state);
        else if (is_operator(str[i]))
            add_tail(list, new_elem(sub_str(str, i, 1), 1, str[i], state));
        else
        {
            handle_word(str, &i, list, state);
            handle_env(str, &i, list, state);
            handle_redirections(str, &i, list, state);
        }
        i++;
    }
    return(list);
}

// Function to print the list

// void bojak(void)
// {
//     system("leaks minishell");
// }
// Main function
int main(int ac, char **av, char **env)
{
    // atexit(bojak);
    (void)av;
    (void)env;
    if(ac != 1)
    {
        return 1;
    }
    while (1)
    {
        char *line;
        line = readline(BRED"$"RSET);
        if (!line)
        {
            printf("exit\n");
            exit(1);
        }
        if(!is_space(line))
            sysntax_error(ft_lexer(line));
        if (line[0])
            add_history(line);
        
    }
    return 0;
}

// Frees all the elements in the list and the list itself
void free_list(t_list *list) 
{
    t_elem *current = list->head;
    t_elem *next;
    while (current != NULL) 
    {
        next = current->next;
        free(current);
        current = next;
    }
    free(list);
}