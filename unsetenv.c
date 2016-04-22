/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhaisne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 13:52:23 by jdhaisne          #+#    #+#             */
/*   Updated: 2016/04/17 16:11:47 by jdhaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_unsetenv(char *name)
{
	if (name == NULL)
	{
		ft_putendl("unsetenv: no argument");
		return (1);
	}
	if (ft_strequ(name, "="))
	{
		ft_putendl("unsetenv: invalid arguments");
		return (1);
	}
	return (0);
}

t_list		*ft_unsetenv(char *name, t_list *env_l)
{
	t_list	*tmp1;
	t_list	*tmp2;

	tmp1 = env_l;
	tmp2 = NULL;
	if (check_unsetenv(name) == 1)
		return (env_l);
	while (tmp1 != NULL)
	{
		if (ft_strncmp(name, tmp1->content, get_name_size(tmp1->content)) == 0)
		{
			if (tmp2 != NULL)
				tmp2->next = tmp1->next;
			free(tmp1->content);
			if (tmp2 == NULL)
				env_l = tmp1->next;
			free(tmp1);
			tmp1 = NULL;
			return (env_l);
		}
		tmp2 = tmp1;
		tmp1 = tmp1->next;
	}
	return (env_l);
}
