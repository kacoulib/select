/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/14 04:48:24 by kacoulib          #+#    #+#             */
/*   Updated: 2017/07/14 04:48:36 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../select.h"

int					keycode_return(t_select select[], int len, int *nb_select)
{
	int				i;

	i = -1;
	while (++i < len)
	{
		if (select[i].is_select)
		{
			ft_putstr(select[i].content);
			if (--(*nb_select) > 0)
				ft_putstr(" ");
		}
	}
	ft_putchar('\n');
	return (0);
}

int					keycode_space(t_select select[], int *x_pos, int *nb_select,
	int *len)
{
	if (select[*x_pos].is_select && (select[*x_pos].is_select = FALSE))
		(*nb_select)--;
	else if ((select[*x_pos].is_select = TRUE))
		(*nb_select)++;
	move_down(select, x_pos, *x_pos, len);
	return (1);
}

int					keycode_esc(t_select select[], int len)
{
	int				i;

	if (!select)
		return (FALSE);
	i = -1;
	while (++i < len)
		if (select[i].is_select)
			ft_putstr(select[i].content);
	return (FALSE);
}

int					keycode_delete(t_select select[], int x_pos, int *len,
	int *nb_select)
{
	char			*tmp;

	tmp = tgetstr("cm", 0);
	tputs(tgoto(tmp, 0, x_pos), 0, display_on_screen);
	tmp = tgetstr("dl", 0);
	tputs(tgoto(tmp, 0, x_pos), 0, display_on_screen);
	select[x_pos].is_show = FALSE;
	if (select[x_pos].is_select)
	{
		select[x_pos].is_select = FALSE;
		(*nb_select)--;
	}
	(*len)--;
	return (TRUE);
}

int					keyboard_events(char keycode[], t_select select[], int *len,
	int *nb_select)
{
	int				lastpos;
	static int		x = 0;

	if (!keycode)
		return (FALSE);
	lastpos = x;
	if (keycode[0] == 27)
	{
		if (keycode[1] == 91 && keycode[2] == 70)
			return (keycode_esc(select, *len));
		if (keycode[2] == 65)
			return (move_up(select, &x, lastpos, len));
		if (keycode[2] == 66)
			return (move_down(select, &x, lastpos, len));
	}
	else if (keycode[0] == 127)
		keycode_delete(select, x, len, nb_select);
	else if (keycode[0] == 32)
		keycode_space(select, &x, nb_select, len);
	else if (keycode[0] == 13 || keycode[0] == 10)
		return (keycode_return(select, *len, nb_select));
	return (*len);
}
