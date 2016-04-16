/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhaisne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 15:48:10 by jdhaisne          #+#    #+#             */
/*   Updated: 2016/04/16 18:00:17 by jdhaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**read_line(t_list *env_l)
{
	char	*str;
	char	*str_ok;
	char	**tab;
	int		i;

	i = 0;
	get_next_line(0, &str);
	str_ok = ft_strtrim(str);
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
