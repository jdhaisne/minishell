/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhaisne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 13:40:20 by jdhaisne          #+#    #+#             */
/*   Updated: 2016/04/15 14:58:31 by jdhaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cd_double_arg(char **arg,t_list *env_l, int p)
{
	char *new;
	char *pwd;

	pwd = ft_envar("PWD", env_l);
	new = ft_strnew(ft_strlen(pwd) - ft_strlen(arg[0]) + ft_strlen(arg[1]) + 1);
	if(ft_strstr(pwd, arg[0]) != NULL)
	{
		new = ft_strcat(new, ft_strsub(pwd, 0, ft_strlen(pwd) - \
					ft_strlen(ft_strstr(pwd, arg[0]))));
		new = ft_strcat(new, arg[1]);
		new = ft_strcat(new, ft_strstr(pwd, arg[0]) + ft_strlen(arg[0]));
		new = clean(new, p, -1);
		ft_putendl(new);
		return (new);
	}
	ft_putstr_fd("cd: string not in pwd: ", 2);
	ft_putendl_fd(arg[0], 2);
	return (NULL);
}
