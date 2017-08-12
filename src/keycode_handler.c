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

#include "ft_select.h"

/*
** Undo the last removed element
** Find the last index in t_info->ctr_z that is different from -1
*/

static int			undo_selection(t_term_info *t_info, t_select select[])
{
	int				i;
	int				j;

	i = t_info->select_len;
	while (t_info->ctr_z[i] == -1 && i > 0)
		i--;
	j = t_info->ctr_z[i];
	if (!select[j].is_show)
	{
		select[j].is_show = TRUE;
		t_info->nb_deleted--;
		t_info->ctr_z[i] = -1;
		t_info->index = j;
		select[j].is_underline = TRUE;
	}
	display_all_elem(t_info, select);
	return (1);
}

static int			keycode_space(t_select select[], t_term_info *t_info)
{
	// if (select[t_info->index].is_select)
	// 	printf("%s %d\n", select[t_info->index].content, select[t_info->index].x_pos);
	if (select[t_info->index].is_select)
	{
		if (!(select[t_info->index].is_select = FALSE))
			t_info->nb_select--;
	}
	else if ((select[t_info->index].is_select = TRUE))
		t_info->nb_select++;
	return (move_cursor(t_info, select, 'D'));
}

static int			keycode_delete(t_select select[], t_term_info *t_info)
{
	int				i;

	if (!select[t_info->index].content)
		return (FALSE);
	select[t_info->index].is_show = FALSE;
	if (select[t_info->index].is_select)
	{
		select[t_info->index].is_select = FALSE;
		t_info->nb_select--;
	}
	i = 0;
	while (t_info->ctr_z[i] != -1 && i < t_info->select_len)
		i++;
	select[t_info->index].is_underline = TRUE;
	t_info->ctr_z[i] = t_info->index;
	display_all_elem(t_info, select);
	if (t_info->nb_deleted++ == t_info->select_len)
		return (FALSE);
	return (move_cursor(t_info, select, 'D'));
}

int				keyboard_events(char keycode[], t_select select[],
	t_term_info *t_info)
{
	if (!keycode)
		return (FALSE);
	if (keycode[0] == 27)
	{
		if (keycode[2] == 66)
			return (move_cursor(t_info, select, 'D'));
		else if (keycode[2] == 65)
			return (move_cursor(t_info, select, 'U'));
		else
			return (0);
	}
	else if (keycode[0] == 127)
		return (keycode_delete(select, t_info));
	else if (keycode[0] == 32)
		keycode_space(select, t_info);
	else if (keycode[0] == 13 || keycode[0] == 10)
		return (0);
	else if (keycode[0] == 24 || keycode[0] == 18)
		return (undo_selection(t_info, select));
	return (1);
}
