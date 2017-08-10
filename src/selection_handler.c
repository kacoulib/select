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

int				arr_len(char **arr)
{
	int			i;

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

void			init_selection(char **av, t_select select[], t_term_info *t_info)
{
	int			i;

	i = -1;
	while (av[++i])
	{
		select[i].content = av[i];
		select[i].id = i;
		select[i].x_pos = 0;
		select[i].y_pos = 0;
		select[i].is_select = FALSE;
		select[i].is_underline = FALSE;
		select[i].is_show = TRUE;
		t_info->ctr_z[i] = -1;
	}
}

/*
** update a liste of selection
*/

void			update_selection(t_term_info *t_info, t_select select[])
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
		y = select[i].id;
		if (select[i].id > t_info->height)
			x = select[i].id / t_info->height;
		if (x > 0)
		y = (y - (t_info->height * x)) - 1;
		select[i].x_pos = t_info->col_space * x;
		select[i].y_pos = y;
	}
}
/*
** Find the next index of the selection.
** If there's only one selection, return that one
**
** @param	direction : A char that should be D for (DOWN) or somthing else for (UP)
** @return	The next index otherwhise -1 is returned
*/

int				move_cursor(t_term_info *t_info, t_select select[], char direction)
{
	int				last_index;
	int				stop;

	if (t_info->select_len == t_info->nb_deleted)
		return (t_info->index);
	last_index = t_info->index;
	stop = 1;
	while (t_info->index != last_index || stop)
	{
		stop = 0;
		if (!select[last_index].is_show && select[t_info->index].is_show)
			last_index = t_info->index;
		if (direction == 'D')
			t_info->index = (t_info->index != t_info->select_len) ? t_info->index + 1 : 0;
		else
			t_info->index = (t_info->index != 0) ? t_info->index - 1: t_info->select_len;
		if (select[t_info->index].is_show)
			break;
	}
	if (select[last_index].is_underline)
		toggle_underline(&select[last_index]);
	toggle_underline(&select[t_info->index]);
	t_info->last_pos = t_info->y_pos;
	return (TRUE);
}


