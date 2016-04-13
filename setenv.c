/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhaisne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 12:46:37 by jdhaisne          #+#    #+#             */
/*   Updated: 2016/04/13 17:05:08 by jdhaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*add_end(t_list *new, t_list *start)
{
	t_list	*tmp;

	tmp = start;
	if (start == NULL)
	{
		start = new;
		return (start);
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	return (start);
}

size_t	get_name_size(char *name)
{
	size_t		i;

	i = 0;
	while (name[i] != '\0' && name[i] != '=')
		i++;
	return (i);
}

void	ft_setenv(char *arg, t_list **env_l)
{
	t_list *tmp;

	tmp = *env_l;
	if (arg == NULL)
	{
		print_list(*env_l);
		return ;
	}
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, arg, get_name_size(arg)) == 0)
		{
			free(tmp->content);
			tmp->content = ft_strdup(arg);
			tmp->content_size = (sizeof(char) * ft_strlen(arg) + 1);
			return ;
		}
		tmp = tmp->next;
	}
	if (ft_strlen(arg) == get_name_size(arg))
		arg = ft_strjoin(arg, "=");
	*env_l = add_end(ft_lstnew(arg, sizeof(char) * ft_strlen(arg) + 1), *env_l);
}
