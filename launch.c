/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhaisne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 18:01:20 by jdhaisne          #+#    #+#             */
/*   Updated: 2016/04/16 20:04:31 by jdhaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**get_path(t_list *env_l)
{
	int		i;
	char	**path;
	char	*tmp;

	if (env_l == NULL)
		return (NULL);
	tmp = ft_envar("PATH", env_l);
	if (tmp == NULL)
		return (NULL);
	path = ft_strsplit(tmp, ':');
	i = 0;
	while (path[i] != NULL)
	{
		path[i] = ft_stradd(path[i], "/");
		i++;
	}
	return (path);
}

static int	built_in2(char **arg, t_list **env_l)
{
	if (ft_strcmp(arg[0], "unsetenv") == 0)
	{
		*env_l = ft_unsetenv(arg[1], *env_l);
		return (1);
	}
	else if (ft_strcmp(arg[0], "cd") == 0)
	{
		cd(arg, env_l, 0);
		return (1);
	}
	else if (ft_strcmp(arg[0], "env") == 0)
	{
		ft_env(arg, *env_l);
		return (1);
	}
	return (0);
}

int			built_in(char **arg, t_list **env_l, int i)
{
	if (ft_strcmp(arg[0], "exit") == 0)
	{
		ft_exit(arg);
		return (1);
	}
	else if (ft_strcmp(arg[0], "env") == 0)
	{
		ft_env(arg, *env_l);
		return (1);
	}
	else if (ft_strcmp(arg[0], "setenv") == 0)
	{
		if (arg[1] == NULL)
		{
			ft_setenv(arg[1], env_l);
			return (1);
		}
		while (arg[i] != NULL)
		{
			ft_setenv(arg[i], env_l);
			i++;
		}
		return (1);
	}
	return (built_in2(arg, env_l));
}

static void	son_process(char **path, char **arg, char **env, char *place)
{
	int err;
	int i;

	err = -1;
	i = 0;
	signal(SIGINT, SIG_DFL);
	while (path[i] != NULL)
	{
		err = execve(ft_strjoin(path[i], arg[0]), arg, env);
		i++;
	}
	if (err == -1 && execve(arg[0], arg, env) == -1)
	{
		ft_putstr(place);
		ft_putstr(": command not found: ");
		ft_putstr(arg[0]);
	}
	ft_free_double_tab(arg);
	ft_putchar('\n');
	exit(err);
}

void		launch(char **arg, char **env, char **path, char *place)
{
	pid_t	pid;
	int		i;

	i = 0;
	pid = fork();
	if (arg[0] == NULL)
		return ;
	if (pid == 0)
		son_process(path, arg, env, place);
	if (pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		wait(&i);
	}
	ft_free_double_tab(env);
}
