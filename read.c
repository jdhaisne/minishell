/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhaisne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 15:48:10 by jdhaisne          #+#    #+#             */
/*   Updated: 2016/04/20 11:38:48 by jdhaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*clean_line(char *str)
{
	char	*str_ok;
	int		i;
	int		j;

	j = 0;
	i = 0;
	str_ok = ft_strnew(ft_strlen(str) + 1);
	while (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '\t')
		{
			str_ok[j] = ' ';
			j++;
			while (str[i] == ' ' || str[i] == '\t')
				i++;
		}
		str_ok[j] = str[i];
		j++;
		i++;
	}
	ft_strdel(&str);
	str_ok[j] = '\0';
	return (str_ok);
}

char	**read_line(t_list *env_l)
{
	char	*str;
	char	*str_ok;
	char	**tab;
	int		i;

	i = 0;
	get_next_line(0, &str);
	str_ok = ft_strtrim(str);
	str_ok = clean_line(str_ok);
	tab = ft_strsplit(str_ok, ' ');
	while (tab[i] != NULL)
	{
		if (ft_strequ(tab[i], "~"))
		{
			ft_strdel(&tab[i]);
			tab[i] = ft_strdup(ft_envar("HOME", env_l));
		}
		i++;
	}
	ft_strdel(&str);
	ft_strdel(&str_ok);
	return (tab);
}
