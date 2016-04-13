/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhaisne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/11 18:48:29 by jdhaisne          #+#    #+#             */
/*   Updated: 2016/04/13 17:08:18 by jdhaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>

extern char **g_environ;

void	print_list(t_list *start);
char	**get_path(char **env);
void	launch(char **arg, char **env, char **path, char *place);
t_list	*double_tab_to_list(char **tab);
int	built_in(char **arg, t_list **env_l);
char	**list_to_tab(t_list *start);

void	ft_env(char **arg, t_list *env_l);
size_t	get_name_size(char *name);
void	ft_setenv(char *arg, t_list **env_l);
t_list	*ft_unsetenv(char *name, t_list *env_l);

void		cd(char **arg, t_list **env_l);
void	ft_exit(char **arg);
char	**split_tab(char **tab, int i);
char	**read_line(t_list *env_l);
char	*cd_r(char **tab, char *arg1, char *arg2);
int		is_option(char *arg, int *p);
int		is_link(char **tab, int i, char **tmp);
char	*clean(char *curpath, int p, int i);
char	*clean2(char **tabpath);
int cd_check_error(char *curpath);
char	*remove_slash(char *path);


#endif
