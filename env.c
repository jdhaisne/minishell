/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhaisne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 13:51:07 by jdhaisne          #+#    #+#             */
/*   Updated: 2016/04/06 13:32:31 by jdhaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char **list_to_tab(t_list *start)
{
	t_list *tmp;
	int		i;
	int 	j;
	char **tab;

	tmp = start;
	i = 0;
	j = 0;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	tab = (char **)ft_memalloc(sizeof(char *) * i + 1);
	tmp = start;
	while (j < i && tmp != NULL)
	{
		tab[j] = ft_strdup(tmp->content);
		tmp = tmp->next;
		j++;
	}
	tab[i] = NULL;
	return (tab);
}

char **split_tab(char **tab, int i)
{
	int size;
	int j;
	char **tab2;

	size = 0;
	j = 0;
	tab2 = NULL;
	while(tab[i + size] != NULL)
		size++;
	tab2 = (char **)ft_memalloc(sizeof(char *) * size + 1);
	while(j < size)
	{
		tab2[j] = strdup(tab[i + j]);
		j++;
	}
	tab2[size] = NULL;
	return (tab2);
}

void	ft_env(char **arg, t_list *env_l)
{
	int i;
	t_list *new_env;
	char **env;
	char **tab;
	char **path;


	i = 1;
	env = NULL;
	tab = NULL;
	path = get_path(list_to_tab(env_l));
	new_env = ft_lstdup(env_l);
	while(arg[i] != NULL && ft_strlen(arg[i]) == get_name_size(arg[i]))
	{
		if(ft_strcmp(arg[i], "-u") == 0)
		{
			ft_unsetenv(arg[i + 1], new_env);
			i += 2;
		}
		else if(ft_strcmp(arg[i], "-i") == 0)
		{
			new_env = NULL;
			i++;
		}
		else if (ft_strcmp(arg[i], "-P") == 0)
		{
			ft_putendl("alt_path");
			i++;
			ft_putendl(arg[i]);
			i++;
		}
		else
		{
			ft_putendl("error");
			break;
		}
	}
	while (arg[i] != NULL && ft_strlen(arg[i]) != get_name_size(arg[i]))
	{
		ft_setenv(arg[i], &new_env);
		i++;
	}
	if (arg[i] == NULL)
	{
		print_list(new_env);
	}
	else
	{
		env = list_to_tab(new_env);
		tab = split_tab(arg, i);
		if (ft_strequ(arg[i], "env") == 1)
			ft_env(tab, new_env);
		else
			launch(tab, env, path);
	}
}
