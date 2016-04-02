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
	char *home;
	home = get_home_path(env_l);
	if(arg[1] == NULL)
	{
		if (home != NULL)
			chdir(home);
		else
		ft_putendl("cd: HOME not set");
	}
	else if(arg[2] == NULL)
	{
		if (arg[1][1] === '~')
			chdir(home);
		chdir(arg[1]);

	}
}
