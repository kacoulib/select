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

#include "ft_select.h"

/*
** Active the revese-video mode if the element is select
**
** @return TRUE on sucess otherwhise return FALSE
*/

int				active_highlight(t_select select)
{
	char		*tmp;

	if (select.is_select)
	{
		if (!(tmp = tgetstr("so", 0)))
			return (FALSE);
		tputs(tmp, 0, display_on_screen);
		if (!(tmp = tgetstr("mr", 0)))
			return (FALSE);
		tputs(tmp, 0, display_on_screen);
	}
	else
	{
		if (!(tmp = tgetstr("se", 0)))
			return (FALSE);
		tputs(tmp, 0, display_on_screen);
	}
	return (TRUE);
}

int				display_on_screen(int c)
{
	if (!write(1, &c, 1))
		return (0);
	return (TRUE);
}

/*
** Initialise the scren by
** 1. clear
** 2. change the terminal mode
** 3. hide the cursor
** 4. Position the cursor at the top and undeline the first element
**
** @return TRUE on sucess otherwhise return FALSE
*/

int				init_screen(t_select select[], t_term_info *t_info)
{
	char			*tmp;
	int				i;

	if (!(tmp = tgetstr("cl", 0)))
		return (FALSE);
	tputs(tmp, 0, display_on_screen);
	if (!(tmp = tgetstr("ti", 0)))
		return (FALSE);
	tputs(tmp, 0, display_on_screen);
	if (!(tmp = tgetstr("vi", 0)))
		return (FALSE);
	tputs(tmp, 0, display_on_screen);
	i = -1;
	while (++i < (t_info->select_len + 1))
		ft_putendl(select[i].content);
	if (!(tmp = tgetstr("cm", 0)))
		return (FALSE);
	toggle_underline(select, 0, 0);
	return (TRUE);
}

/*
** Toggle the selection on an element
** If the element was selected, deselect-it OR it was deselected, select-it
**
** @return TRUE on sucess otherwhise return FALSE
*/

int				toggle_underline(t_select select[], int index, int y_pos)
{
	char		*tmp;

	if (select[index].is_underline)
	{
		if (!(tmp = tgetstr("ue", 0)))
			return (FALSE);
		select[index].is_underline = FALSE;
	}
	else
	{
		if (!(tmp = tgetstr("us", 0)))
			return (FALSE);
		select[index].is_underline = TRUE;
	}
	tputs(tmp, 0, display_on_screen);
	if (!(tmp = tgetstr("cm", 0)))
		return (FALSE);
	tputs(tgoto(tmp, 0, y_pos), 0, display_on_screen);
	active_highlight(select[index]);
	ft_putstr(select[index].content);
	return (TRUE);
}
