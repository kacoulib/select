/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 19:25:19 by kacoulib          #+#    #+#             */
/*   Updated: 2017/07/12 19:25:48 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../select.h"


int				active_highlight(t_select select[], int x_pos)
{
	char		*tmp;

	if (select[x_pos].is_select)
	{
		if (!(tmp = tgetstr("so", 0))) // activate standout mode
			return (FALSE);
		tputs(tmp, 0, display_on_screen);
		if (!(tmp = tgetstr("mr", 0))) // reverse video
			return (FALSE);
		tputs(tmp, 0, display_on_screen);
		ft_putstr(select[x_pos].content);
	}
	// tputs(tgoto(tmp, 0, x_pos), 0, display_on_screen);
	// ft_putstr(select[x_pos].content);
	if (!(tmp = tgetstr("se", 0))) // desactivate standout mode
		return (FALSE);
	tputs(tmp, 0, display_on_screen);
	return (1);
}

int					display_on_screen(int c)
{
	if (!write(1, &c, 1))
		return (0);
	return (1);
}

int					display_with_video_mode(t_select select[], int *x_pos,
	int lastpos, int *len)
{
	char			*tmp;

	if (!(tmp = tgetstr("so", 0))) // activate standout mode
		return (FALSE);
	tputs(tmp, 0, display_on_screen);
	if (!(tmp = tgetstr("mr", 0))) // reverse video
		return (FALSE);
	tputs(tmp, 0, display_on_screen);
	ft_putstr(select[*x_pos].content);
	if (!(tmp = tgetstr("se", 0))) // desactivate standout mode
		return (FALSE);
	tputs(tmp, 0, display_on_screen);
	return (move_up(select, x_pos, lastpos, len));
}

int				toggle_underline(t_select select[], int x_pos)
{
	char		*tmp;

	if (select[x_pos].is_underline)
	{
		if (!(tmp = tgetstr("ue", 0)))
			return (FALSE);
		select[x_pos].is_underline = FALSE;
	}
	else
	{
		if (!(tmp = tgetstr("us", 0)))
			return (FALSE);
		select[x_pos].is_underline = TRUE;
	}
	tputs(tgoto(tmp, 0, x_pos), 0, display_on_screen);
	active_highlight(select, x_pos);
	ft_putstr(select[x_pos].content);
	return (1);
}
