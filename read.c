/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhaisne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 15:48:10 by jdhaisne          #+#    #+#             */
/*   Updated: 2016/04/13 15:38:35 by jdhaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

char	**read_line(t_list *env_l)
{
	char *str;
	char *str_ok;
	char **tab;
	int i;

	i = 0;
	get_next_line(0, &str);
	str = ft_strtrim(str);
	str_ok = str;
	tab = ft_strsplit(str_ok, ' ');
	while(tab[i] != NULL)
	{
		if(ft_strequ(tab[i], "~"))
		{
			ft_strdel(&tab[i]);
			tab[i] = ft_strdup(ft_envar("HOME", env_l));
		}
		i++;
	}
	return (tab);
}
