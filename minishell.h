#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

extern char **environ;

void	print_list(t_list *start);
char	**get_path(char **env);
void	launch(char **arg, char **env, char **path);
t_list	*double_tab_to_list(char **tab);
int	built_in(char **arg, t_list **env_l);
char	**list_to_tab(t_list *start);

void	ft_env(char **arg, t_list *env_l);
size_t	get_name_size(char *name);
void	ft_setenv(char *arg, t_list **env_l);
t_list	*ft_unsetenv(char *name, t_list *env_l);

void		cd(char **arg, t_list **env_l);
void	ft_exit(char **arg);
char **split_tab(char **tab, int i);

#endif
