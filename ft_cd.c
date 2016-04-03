#include "minishell.h"

static char	*get_home_path(t_list *env_l)
{
	char	*home_path;

	while(env_l != NULL && ft_strncmp(env_l->content, "HOME", 4) != 0)
		env_l = env_l->next;
	if (env_l == NULL)
		return (NULL);
	home_path = ft_strchr(env_l->content, '=');
	return (++home_path);
}

void		cd(char **arg, t_list *env_l)
{
	char	*home;
	char	*curpath;
	int		i;
	int		P;

	home = get_home_path(env_l);
	i = 1;
	/*while(arg[i] != NULL && arg[i][0] == '-')
	{
		while (arg[i][
		i++;
	}*/
	if (arg[i] == NULL)
	{

	}
	else
	{
		if(arg[i][0] == '/')
			curpath = ftstrdup(arg[i]);
	}
}
