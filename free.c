/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhaisne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/11 17:56:04 by jdhaisne          #+#    #+#             */
/*   Updated: 2016/04/16 17:55:19 by jdhaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_double_tab(char **tab)
{
	int i;

	i = 0;
	if (tab == NULL)
	{
		return ;
	}
	while (tab[i] != NULL)
	{
		ft_strdel(&tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

void	free_env(void *content, size_t size)
{
	char *str;

	str = (char *)content;
	ft_strdel(&str);
	content = NULL;
	str = NULL;
	size = 0;
}
