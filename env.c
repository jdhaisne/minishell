/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhaisne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 13:51:07 by jdhaisne          #+#    #+#             */
/*   Updated: 2016/04/15 16:30:39 by jdhaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**list_to_tab(t_list *start)
{
	t_list	*tmp;
	int		i;
	int		j;
	char	**tab;

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

char	**split_tab(char **tab, int i)
{
	int		size;
	int		j;
	char	**tab2;

	size = 0;
	j = 0;
	tab2 = NULL;
	while (tab[i + size] != NULL)
		size++;
	tab2 = (char **)ft_memalloc(sizeof(char *) * size + 1);
	while (j < size)
	{
		tab2[j] = strdup(tab[i + j]);
		j++;
	}
	tab2[size] = NULL;
	return (tab2);
}

int		env_opt(char **arg, t_list **new_env, int i)
{
	while (arg[i] != NULL && ft_strlen(arg[i]) == get_name_size(arg[i]))
	{
		if (ft_strcmp(arg[i], "-u") == 0)
		{
			if (arg[i + 1] == NULL)
			{
				ft_putstr("env: option require an arguments -- u\nusage: env ");
				ft_putstr("[-i] [-u name] [name=value ...] [utility [argument");
				ft_putendl("...]]");
				return (-1);
			}
			ft_unsetenv(arg[i + 1], *new_env);
			i += 2;
		}
		else if (ft_strcmp(arg[i], "-i") == 0 || ft_strequ(arg[i], "-"))
		{
			*new_env = NULL;
			i++;
		}
		else
			break ;
	}
	return (i);
}

void	ft_env(char **arg, t_list *env_l)
{
	int		i;
	t_list	*new_env;
	char	**env;
	char	**tab;
	char	**path;

	env = NULL;
	tab = NULL;
	if (env_l == NULL)
		return ;
	path = get_path(env_l);
	new_env = ft_lstdup(env_l);
	if ((i = env_opt(arg, &new_env, 1)) < 0)
		return ;
	while (arg[i] != NULL && ft_strlen(arg[i]) != get_name_size(arg[i]))
	{
		ft_setenv(arg[i], &new_env);
		i++;
	}
	if (arg[i] == NULL)
		print_list(new_env);
	else if (ft_strequ("env", arg[i]))
		ft_env(split_tab(arg, i), new_env);
	else
		launch(split_tab(arg, i), list_to_tab(new_env), path, "env");
}
