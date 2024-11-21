/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouhail <ysouhail@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:13:42 by ysouhail          #+#    #+#             */
/*   Updated: 2024/11/12 10:27:41 by ysouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_quotes(t_list *list, char *str, int *i, t_state *state)
{
    t_state new_state;
    t_token new_token;

    if (str[*i] == DOBL_Q)
    {
        new_state = IN_DQUOTE;
        new_token = DOBL_Q;
    }
    else
    {
        new_state = IN_SIQUOTE;
        new_token = SING_Q;
    }
    if (*state == GENERAL)
    {
        add_tail(list, new_elem(sub_str(str, *i, 1), 1, new_token, *state));
        *state = new_state;
    }
    else if (*state == new_state)
    {
        *state = GENERAL;
        add_tail(list, new_elem(sub_str(str, *i, 1), 1, new_token, *state));
    }
    else
        add_tail(list, new_elem(sub_str(str, *i, 1), 1, new_token, *state));
}

void handle_redirections(char *str, int *i, t_list *list, t_state x)
{
    if (str[*i] == '<' && str[*i + 1] == '<')
    {
        add_tail(list, new_elem("<<", 2, HERE_DOC, x));
        (*i)++;
    }
    else if (str[*i] == '>' && str[*i + 1] == '>')
    {
        add_tail(list, new_elem(">>", 2, APEND, x));
        (*i)++;
    }
    else if (str[*i] == '<')
    {
        add_tail(list, new_elem("<", 1, REDIR_IN, x));
    }
    else if (str[*i] == '>')
    {
        add_tail(list, new_elem(">", 1, REDIR_OUT, x));
    }
}

void handle_env(char *str, int *i, t_list *list, t_state x)
{
    if (str[*i] == ENV)
    {
        int start = *i;
        (*i)++;
        while (str[*i]!= ENV && str[*i]!='<' && str[*i]!= '>' && str[*i] != '\0' && !is_operator(str[*i]) && str[*i] != PIPE_LINE)
        {
            printf("xlx\n");
            (*i)++;
        }
        char *sub = sub_str(str, start, *i - start);
        add_tail(list, new_elem(sub, str_len(sub), ENV, x));
        free(sub);
        (*i)--; // Adjust the index to continue processing;
        // (*i)--;
    }
}

// Function to handle words
void handle_word(char *str, int *i, t_list *list, t_state x)
{
    if (!is_operator(str[*i]) && str[*i] && str[*i] != '<' && str[*i] != '>' && str[*i]!= ENV)
    {
        int start = *i;
        while (str[*i] != ENV && str[*i] && !is_operator(str[*i]) && str[*i] != WHITE_SPACE && str[*i] != '<' && str[*i] != '>')
        {
            (*i)++;
        }
        char *cpy = sub_str(str, start, (*i - start));
        add_tail(list, new_elem(cpy, str_len(cpy), WORD, x));
        free(cpy);
        (*i)--;
    }
}

int is_operator(char c)
{
    return (c == WHITE_SPACE || c == NEW_LINE || c == SING_Q || c == DOBL_Q ||
        c == ESCAPE || c == PIPE_LINE);
}