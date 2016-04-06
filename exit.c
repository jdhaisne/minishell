/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhaisne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 11:35:40 by jdhaisne          #+#    #+#             */
/*   Updated: 2016/04/06 11:39:48 by jdhaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **arg)
{
	if(arg[1] == NULL)
		exit(0);
	if(arg[2] == NULL)
		exit(ft_atoi(arg[1]));
	ft_putendl("exit: too many arguments");
}
