/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouhail <ysouhail@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:34:57 by ysouhail          #+#    #+#             */
/*   Updated: 2024/11/19 13:13:06 by ysouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sysntax_error(t_list *list)
{
	int count = 0;
	int x = 0;
	int i = 0;
	t_elem *current = list->head;
    t_elem *next;
	int pip = 0;
	while (current != NULL)
	{
		if(current->content[i] == SING_Q)
		{
			count++;
		}
		else if (current->content[i] == DOBL_Q)
		{
			x++;
		}
		else if (current->content[i]== PIPE_LINE)
		{
			if ((current->next && current->next->content[i] == '|' && current->state == GENERAL) 
					|| (list->head->content[i] == '|') || list->end->content[i] == '|')
            {
                pip = 1;
            }
		}
		next = current->next;
		current = next;
	}
	if (count % 2 != 0 || x % 2 != 0)
	{
		printf("synthax error\n");
		free_list(list);
	}
	else if(pip == 1)
	{
		printf("syntax error near unexpected token `|'\n");
		free_list(list);
	}
	else{
		// print_list(list);
		struct_full(list);
		free_list(list);
	}
}

t_cmd *init_cmd()
{
	t_cmd *cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return NULL;
    cmd->args = NULL;
    cmd->redirect = NULL;
    cmd->pip = 0;
	cmd->next = NULL;
    return cmd;
}
// void arg_fuller(char *str, t_cmd *cmds)
// {
	
// }

void arg_fuller(char *str, t_cmd *cmds)
{
    // int count = 0;

    // at the bginig is null
    if (cmds->args == NULL) 
	{
        cmds->args = malloc(sizeof(char *) * 2);
        if (cmds->args == NULL)
            return; 
        cmds->args[0] = str_dup(str);
        cmds->args[1] = NULL;
    } 
	else 
	{
        // Count the existing argument
        // while (cmds->args[count] != NULL)
        //     count++;

        // // ollcated memory for the new argnt
        // cmds->args = malloc(sizeof(char *) * (count + 2));
        // if (cmds->args == NULL)
        //     return;
        // // Add the new argnt
        // cmds->args[count] = str_dup(str);
        // cmds->args[count + 1] = NULL;
		cmds->args = big_join(cmds->args, str);
    }
}

char **big_join(char **args, char* arg)
{
	char **newargs;
	int count = 0;
	int i  = 0;
	while (args[i])
	{
		count++;
		i++;
	}
	i = 0;
	newargs = malloc(sizeof(char *) * (count + 2));
	while (args[i])
	{
		newargs[i] = str_dup(args[i]);
		i++;
	}
	newargs[i] = str_dup(arg);
	i++;
	newargs[i] =NULL;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	return(newargs);
}

// void add_back(t_cmd **list, t_cmd *new) 
// {
//     if (!list) 
//     {
//         (*list) = new;
//     } 
//     else 
//     {
//         (*list)->next = new;
//     }
// }
void add_back(t_cmd **list, t_cmd *new) 
{
    t_cmd *last = *list;
    if (!(*list) && !new)
        return ; 
    if (!list || !(*list)) 
    {
        *list = new;
    } 
    else 
    {
        while ((last)->next != NULL)
        {
            (last) = (last)->next;
        }
        last->next = new;
    }
}

void struct_full(t_list *list)
{
    t_elem *str = list->head;
    t_cmd *cmds = NULL;
    bool com = false;
    t_cmd *cmd =NULL;
    char *sub = NULL;

    while (str != NULL)
    {
        cmd = init_cmd();
        com = false;
        while (str != NULL)
        {
            // if (str->type == PIPE_LINE && str->state == GENERAL)
            // {
            //     break;
            // }
            // if (str->type == REDIR_IN)
            // {
                
            // }
            
            if (str->type == WORD)
            {
                sub = cut_string(&str);
                printf("...%s...\n", sub);
                if (com == false)
                {
                    printf("0000\n");
                    cmd->cmd = str_dup(sub);
                    com = true;
                }
                else
                {
                    printf("1111\n");
                    arg_fuller(sub, cmd);
                }
                free(sub);
                sub = NULL;
            }
            if (str == NULL)
                break;
            if (str->type == PIPE_LINE && str->state == GENERAL)
            {
                break;
            }
            // printf("content is %s\n", str->content);
            str = str->next;
        }
        add_back(&cmds, cmd);
        // cmd = init_cmd();
        // com = false;
        if (str != NULL && str->type == PIPE_LINE && str->state == GENERAL)
        {
            str = str->next;
            // cmd = init_cmd();
            // com = false;
        }
    }
    t_cmd *tmp = cmds;
    while (tmp)
    {
        int i = 0;
        printf("cmd == %s==\n",tmp->cmd);
        // if (cmd != NULL)
        
        while (tmp->args && tmp->args[i])
        {
            printf("args == %s==\n", tmp->args[i]);
            i++;
        }
        tmp = tmp->next;
    }
    // printf("cmd2 == %s\n",cmds->next->cmd);
    // t_cmd *tmp = cmds;
    // while (tmp)
    // {
    //     printf("cmd = %s\n",tmp->cmd);
    //     tmp = tmp->next;
    // }

    // int i = 0;
    // while (cmds)
    // {
    //     printf("/-/%s/-/\n", cmds->args[i]);
    //     i++;
    // }
}

// void struct_full(t_list *list)
// {
// 	t_elem *str = list->head;
//     // t_elem *next;
// 	t_cmd *cmds = init_cmd();
// 	bool com = false;
// 	t_cmd *cmd;
// 	// int x = 0;
// 	// int j = 0;
// 	char *sub = NULL;
// 	// char *join = NULL;
// 	while (str != NULL)
// 	{	
// 		cmd = init_cmd();	
// 		while (str->type != PIPE_LINE)
// 		{
// 			if (str->type == WORD)
// 			{
// 				sub = cut_string(&str);
// 				// printf("........%s....\n", sub);
// 				if(com == false)
// 				{
// 					cmd->cmd = str_dup(sub);
// 					com = true;
// 				}
// 				else
// 				{
// 					arg_fuller(sub, cmd);
// 				}
// 				free(sub);
// 				sub = NULL;
// 				printf("hhhh\n");
// 			}
// 			// else if(str->type == WORD && (str->state == IN_SIQUOTE || str->state == IN_DQUOTE))
// 			// {
// 			// 	if(str->state == IN_SIQUOTE)
// 			// 	{
// 			// 		// while (str->state == IN_SIQUOTE)
// 			// 		// {
// 			// 		// 	// sub = str_dup(str->content);
// 			// 		// 	join = str_join(sub, str->content);
// 			// 		// 	free(sub);
// 			// 		// 	sub = str_dup(join);
// 			// 		// 	free(join);
// 			// 		// 	// printf("----%s ",str->content);
// 			// 		// 	// printf("----%u\n",str->state);
// 			// 		// 	next = str->next;
// 			// 		// 	str = next;
// 			// 		// }
// 			// 		sub = cut_string(&str);
// 			// 		if(com == false)
// 			// 		{
// 			// 			cmd->cmd = str_dup(sub);
// 			// 			com = true;
// 			// 		}
// 			// 		else
// 			// 		{
// 			// 			// str = str->next;
// 			// 			arg_fuller(sub, cmd);
// 			// 		}
// 			// 	}
// 			// 	// printf("sub ===%s\n", sub);
// 			// 	free(sub);
// 			// 	sub =  NULL;
// 			// }
// 			// else if ((str->type == REDIR_IN || str->type == HERE_DOC) && str->state == GENERAL)
// 			// {
// 			// 	if(str->type == REDIR_IN)
// 			// 	{
// 			// 		cmd->redirect->type = REDIR_IN;
// 			// 		if (str->next->type == WORD && str->next->state == GENERAL)
// 			// 		{
// 			// 			cmd->redirect->file = str_dup(str->next->content);
// 			// 		}
// 			// 		else if (str->type == IN_SIQUOTE)
// 			// 		{
						
// 			// 		}
					
// 			// 	}
// 			// 	else
// 			// 	{
					
// 			// 	}
				
				
// 			// }
// 			printf("xxx\n");
// 			if(!str)
// 				break;
// 			str = str->next;
// 			printf("jjjj\n");
// 			// str = next;
// 		}
// 		add_back(&cmds, cmd);
// 		if(str)
// 			str = str->next;
// 	}
// 	printf("????%s??\n",cmd->cmd);
// 	// char **test = cmds->args;
// 	int i = 0;
	
// 	while (cmd->args && cmd->args[i])
// 	{
// 		printf("/-/%s/-/\n", cmd->args[i]);
// 		i++;
// 	}

// }
