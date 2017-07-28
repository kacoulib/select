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

#include "../ft_select.h"

int					display_result(t_select select[], t_term_info *term_info)
{
	int				i;
	char			*tmp;

	if (!term_info->nb_select)
		return (0);
	if (!(tmp = tgetstr("cm", 0)))
		return (FALSE);
	tputs(tgoto(tmp, 0, term_info->select_len + 1), 0, display_on_screen);
	i = -1;
	while (++i < term_info->select_len + 1)
	{
		if (select[i].is_select)
		{
			ft_putstr(select[i].content);
			if (--(term_info->nb_select) > 0)
				ft_putstr(" ");
		}
	}
	ft_putchar('\n');
	return (1);
}

int					keycode_space(t_select select[], t_term_info *t_info)
{
	if (select[t_info->y_pos].is_select && !(select[t_info->y_pos].is_select = FALSE))
		t_info->nb_select--;
	else if ((select[t_info->y_pos].is_select = TRUE))
		t_info->nb_select++;
	move_down(select, t_info);
	return (1);
}

int					keycode_delete(t_select select[], t_term_info *t_info)
{
	char			*tmp;

	tmp = tgetstr("cm", 0);
	tputs(tgoto(tmp, 0, t_info->y_pos), 0, display_on_screen);
	tmp = tgetstr("dl", 0);
	tputs(tgoto(tmp, 0, t_info->y_pos), 0, display_on_screen);
	select[t_info->y_pos].is_show = FALSE;
	if (select[t_info->y_pos].is_select)
	{
		select[t_info->y_pos].is_select = FALSE;
		t_info->nb_select--;
	}
	t_info->select_len--;
	return (TRUE);
}

int					keyboard_events(char keycode[], t_select select[], t_term_info *t_info)
{
	if (!keycode)
		return (FALSE);

	if (keycode[0] == 27)
	{
		if (keycode[2] == 66)
			return (move_down(select, t_info));
		else if (keycode[2] == 65)
			return (move_up(select, t_info));
		else
			return (0);
	}
	else if (keycode[0] == 127)
		keycode_delete(select, t_info);
	else if (keycode[0] == 32)
		keycode_space(select, t_info);
	else if (keycode[0] == 13 || keycode[0] == 10)
		return (0);
	return (1);
}
