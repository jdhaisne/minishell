/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhaisne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 13:54:00 by jdhaisne          #+#    #+#             */
/*   Updated: 2016/04/15 16:36:31 by jdhaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_link(char **tab, int i, char **tmp)
{
	struct stat	buf;
	char		*path;
	int			j;

	path = ft_strdup("/");
	path = ft_stradd(path, tab[0]);
	j = 1;
	while (j <= i && ft_strlen(tab[j]) > 0)
	{
		path = ft_stradd(path, "/");
		path = ft_stradd(path, tab[j]);
		j++;
	}
	lstat(path, &buf);
	if ((buf.st_mode & S_IFMT) != S_IFLNK)
		return (0);
	*tmp = ft_strnew(buf.st_size + 1);
	readlink(path, *tmp, buf.st_size + 1);
	return (1);
}

char	*clean2(char **tabpath)
{
	char	*new;
	int		i;

	i = 0;
	new = ft_strdup("/");
	while (tabpath[i] != NULL)
	{
		if (ft_strlen(tabpath[i]) > 0 && i > 0 && ft_strlenrc(new, '/') > 0)
			new = ft_stradd(new, "/");
		new = ft_stradd(new, tabpath[i]);
		ft_strdel(&tabpath[i]);
		i++;
	}
	new = remove_slash(new);
	return (new);
}

char	*clean(char *curpath, int p, int i, int j)
{
	char	**tabpath;
	char	*tmp;

	tabpath = ft_strsplit(curpath, '/');
	while (tabpath[++i] != NULL)
	{
		j = 0;
		if (ft_strequ(tabpath[i], "."))
			ft_strclr(tabpath[i]);
		else if (ft_strequ(tabpath[i], ".."))
		{
			ft_strclr(tabpath[i]);
			while (i - j >= 0 && ft_strlen(tabpath[i - j]) == 0)
				j++;
			if(i - j >= 0)
			ft_strclr(tabpath[i - j]);
		}
		else if (is_link(tabpath, i, &tmp) == 1 && p == 1)
		{
			ft_strdel(&tabpath[i]);
			tabpath[i] = ft_strdup(tmp);
			ft_strdel(&tmp);
		}
	}
	return (clean2(tabpath));
}

int		is_option(char *arg, int *p)
{
	int i;

	i = 1;
	if (arg[0] != '-')
		return (0);
	if (arg[1] == '\0')
		return (0);
	while (arg[i] != '\0')
	{
		if (arg[i] == 'P')
			*p = 1;
		else if (arg[i] == 'L')
			*p = 0;
		else
		{
			*p = 0;
			return (0);
		}
		i++;
	}
	return (1);
}

char	*cd_r(char **tab, char *arg1, char *arg2)
{
	int		i;
	int		a;
	char	*curpath;

	i = 0;
	a = 0;
	curpath = ft_strdup("");
	if (ft_strequ(arg1, "/"))
		return (ft_strjoin(arg2, getcwd(NULL, 0) + 1));
	while (tab[i] != NULL)
	{
		curpath = ft_stradd(curpath, "/");
		if (ft_strequ(tab[i], arg1) && a == 0)
		{
			curpath = ft_stradd(curpath, arg2);
			a = 1;
		}
		else
			curpath = ft_stradd(curpath, tab[i]);
		i++;
	}
	if (a == 0)
		return (NULL);
	return (curpath);
}
