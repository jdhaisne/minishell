/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhaisne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 15:48:10 by jdhaisne          #+#    #+#             */
/*   Updated: 2016/04/07 12:27:48 by jdhaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

char	**read_line(void)
{
	char *str;
	char *str_ok;
	int i;
	int j;

	i = 0;
	j = 0;
	get_next_line(0, &str);
	str = ft_strtrim(str);
	str_ok = str;
	return (ft_strsplit(str_ok, ' '));
}
