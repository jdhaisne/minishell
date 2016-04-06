/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhaisne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 12:25:10 by jdhaisne          #+#    #+#             */
/*   Updated: 2016/04/01 16:13:51 by jdhaisne         ###   ########.fr       */
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
	if (ft_strcmp(arg[0], "exit") == 0)
	{
		exit(0);
		return (1);
	}
	else if (ft_strcmp(arg[0], "env") == 0)
	{
		ft_env(arg, *env_l);
		return (1);
	}
	else if (ft_strcmp(arg[0], "setenv") == 0)
	{
		ft_setenv(arg[1], env_l);
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
		if(err == -1)
		{
			ft_putstr("minishell: command not found: ");
			ft_putendl(arg[0]);
		}
		exit(0);
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
	if (argc == 5)
		ft_putendl(argv[0]);
	while(1)
	{
		ft_putstr("$> ");
		get_next_line(0, &str);
		str = ft_strtrim(str);
		arg = ft_strsplit(str, ' ');
		if(*arg != NULL)
		{
		if(built_in(arg, &env_l) == 0)
			launch(arg, environ, get_path(environ));

		//close
		}
		free(str);
	}
	return (0);
}
