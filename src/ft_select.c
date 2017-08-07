/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 14:36:16 by kacoulib          #+#    #+#             */
/*   Updated: 2017/07/11 14:36:32 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"


int					read_term(t_select select[], t_term_info *t_info)
{
	char			buff[PATH_MAX];

	init_screen(select, t_info);
	while (read(0, buff, PATH_MAX) > 0)
	{
		if (!keyboard_events(buff, select, t_info))
		{
			break;
		}
	}
	return (reset_term(get_terminal()));
}

int					main(int ac, char **av)
{
	t_select		select_list[arr_len((av[1] ? &av[1] : 0))];
	struct termios	*term;
	t_term_info		*t_info;

	if ((!av || ac == 1) || !(av = &av[1]))
		return (FALSE);
	term = get_terminal();
	if (!set_cannic_mode(term))
		return (FALSE);
	if (!(t_info = get_or_init_term(av, term)))
		return (FALSE);
	ft_bzero(select_list, t_info->select_len);
	init_selection(av, select_list);
	signal_handler();
	read_term(select_list, t_info);
	display_result(select_list, t_info);
	return (FALSE);
}
