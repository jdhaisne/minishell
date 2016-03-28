/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhaisne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 12:25:10 by jdhaisne          #+#    #+#             */
/*   Updated: 2016/03/25 15:35:20 by jdhaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **get_path(char **env)
{
	int i;
	char **path;
	char *tmp;

	i = 0;
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

char *get_home_path(t_list *env_l)
{
	char	*home_path;
	char	**tmp;

	while(ft_strncmp(env_l->content, "HOME", 4) != 0)
		env_l = env_l->next;
	home_path = env_l->content;
	tmp = ft_strsplit(home_path, '=');
	home_path = tmp[1];
	//free_double(tmp);
	return (home_path);
}

void cd(char **arg, t_list *env_l)
{
	char *home;
	home = get_home_path(env_l);
	if(arg[1] == NULL)
		chdir(home);
	else if(arg[2] == NULL)
		chdir(arg[1]);
}

void	print_list(t_list *start)
{
	while(start != NULL)
	{
		ft_putendl(start->content);
		start = start->next;
	}
}

char *get_value(t_list *env_l, char *name)
{
	char *value;
	char **tmp;

	value = NULL;
	while (env_l != NULL)
	{
		if(ft_strncmp(env_l->content, name, ft_strlen(name)) == 0)
		{
			tmp = ft_strsplit(env_l->content, '=');
			value = tmp[1];
		}
		env_l = env_l->next;
	}
	return (value);
}

void	env(char **arg, t_list *env_l)
{
	int i;
	char *value;

	i = 1;
	value = NULL;
	if (arg[i] == NULL)
		print_list(env_l);
	while (arg[i] != NULL)
	{
		value = get_value(env_l, arg[i]);
		if(value != NULL)
			ft_putendl(value);
		i++;
	}
}

t_list	*add_end(t_list *start, t_list *new)
{
	t_list *tmp;

	tmp = start;
	while(tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	return(start);
}

void	ft_setenv(char **arg, t_list **env_l)
{
	t_list *new;
	char *str;

	if (arg[1] == NULL)
	{
		print_list(*env_l);
		return ;
	}
	str = ft_strjoin(arg[1], "=");
	if(arg[2] != NULL)
		str = ft_strjoin(str, arg[2]);
	new = ft_lstnew(str, sizeof(char) * ft_strlen(str));
	*env_l = add_end(*env_l, new);
}

void	built_in(char **arg, t_list **env_l)
{
	if (ft_strcmp(arg[0], "exit") == 0)
		exit(0);
	else if (ft_strcmp(arg[0], "env") == 0)
		env(arg, *env_l);
	else if (ft_strcmp(arg[0], "setenv") == 0)
		ft_setenv(arg, env_l);
	else if (ft_strcmp(arg[0], "cd") == 0)
		cd(arg, *env_l);
}

t_list	*double_tab_to_list(char** tab)
{
	int		i;
	t_list	*start;
	t_list	*tmp;

	i = 0;
	start = ft_lstnew(tab[i], sizeof(char) * ft_strlen(tab[i]));
	tmp = start;
	i++;
	while(tab[i] != NULL)
	{
		tmp->next = ft_lstnew(tab[i], sizeof(char) * ft_strlen(tab[i]));
		tmp = tmp->next;
		i++;
	}
	tmp->next = NULL;
	return (start);
}

int main(int argc, char **argv, char **env)
{
	char	*str;
	char	**arg;
	char	**path;
	t_list	*env_l;
	int		i;
	pid_t pid;

	//init;
	path = get_path(env);
	env_l = double_tab_to_list(env);
	while(1)
	{
		i = 0;
		ft_putstr("$> ");
		get_next_line(0, &str);
		arg = ft_strsplit(str, ' ');
		built_in(arg, &env_l);
		pid = fork();
		if(pid == 0)
		{
			while(path[i] != NULL)
			{
				execve(ft_strjoin(path[i], arg[0]), arg, env);

				i++;
			}
		}
		if(pid > 0)
			wait(&i);
		//close
		free(str);
	}
	return (0);
}
