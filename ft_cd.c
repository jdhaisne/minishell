#include "minishell.h"

int		is_link(char **tab, int i, char **tmp)
{
	struct stat buf;
	char *path;
	int j;

	path = ft_strdup("/");
	path = ft_stradd(path, tab[0]);
	j = 1;
	while (j <= i && ft_strlen(tab[j]) > 0)
	{
		path = ft_stradd(path, "/");
		path = ft_stradd(path, tab[j]);
		j++;
	}
	lstat(path, &buf);
	ft_putendl(path);
	if ((buf.st_mode & S_IFMT) != S_IFLNK)
		return (0);
	ft_putendl("B");
	*tmp = ft_strnew(buf.st_size + 1);
	*tmp[readlink(path, *tmp, buf.st_size + 1)] = '\0';
	ft_putendl(*tmp);
	return (1);
}

char	*clean(char *curpath, int P)
{
	int		i;
	int		j;
	char	**tabpath;
	char	*new;
	char	*tmp;

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
		else if(is_link(tabpath, i, &tmp) == 1 && P == 1)
		{
			ft_strdel(&tabpath[i]);
			tabpath[i] = ft_strdup(tmp);
			ft_strdel(&tmp);
		}
		ft_putendl(tabpath[i]);
		i++;
	}
	i = 0;
	new= ft_strcat(new,"/"); 
	while(tabpath[i] != NULL)
	{
		if (ft_strlen(tabpath[i]) > 0 && i > 0 && ft_strlenrc(new, '/') > 0)
			new = ft_stradd(new,"/"); 
		new = ft_stradd(new, tabpath[i]);
		ft_strdel(&tabpath[i]);
		i++;
	}
	ft_putendl(new);
	return (new);
}

/*static void error(char *curpath)
  {

  }*/

static int	is_option(char *arg, int *P)
{
	int i;

	i = 1;
	if (arg[0] != '-')
		return (0);
	if (arg[1] == '\0')
		return (0);
	while (arg[i] != '\0')
	{
		if (arg[i] == 'P')
			*P = 1;
		else if (arg[i] == 'L')
			*P = 0;
		else
		{
			*P = 0;
			return (0);
		}
		i++;
	}
	return (1);
}

char		*cd_r(char **tab, char *arg1, char *arg2)
{
	int		i;
	int		a;
	char	*curpath;

	i = 0;
	a = 0;
	curpath = ft_strdup("");
	if (ft_strequ(arg1, "/"))
		return (ft_strdup(arg2));
	while(tab[i] != NULL)
	{
		curpath = ft_stradd(curpath, "/");
		if(ft_strequ(tab[i], arg1) && a == 0)
		{
			curpath = ft_stradd(curpath, arg2);
			a = 1;
		}
		else
			curpath = ft_stradd(curpath, tab[i]);
		i++;
	}
	ft_putendl(curpath);
	if (a == 0)
		return (NULL);
	return (curpath);
}

void		cd(char **arg, t_list **env_l)
{
	char	*home;
	char	*curpath;
	char	*pwd;
	int		i;
	int		P;

	home = ft_envar("HOME", *env_l);
	pwd = getcwd(NULL, 0);
	i = 1;
	P = 0;
	while(arg[i] != NULL && is_option(arg[i], &P))
		i++;
	if (arg[i] == NULL)
	{
		if (home == NULL)
			ft_putendl("cd: HOME not set");
		else
			chdir(home);
		return;
	}
	else
	{
		if (arg[i + 1] != NULL)
		{
			curpath = cd_r(ft_strsplit(pwd, '/'), arg[i], arg[i +1]);
			if (curpath == NULL)
			{
				ft_putstr("cd: string not in pwd: ");
				ft_putendl(arg[i]);
				return;
			}
		}
		else if(arg[i][0] == '/')
			curpath = ft_strdup(arg[i]);
		else if(ft_strequ(arg[i], "-") == 1)
		{
			if(ft_envar("OLDPWD", *env_l) == NULL)
			{
				ft_putendl("cd: OLDPWD not set");
				return ;
			}
			curpath = ft_strdup(ft_envar("OLDPWD", *env_l));
			ft_putendl(ft_envar("OLDPWD", *env_l));
		}
		else if (arg[i][0] == '.' && ft_strncmp(arg[i],"...", 3) != 0)
		{
			curpath = ft_strdup(getcwd(NULL, 0));
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
			curpath = ft_strdup(getcwd(NULL, 0));
			curpath = ft_stradd(curpath, "/");
			curpath = ft_stradd(curpath, arg[i]);
		}
	}
	curpath = clean(curpath , P);
	if (chdir(curpath) < 0)
	{
		ft_putendl(curpath);
		ft_putendl("cd: error");
		return;
	}
	pwd = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
	ft_setenv(pwd, env_l);
	ft_strdel(&pwd);
	pwd = ft_strjoin("PWD=", curpath);
	ft_setenv(pwd, env_l);
	ft_strdel(&pwd);
	ft_strdel(&curpath);
}
