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
*/

void		init_selection(char **av, t_select list[], t_term_info *t_info)
{
	int			i;

	i = -1;
	while (av[++i])
	{
		list[i].content = av[i];
		list[i].id = i;
		list[i].x_pos = 0;
		list[i].y_pos = 0;
		list[i].is_select = FALSE;
		list[i].is_underline = FALSE;
		list[i].is_show = TRUE;
		t_info->ctr_z[i] = -1;
	}
}

/*
** update a liste of selection
*/

void		update_selection(t_term_info *t_info, t_select list[])
{
	int			i;
	int			x;
	int			y;

	i = -1;
	x = 0;
	y = 0;
	update_screen_info();
	while (++i < (t_info->select_len + 1))
	{
		y = list[i].id;
		if (list[i].id > t_info->height)
			x = list[i].id / t_info->height;
		if (x > 0)
		y = (y - (t_info->height * x)) - 1;
		list[i].x_pos = t_info->col_space * x;
		list[i].y_pos = y;
	}
}
