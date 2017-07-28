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

#include "../ft_select.h"

/*
** Show the slect element underline if not selected otherwise de-select it.
**
** @return return FALSE if no line found else return true
*/

int					underline_and_deplace(t_select select[], t_term_info *t_info)
{
	toggle_underline(select, t_info->last_pos);
	toggle_underline(select, t_info->index);
	t_info->last_pos = t_info->index;
	return (TRUE);
}

/*
** Move the cursor one line below.
** Loop un until it found a line
**
** @return return FALSE if no line found else return true
*/

int					move_down(t_select select[], t_term_info *t_info)
{
	int				start_index;

	t_info->y_pos = (t_info->y_pos < t_info->select_len) ? t_info->y_pos : -1;
	start_index = t_info->y_pos;
	while (t_info->y_pos < t_info->select_len)
	{
		t_info->y_pos++;
		if (t_info->y_pos == start_index)
			return (FALSE);
		if (select[t_info->y_pos].is_show && (t_info->index = t_info->y_pos))
			return (underline_and_deplace(select, t_info));
	}
	return (FALSE);
}

/*
** Move the cursor one line above.
** Loop un until it found a line
**
** @return return FALSE if no line found else return true
*/

int					move_up(t_select select[], t_term_info *t_info)
{
	int				i;
	int				start_index;

	t_info->y_pos = (t_info->y_pos > 0) ? t_info->y_pos : t_info->select_len + 1;
	start_index = t_info->y_pos;
	i = -1;
	while (++i < t_info->select_len)
	{
	printf("\t\t\t\t\t\t\t%d %d %d\n", t_info->last_pos, t_info->index, i);
		t_info->y_pos--;
		// if (t_info->y_pos == start_index)
		// 	return (FALSE);
		// if (t_info->y_pos == 0)
		// 	t_info->y_pos = t_info->select_len;
		if (select[t_info->y_pos].is_show && (t_info->index = t_info->y_pos))
			return (underline_and_deplace(select, t_info));
	}
	return (FALSE);
}
