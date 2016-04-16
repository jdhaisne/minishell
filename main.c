/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhaisne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 12:25:10 by jdhaisne          #+#    #+#             */
/*   Updated: 2016/04/16 18:58:45 by jdhaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_list *start)
{
	while (start != NULL)
	{
		ft_putendl(start->content);
		start = start->next;
	}
}

t_list	*double_tab_to_list(char **tab)
{
	int		i;
	t_list	*start;
	t_list	*tmp;

	i = 0;
	if (tab == NULL || tab[0] == NULL)
		return (NULL);
	start = ft_lstnew(tab[i], sizeof(char) * ft_strlen(tab[i]) + 1);
	tmp = start;
	i++;
	while (tab[i] != NULL)
	{
		tmp->next = ft_lstnew(tab[i], sizeof(char) * ft_strlen(tab[i]) + 1);
		tmp = tmp->next;
		i++;
	}
	tmp->next = NULL;
	return (start);
}

void	show_prompt(t_list *env_l)
{
	char *cwd;
	char *cwd_lnk;

	cwd = getcwd(NULL, 0);
	cwd_lnk = ft_envar("PWD", env_l);
	ft_putstr("$> ");
	if (cwd_lnk != NULL && ft_strlen(cwd_lnk) > 1)
		ft_putstr((ft_strrchr(cwd_lnk, '/')) + 1);
	else if (cwd_lnk != NULL && ft_strlen(cwd_lnk) <= 1)
		ft_putstr((ft_strrchr(cwd_lnk, '/')));
	else if (ft_strlen(cwd) > 1)
		ft_putstr((ft_strrchr(cwd, '/')) + 1);
	else
		ft_putstr((ft_strrchr(cwd, '/')));
	ft_putstr(": ");
	ft_strdel(&cwd);
}

int		main(int argc, char **argv, char **env)
{
	char	**arg;
	t_list	*env_l;
	char	**path;

	env_l = double_tab_to_list(env);
	path = get_path(env_l);
	ft_putendl("welcomw in jdsh");
	if (argc == 5)
		ft_putendl(argv[0]);
	while (1)
	{
		show_prompt(env_l);
		arg = read_line(env_l);
		if (*arg != NULL)
		{
			if (built_in(arg, &env_l, 1) == 0)
				launch(arg, list_to_tab(env_l), path, "minishell");
		}
		ft_free_double_tab(arg);
	}
	return (0);
}
