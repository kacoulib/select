/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 10:08:30 by kacoulib          #+#    #+#             */
/*   Updated: 2017/09/29 10:08:46 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int					update_screen_info_last_part(t_term_info *t_info)
{
	char					*tmp;
	int						x;

	x = (t_info->width / 2) - 16;
	tputs(tmp, 0, tputs_display_function);
	if (!(tmp = tgetstr("cm", 0)))
		return (FALSE);
	tputs(tgoto(tmp, x - 1, t_info->height / 2), 0, tputs_display_function);
	ft_putendl("Sorry but the screen is too small");
	t_info->is_win_size_ok = FALSE;
	return (FALSE);
}

int							update_screen_info(void)
{
	int						i;
	struct winsize			w;
	t_term_info				*t_info;

	t_info = get_or_init_term(NULL, NULL);
	if (ioctl(2, TIOCGWINSZ, &w) != 0)
		return (FALSE);
	i = t_info->select_len - t_info->nb_deleted;
	t_info->height = w.ws_row;
	t_info->width = w.ws_col;
	if (i >= w.ws_row || t_info->col_space > t_info->width)
	{
		t_info->nb_col = w.ws_col / t_info->col_space;
		i = (t_info->nb_col) ? (i / t_info->nb_col) : i;
		if (i >= w.ws_row || t_info->col_space > t_info->width)
			return (update_screen_info_last_part(t_info));
	}
	t_info->is_win_size_ok = TRUE;
	return (TRUE);
}
