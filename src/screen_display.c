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

static int		active_highlight(t_select select)
{
	char		*tmp;

	if (select.is_select)
	{
		if (!(tmp = tgetstr("so", 0)))
			return (FALSE);
		tputs(tmp, 1, tputs_display_function);
		if (!(tmp = tgetstr("mr", 0)))
			return (FALSE);
		tputs(tmp, 1, tputs_display_function);
	}
	else
	{
		if (!(tmp = tgetstr("se", 0)))
			return (FALSE);
		tputs(tmp, 1, tputs_display_function);
	}
	return (TRUE);
}

static int		display_single_elem(t_select select)
{
	t_term_info *term;
	char		*tmp;

	if (!select.is_show)
		return (FALSE);
	term = get_or_init_term(NULL, NULL);
	if (!(tmp = tgetstr("cm", 0)))
		return (FALSE);
	tputs(tgoto(tmp, select.x_pos, select.y_pos), 0, tputs_display_function);
	active_highlight(select);
	ft_put_file_name(select.content, select.type);
	return (TRUE);
}

/*
** Initialise the scren by
** 0. Remove the underline
** 1. Clear
** 2. Print all selection on the screen
** 3. Underline the current element
**
** @return TRUE on sucess otherwhise return FALSE
*/

int				display_all_elem(void)
{
	char		*tmp;
	int			i;
	t_term_info	*t_info;

	t_info = get_or_init_term(NULL, NULL);
	if (!(tmp = tgetstr("ue", 0)))
		return (FALSE);
	tputs(tmp, 1, tputs_display_function);
	if (!(tmp = tgetstr("cl", 0)))
		return (FALSE);
	tputs(tmp, 1, tputs_display_function);
	if (!update_screen_info())
		return (FALSE);
	update_selection(t_info, t_info->select);
	i = -1;
	while (++i < (t_info->select_len + 1))
		display_single_elem(t_info->select[i]);
	toggle_underline(&t_info->select[t_info->index]);
	if (!(tmp = tgetstr("ue", 0)))
		return (FALSE);
	tputs(tmp, 1, tputs_display_function);
	return (TRUE);
}

/*
** Toggle the selection on an element
** If the element was selected, deselect-it OR it was deselected, select-it
**
** @return TRUE on sucess otherwhise return FALSE
*/

int				toggle_underline(t_select *select)
{
	char		*tmp;

	if (!select->is_show)
		return (FALSE);
	if (select->is_underline)
	{
		if (!(tmp = tgetstr("ue", 0)))
			return (FALSE);
		select->is_underline = FALSE;
	}
	else
	{
		if (!(tmp = tgetstr("us", 0)))
			return (FALSE);
		select->is_underline = TRUE;
	}
	tputs(tmp, 1, tputs_display_function);
	return (display_single_elem(*select));
}

int				tputs_display_function(int c)
{
	if (!write(isatty(STDOUT_FILENO), &c, 1))
		return (0);
	return (TRUE);
}
