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

int					keyCode_space(t_select select[], int x_pos)
{
	char			*tmp;

	// ft_putendl(ANSI_COLOR_CYAN);
	// ft_putendl(select[x_pos].content);
	// ft_putendl(ANSI_COLOR_RESET);
	// select = NULL;
	if (select)
		;
	if (!(tmp = tgetstr("so", 0)))
		return (FALSE);
	tputs(tmp, 0, display_on_screen);
	if (!(tmp = tgetstr("se", 0)))
		return (FALSE);
	tputs(tmp, 0, display_on_screen);
	return (x_pos);
}
int					keyCode_esc(t_select select[], int len)
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

int					keyCode_ctr(t_select select[], int x_pos, int lastpos)
{
	char			*tmp;

	if (!(tmp = tgetstr("ue", 0)))
		return (FALSE);
	tputs(tmp, 0, display_on_screen);
	if (!(tmp = tgetstr("cm", 0)))
		return (FALSE);
	tputs(tgoto(tmp, 0, lastpos), 1, display_on_screen);
	ft_putstr(select[lastpos].content);
	tputs(tgoto(tmp, 0, x_pos), 1, display_on_screen);
	if (!(tmp = tgetstr("us", 0)))
		return (FALSE);
	tputs(tmp, 0, display_on_screen);
	ft_putendl(select[x_pos].content);
	return (TRUE);	
}

int					keyCode_delete(char keyCode[], t_select select[], int x_pos)
{
	char			*tmp;

	if (!keyCode)
		return (FALSE);
	select = NULL; // to remove
	if (keyCode[0] == 127 && keyCode[1] == 91 && keyCode[2] == 66)
	{
		tmp = tgetstr("dl", 0);
		tputs(tgoto(tmp, 0, x_pos), 0, display_on_screen);
	}
	return (TRUE);
}

int					keyboard_events(char keyCode[], t_select select[], int len)
{
	int				lastpos;
	static int		x = 0;

	if (!keyCode)
		return (FALSE);
	// printf("%d\n", x);
	if (keyCode[0] == 27)
	{
		if (keyCode[1] == 91 && keyCode[2] == 70)
			return (keyCode_esc(select, len));
		lastpos = x;
		if (keyCode[2] == 65)
			x = (x > 0) ? x - 1 : len;
		if (keyCode[2] == 66)
			x = (x < len) ? x + 1 : 0;
		keyCode_ctr(select, x, lastpos);
	}
	else if (keyCode[0] == 127)
		keyCode_delete(keyCode, select, x);
	else if (keyCode[0] == 32)
		keyCode_space(select, x);
	return (TRUE);
}
