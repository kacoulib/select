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

#include "../ft_select.h"

int			arr_len(char **arr)
{
	int				i;

	if (!arr)
		return (0);
	i = -1;
	while (arr[++i])
		;
	return (i);
}

/*
** Delete the selection liste one by one
**
** @return a null
*/

t_select		*delete_selection(t_select *head)
{
	if (!head)
		return (NULL);
	return (head);
}

/*
** Create a liste of selection
**
** @return return the top head of created selection
*/

void		init_selection(char **av, t_select list[])
{
	int			i;

	i = -1;
	while (av[++i])
	{
		list[i].content = ft_strdup(av[i]);
		list[i].is_select = FALSE;
		list[i].is_underline = FALSE;
		list[i].is_show = TRUE;
	}
}

/*
**
**
** @return return the top head of created term_info
*/

t_term_info		*init_term_info(char **av)
{
	t_term_info		*new_term_info;


	if (!(new_term_info = malloc(sizeof(t_term_info) + 1)))
		return (NULL);
	new_term_info->index = 0;
	new_term_info->last_pos = 0;
	new_term_info->nb_select = 0;
	new_term_info->select_len = arr_len(av) - 1;
	new_term_info->x_pos = 0;
	new_term_info->y_pos = 0;
	return (new_term_info);
}
