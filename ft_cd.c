/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhaisne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 12:24:35 by jdhaisne          #+#    #+#             */
/*   Updated: 2016/04/16 20:04:15 by jdhaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cd_old(t_list *env_l)
{
	char *curpath;
	char *oldpwd;

	oldpwd = ft_envar("OLDPWD", env_l);
	if (oldpwd == NULL || ft_strlen(oldpwd) == 0)
	{
		ft_putendl("cd: OLDPWD not set");
		return (NULL);
	}
	curpath = ft_strdup(oldpwd);
	ft_putendl(oldpwd);
	return (curpath);
}

char	*cd_get_curpath(char *arg, t_list *env_l, int i)
{
	char *curpath;
	char *cwd;

	if (arg[0] == '~')
	{
		curpath = ft_strdup(ft_envar("HOME", env_l));
		curpath = ft_stradd(curpath, "/");
		curpath = ft_stradd(curpath, arg + 1);
	}
	else
	{
		if ((cwd = ft_envar("PWD", env_l)) == NULL)
		{
			cwd = getcwd(NULL, 0);
			i = 1;
		}
		if (ft_strequ(cwd, "/") == 0)
			curpath = ft_strdup(cwd);
		else
			curpath = ft_strnew(sizeof(char));
		curpath = ft_stradd(ft_stradd(curpath, "/"), arg);
	}
	if (i == 1)
		ft_strdel(&cwd);
	return (curpath);
}

char	*cd_dir(char **arg, int i, int p, t_list *env_l)
{
	char *curpath;

	if (arg[i + 1] != NULL && arg[i + 2] == NULL)
	{
		curpath = cd_double_arg(split_tab(arg, i), env_l, p);
	}
	else if (arg[i + 1] != NULL && arg[i + 2] != NULL)
	{
		ft_putendl("cd: too many arguments");
		return (NULL);
	}
	else if (arg[i][0] == '/')
		curpath = ft_strdup(arg[i]);
	else if (ft_strequ(arg[i], "-") == 1)
		curpath = cd_old(env_l);
	else
		curpath = cd_get_curpath(arg[i], env_l, 0);
	if (cd_check_error(curpath, p) == 1)
		return (NULL);
	return (curpath);
}

void	cd_end(char *curpath, char *pwd, int p, t_list **env_l)
{
	curpath = clean(curpath, p, -1, 0);
	if (chdir(curpath) < 0)
	{
		ft_putendl(curpath);
		ft_putendl("cd: error");
		return ;
	}
	ft_strdel(&pwd);
	pwd = ft_strjoin("OLDPWD=", ft_envar("PWD", *env_l));
	if (pwd != NULL)
		ft_setenv(pwd, env_l);
	ft_strdel(&pwd);
	pwd = ft_strjoin("PWD=", curpath);
	ft_setenv(pwd, env_l);
	ft_strdel(&pwd);
	ft_strdel(&curpath);
}

void	cd(char **arg, t_list **env_l, int p)
{
	char	*home;
	int		i;
	char	*curpath;
	char	*pwd;

	i = 1;
	home = ft_envar("HOME", *env_l);
	pwd = getcwd(NULL, 0);
	while (arg[i] != NULL && is_option(arg[i], &p))
		i++;
	if (arg[i] == NULL)
	{
		if (home == NULL)
		{
			ft_putendl("cd: home not set");
			return ;
		}
		else
			curpath = ft_strdup(home);
	}
	else
		curpath = cd_dir(arg, i, p, *env_l);
	if (curpath == NULL)
		return ;
	cd_end(curpath, pwd, p, env_l);
}
