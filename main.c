/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhaisne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 12:25:10 by jdhaisne          #+#    #+#             */
/*   Updated: 2016/04/06 16:31:59 by jdhaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **get_path(char **env)
{
	int i;
	char **path;
	char *tmp;

	i = 0;
	if(env[0] == NULL)
		return (NULL);
	while (ft_strncmp(env[i], "PATH", 4) != 0)
		i++;
	path = ft_strsplit(env[i], ':');
	i = 0;
	while(path[i] != NULL)
	{
		tmp = ft_strjoin(path[i], "/");
		free(path[i]);
		path[i] = tmp;
		i++;
	}
	return(path);
}


void	print_list(t_list *start)
{
	while(start != NULL)
	{
		ft_putendl(start->content);
		start = start->next;
	}
}

int	built_in(char **arg, t_list **env_l)
{
	int i;

	i = 1;
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
		if(arg[1] == NULL)
				{
				ft_setenv(arg[1], env_l);
				return (1);
				}
		while(arg[i] != NULL)
		{
			ft_setenv(arg[i], env_l);
			i++;
		}
		return (1);
	}
		else if (ft_strcmp(arg[0], "unsetenv") == 0)
	{
		*env_l = ft_unsetenv(arg[1], *env_l);
		return (1);
	}
	else if (ft_strcmp(arg[0], "cd") == 0)
	{
		cd(arg, env_l);
		return (1);
	}
	else
		return (0);
}

t_list	*double_tab_to_list(char **tab)
{
	int		i;
	t_list	*start;
	t_list	*tmp;

	i = 0;
	if(tab[0] == NULL)
		return (NULL);
	start = ft_lstnew(tab[i], sizeof(char) * ft_strlen(tab[i]) + 1);
	tmp = start;
	i++;
	while(tab[i] != NULL)
	{
		tmp->next = ft_lstnew(tab[i], sizeof(char) * ft_strlen(tab[i]) + 1);
		tmp = tmp->next;
		i++;
	}
	tmp->next = NULL;
	return (start);
}

void	launch(char **arg, char **env, char **path)
{
	pid_t	pid;
	int		i;
	int		err;

	i = 0;
	err = -1;
	pid = fork();
	if(arg[0] == NULL)
		return ;
	if (pid == 0)
	{
		while (path[i] != NULL)
		{
			err = execve(ft_strjoin(path[i], arg[0]), arg, env);
			i++;
		}
		if(err == -1 && execve(arg[0], arg, env) == -1)
		{
			ft_putstr("minishell: command not found: ");
			ft_putendl(arg[0]);
		}
		exit(err);
	}
	if(pid > 0)
		wait(&i);
}

int main(int argc, char **argv)
{
	char	*str;
	char	**arg;
	t_list	*env_l;

	//init;
	env_l = double_tab_to_list(environ);
	ft_putendl("welcomw in jdsh");
	str = NULL;
	if (argc == 5)
		ft_putendl(argv[0]);
	while(1)
	{
		ft_putstr("$> ");
		arg = read();
		if(*arg != NULL)
		{
		if(built_in(arg, &env_l) == 0)
			launch(arg, list_to_tab(env_l), get_path(list_to_tab(env_l)));

		//close
		}
		free(str);
	}
	return (0);
}
