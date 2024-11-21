/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_staff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouhail <ysouhail@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 11:54:34 by ysouhail          #+#    #+#             */
/*   Updated: 2024/11/08 10:26:07 by ysouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *print_state(int type)
{
    if (type == ENV)
        return "ENV";
    else if (type == HERE_DOC)
        return "HERE_DOC";
    else if (type == REDIR_IN)
        return "REDIR_IN";
    else if (type == REDIR_OUT)
        return "REDIR_OUT";
    // else if (type == GENERAL)
    //     return "GENERAL";
    else if (type == APEND)
        return "APEND";
    else if (type == WORD)
        return "WORD";
    else if (type == WHITE_SPACE)
        return "WHITE_SPACE";
    else if (type == PIPE_LINE)
        return "PIPE_LINE";
    else if (type == SING_Q)
        return "SING_Q";
    else if (type == DOBL_Q)
        return "DOBL_Q";
    else
        return "UNKNOWN";
}

char *get_state(int x)
{
    if (x == IN_DQUOTE)
        return("IN_DQUOTE");
    else if(x == IN_SIQUOTE)
        return("IN_SIQUOTE");
   else
        return("GENERAL");
}

void print_list(t_list *list)
{
    if (!list)
    {
        return;
    }
    t_elem *current = list->head;
    while (current != NULL)
    {
        printf("Content: %s\n", current->content);
        printf("Length: %d\n", current->len);
        printf("Type: %s\n", print_state(current->type));
        printf("State: %s\n", get_state(current->state));
        printf("--------------------\n");
        current = current->next;
    }
}