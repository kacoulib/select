/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/12 17:13:18 by kacoulib          #+#    #+#             */
/*   Updated: 2017/08/12 17:13:38 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int		move_last_part(t_term_info *t_info, t_select select[],
	int last_index)
{
	if (select[last_index].is_underline)
		toggle_underline(&select[last_index]);
	toggle_underline(&select[t_info->index]);
	t_info->last_pos = t_info->y_pos;
	return (TRUE);
}

/*
** Find the next index of the selection.
** If there's only one selection, return that one
**
** @param	direction : A char that should be D for (DOWN)
**			or somthing else for (UP)
** @return	The next index otherwhise -1 is returned
*/

int				move_cursor(t_term_info *t_info, t_select select[],
	char direction)
{
	int				last_index;
	int				stop;

	if (t_info->select_len == t_info->nb_deleted - 1)
		return (t_info->index);
	last_index = t_info->index;
	stop = 1;
	while (t_info->index != last_index || stop)
	{
		stop = 0;
		if (!select[last_index].is_show && select[t_info->index].is_show)
			last_index = t_info->index;
		if (direction == 'D')
			t_info->index = (t_info->index != t_info->select_len) ?
		t_info->index + 1 : 0;
		else
			t_info->index = (t_info->index != 0) ?
		t_info->index - 1 : t_info->select_len;
		if (select[t_info->index].is_show)
			break ;
	}
	return (move_last_part(t_info, select, last_index));
}
