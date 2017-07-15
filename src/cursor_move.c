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

#include "../select.h"

int					underline_and_deplace(t_select select[], int x_pos,
	int lastpos)
{
	char			*tmp;

	if (!(tmp = tgetstr("cm", 0)))
		return (FALSE);
	tputs(tgoto(tmp, 0, lastpos), 0, display_on_screen);
	toggle_underline(select, lastpos);
	tputs(tgoto(tmp, 0, x_pos), 0, display_on_screen);
	toggle_underline(select, x_pos);
	return (TRUE);
}

/*
** Move the cursor one line below.
** Loop un until he found a line
**
** @return return FALSE if no line found else return true
*/

int					move_down(t_select select[], int *x_pos, int lastpos,
	int *len)
{
	int				start_index;

	*x_pos = (*x_pos < *len) ? *x_pos : -1;
	start_index = *x_pos;
	while (*x_pos < *len)
	{
		(*x_pos)++;
		if (*x_pos == start_index)
			return (0);
		if (select[*x_pos].is_show)
			return (underline_and_deplace(select, *x_pos, lastpos));
	}
	return (0);
}

/*
** Move the cursor one line above.
** Loop un until he found a line
**
** @return return FALSE if no line found else return true
*/

int					move_up(t_select select[], int *x_pos, int lastpos,
	int *len)
{
	int				start_index;

	*x_pos = (*x_pos > 0) ? *x_pos : *len + 1;
	start_index = *x_pos;
	while (*x_pos < (*len + 2) && *len)
	{
		(*x_pos)--;
		if (*x_pos == start_index)
			return (0);
		if (select[*x_pos].is_show)
			return (underline_and_deplace(select, *x_pos, lastpos));
	}
	return (0);
}
