	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 20:40:50 by kacoulib          #+#    #+#             */
/*   Updated: 2017/07/12 20:41:01 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int			arr_len(char **arr)
{
	int				i;

	if (!arr)
		return (0);
	i = -1;
	while (arr[++i])
		;
	return (i);
}

/*
** Delete the selection liste one by one
**
** @return a null
*/

t_select		*delete_selection(t_select *head)
{
	if (!head)
		return (NULL);
	return (head);
}

/*
** Create a liste of selection
**
** @return return the top head of created selection
*/

void		init_selection(char **av, t_select list[])
{
	int			i;

	i = -1;
	while (av[++i])
	{
		list[i].content = av[i];
		list[i].id = i;
		list[i].is_select = FALSE;
		list[i].is_underline = FALSE;
		list[i].is_show = TRUE;
	}
}
