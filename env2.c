/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhaisne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/17 14:55:13 by jdhaisne          #+#    #+#             */
/*   Updated: 2016/04/20 11:38:07 by jdhaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		env_err(int mode, char opt)
{
	if (mode == 1)
	{
		ft_putstr("env: illegal option -- ");
		ft_putchar(opt);
		ft_putchar('\n');
	}
	else
		ft_putstr("env: option require an arguments -- u\n");
	ft_putstr("usage: env [-i] [-u name] [name=value ...] [utility [argument");
	ft_putendl("...]]");
	return (-1);
}

void	free_env_err(char **path, t_list *new_env)
{
	ft_free_double_tab(path);
	ft_lstdel(&new_env, free_env);
}
