/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 15:23:13 by kacoulib          #+#    #+#             */
/*   Updated: 2017/07/15 15:24:27 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Move the cursor one line below.
** Loop un until it found a line
**
** @return return FALSE if no line found else return true
*/

int					move_down(t_select select[], t_term_info *t_info)
{
	int				last_index;
	int				last_y_pos;
	int				stop;

	last_index = t_info->index;
	last_y_pos = t_info->y_pos;
	stop = 1;

	while (t_info->index != last_index || stop)
	{
		stop = 0;
		t_info->index = (t_info->index != t_info->select_len) ? t_info->index + 1 : 0;
		if (select[t_info->index].is_show)
			break;
	}
	t_info->y_pos = (t_info->y_pos != t_info->select_len) ? t_info->y_pos + 1 : 0;
	toggle_underline(select, last_index, last_y_pos);
	toggle_underline(select, t_info->index, t_info->y_pos);
	t_info->last_pos = t_info->y_pos;
	return (TRUE);
}

/*
** Move the cursor one line above.
** Loop un until it found a line
**
** @return return FALSE if no line found else return true
*/

int					move_up(t_select select[], t_term_info *t_info)
{
	int				last_index;
	int				last_y_pos;
	int				stop;

	last_index = t_info->index;
	last_y_pos = t_info->y_pos;
	stop = 1;

	while (t_info->index != last_index || stop)
	{
		stop = 0;
		t_info->index = (t_info->index != 0) ? t_info->index - 1: t_info->select_len;
		if (select[t_info->index].is_show)
			break;
	}
	t_info->y_pos = (t_info->y_pos != 0) ? t_info->y_pos - 1: t_info->select_len;
	toggle_underline(select, last_index, last_y_pos);
	toggle_underline(select, t_info->index, t_info->y_pos);
	t_info->last_pos = t_info->y_pos;
	return (TRUE);
}
