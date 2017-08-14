/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 20:40:50 by kacoulib          #+#    #+#             */
/*   Updated: 2017/07/12 20:41:01 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int				arr_len(char **arr)
{
	int			i;

	if (!arr)
		return (0);
	i = -1;
	while (arr[++i])
		;
	return (i);
}

static void		set_file_type(t_select *select)
{
	struct stat sb;

	select->type = 0;
	if ((lstat(select->content, &sb) != -1) ||
		(stat(select->content, &sb) != -1))
	{
		if (S_ISLNK(sb.st_mode))
			select->type = 2;
		else if (sb.st_mode & S_ISVTX)
			select->type = 4;
		else if (!S_ISDIR(sb.st_mode) && sb.st_mode & S_IXUSR)
			select->type = 3;
		else
			select->type = 1;
	}
}

/*
** Create a liste of selection
*/

void			init_selection(char **av, t_select select[],
	t_term_info *t_info)
{
	int			i;

	i = -1;
	while (av[++i])
	{
		select[i].content = av[i];
		select[i].id = i;
		select[i].x_pos = 0;
		select[i].y_pos = 0;
		select[i].is_select = FALSE;
		select[i].is_underline = FALSE;
		select[i].is_show = TRUE;
		t_info->ctr_z[i] = -1;
		set_file_type(&select[i]);
	}
	t_info->select = select;
}

/*
** update the selection list
*/

void			update_selection(t_term_info *t_info, t_select select[])
{
	int			i;
	int			x;
	int			z;

	i = -1;
	x = 0;
	z = -1;
	while (++i < (t_info->select_len + 1))
	{
		if (select[i].is_show)
		{
			z++;
			if (z >= t_info->height)
				x = z / t_info->height;
			select[i].x_pos = t_info->col_space * x;
			select[i].y_pos = (z - (t_info->height * x));
		}
	}
}
