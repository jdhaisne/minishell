#include "minishell.h"

char	*clean(char *curpath)
{
	int i;
	int j;
	char	**tabpath;
	char *new;

	i = 0;
	new = ft_strnew(ft_strlen(curpath));
	tabpath = ft_strsplit(curpath, '/');
	while (tabpath[i] != NULL)
	{
		j = 1;
		if (ft_strequ(tabpath[i], "."))
			ft_strclr(tabpath[i]);
		else if(ft_strequ(tabpath[i], ".."))
		{
			ft_strclr(tabpath[i]);
			while (i - j >= 0 && ft_strlen(tabpath[i - j]) == 0)
				j++;
			ft_strclr(tabpath[i - j]);
		}
		i++;
	}
	i = 0;
			new= ft_strcat(new,"/"); 
	while(tabpath[i] != NULL)
	{
		if (ft_strlen(tabpath[i]) > 0 && i > 0 && ft_strlenrc(new, '/') > 0)
			new = ft_strcat(new,"/"); 
		new = ft_strcat(new, tabpath[i]);
		ft_strdel(&tabpath[i]);
		i++;
	}
	ft_putendl(new);
	return (new);
}

/*static void error(char *curpath)
{
	
}*/

void		cd(char **arg, t_list **env_l)
{
	char	*home;
	char	*curpath;
	char *pwd;
	int		i;
	//int		P;

	home = ft_envar("HOME", *env_l);
	i = 1;
	//P = 0;
	/*while(arg[i] != NULL && arg[i][0] == '-')
	  {
	  while (arg[i][
	  i++;
	  }*/
	if (arg[i] == NULL)
	{	if (home == NULL)
		ft_putendl("cd: HOME not set");
		else
			chdir(home);
		return;
	}
	else
	{
		if(arg[i][0] == '/')
			curpath = ft_strdup(arg[i]);
		else if(ft_strequ(arg[i], "-") == 1)
		{
			curpath = ft_strdup(ft_envar("OLDPWD", *env_l));
			ft_putendl(ft_envar("OLDPWD", *env_l));
		}
		else if (arg[i][0] == '.' && ft_strncmp(arg[i],"...", 3) != 0)
		{
			curpath = ft_strdup(ft_envar("PWD", *env_l));
			curpath = ft_stradd(curpath, "/");
			curpath = ft_stradd(curpath, arg[i]);
		}
		else if (arg[i][0] == '~')
		{
			curpath = ft_strdup(ft_envar("HOME", *env_l));
			curpath = ft_stradd(curpath, "/");
			curpath = ft_stradd(curpath, arg[i] + 1);
		}
		else
		{
			curpath = ft_strdup(ft_envar("PWD", *env_l));
			curpath = ft_stradd(curpath, "/");
			curpath = ft_stradd(curpath, arg[i]);
		}
	}
	curpath = clean(curpath);
	if (chdir(curpath) < 0)
	{
		ft_putendl(curpath);
		ft_putendl("cd: error");
		return;
	}
	pwd = ft_strjoin("OLDPWD=", ft_envar("PWD", *env_l));
	ft_setenv(pwd, env_l);
	ft_strdel(&pwd);
	pwd = ft_strjoin("PWD=", curpath);
	ft_setenv(pwd, env_l);
	ft_strdel(&pwd);
	ft_strdel(&curpath);
}
