/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouhail <ysouhail@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 06:58:17 by ysouhail          #+#    #+#             */
/*   Updated: 2024/11/19 10:32:01 by ysouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int str_cmp(char *s1, char *s2)
{
	int i = 0;
	int x = 0;
	while (s1[i] || s2[i])
	{
		if(s1[i] != s2[i])
		{
			return(s1[i]-s2[i]);
		}
		x = s1[i] - s2[i];
		i++;
	}
	return x;
}
bool		is_space(char *s)
{
	int  i = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t')
		{
			return(false);
		}
		i++;
	}
	return true;
}
char	*sub_str(char *str, int start, int len)
{
	int i = start;
	int j = 0;
	char *sub = malloc(len+1);
	if (!sub)
		return NULL;
	while (j < len && str[i])
	{
		sub[j] = str[i];
		i++;
		j++;
	}
	sub[j] = '\0';
	return sub;
}
int str_len(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return i;
}
char	*str_dup(char *str)
{
	int i = 0;
	char *dup;
	if (!str)
	{
		return NULL;
	}
	dup = malloc(str_len(str)+1);
	if (!dup)
	{
		return NULL;
	}
	
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
char *str_join(char *s1, char *s2)
{
	int i = 0;
	int j = 0;
	if(!s2)
		return NULL;
	if(!s1)
	{
		s1 = malloc(1);
		s1[0] = '\0';
	}
	char *str = malloc(str_len(s1) + str_len(s2) +1);
	if(!str)
		return NULL;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i+j] = s2[j];
		j++;
	}
	str[i+j] = '\0';
	return str;
	
}
char *cut_string(t_elem **list)
{
    char *rs = str_dup("");
    char *tmp = NULL;
    while ( (*list))
    {
        if (((*list)->content[0] == SING_Q || (*list)->content[0] == DOBL_Q) && (*list)->state == GENERAL)
        {
            (*list) = (*list)->next;
            if (!(*list))
                break;
        }
        if (((*list)->type == WHITE_SPACE && (*list)->state == GENERAL))
        {
			break;
		}
		if (((*list)->type == PIPE_LINE && (*list)->state == GENERAL))
		{
			// (*list) = (*list)->next;
			break;
		}
        tmp = str_join(rs, (*list)->content);
        free(rs);
        rs = str_dup(tmp);
        free(tmp);
        tmp = NULL;
		printf("*-*-*%s*-*-*\n",rs);
        (*list) = (*list)->next;
    }
    return rs;
}

// int main()
// {
// 	printf("%s\n", str_join("hellow", " jack"));
// 	return 0 ;
// }
// char *get_string_qut(t_elem *str)
// {
	
// }
// char	*str_join(char *s1, char *s2)
// {
	
// }
// char	*cpy_str(char *str)
// {
// 	int i = 0;
// 	char *cpy = malloc()
// 	while (str[i])
// 	{
// 		/* code */
// 	}
	
// }
