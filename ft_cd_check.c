/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhaisne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/13 12:31:55 by jdhaisne          #+#    #+#             */
/*   Updated: 2016/04/13 15:07:03 by jdhaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_slash(char *path)
{
	int i;
	int j;
	char *new;

	i = 0;
	j = 0;
	new = ft_strnew(sizeof(char) * ft_strlen(path) + 1);
	while(path[i] != '\0')
	{
		if(!(path[i] == '/' && path[i + 1] == '/'))
		{
			new[j] = path[i];
			j++;
		}
		i++;
	}
	ft_strdel(&path);
	return (new);
}

int cd_check_error(char *curpath)
{
	char	**tab;
	char	*tmp;
	int		i;

	tab = ft_strsplit(curpath, '/');
	i = 0;
	tmp = ft_strnew(sizeof(char));
	while(tab[i] != NULL)
	{
		tmp = ft_stradd(tmp, "/");
		tmp = ft_stradd(tmp, tab[i]);
		if(access(tmp, F_OK) == -1)
		{
			ft_putstr("cd : ");
			ft_putstr(tmp);
			ft_putendl(": no such file or directories");
			return (1);
		}
		if(access(tmp, X_OK) == -1)
		{
			ft_putstr("cd : ");
			ft_putstr(tmp);
			ft_putendl(": permission denied");
			return (1);
		}
		tmp = clean(tmp, 0, 0);
		i++;
	}
	ft_putendl("a");
	return (0);
}
