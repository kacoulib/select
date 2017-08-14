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

static int			ft_putstr_space_caracter(char *str)
{
	int				i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ')
			write(1, "\\ ", 2);
		else
			write(1, &str[i], 1);
	}
	return (TRUE);
}

static int			display_result(t_select select[], t_term_info *term_info)
{
	int				i;

	if (!term_info->nb_select)
		return (0);
	i = -1;
	while (++i < term_info->select_len + 1)
	{
		if (select[i].is_select)
		{
			if (strchr(select[i].content, ' '))
				ft_putstr_space_caracter(select[i].content);
			else
				ft_putstr(select[i].content);
			if (--(term_info->nb_select) > 0)
				ft_putstr(" ");
		}
	}
	ft_putchar('\n');
	return (1);
}

static int			read_term(t_select select[], t_term_info *t_info)
{
	char			buff[PATH_MAX];
	char			*tmp;

	if (!(tmp = tgetstr("ti", 0)))
		return (FALSE);
	tputs(tmp, 0, tputs_display_function);
	if (!(tmp = tgetstr("vi", 0)))
		return (FALSE);
	tputs(tmp, 0, tputs_display_function);
	display_all_elem();
	while (read(0, buff, PATH_MAX) > 0)
	{
		if (t_info->is_win_size_ok)
			if (!keyboard_events(buff, select, t_info))
				break ;
	}
	return (reset_term(get_terminal()));
}

int					main(int ac, char **av)
{
	t_select		select_list[arr_len((av[1] ? &av[1] : 0))];
	int				ctr_z[arr_len((av[1] ? &av[1] : 0))];
	t_term_info		*t_info;
	struct termios	*term;

	if ((!av || ac == 1) || !(av = &av[1]))
		return (FALSE);
	term = get_terminal();
	if (!set_cannic_mode(term))
		return (FALSE);
	if (!(t_info = get_or_init_term(av, term)))
		return (FALSE);
	ft_bzero(ctr_z, t_info->select_len);
	t_info->ctr_z = ctr_z;
	ft_bzero(select_list, t_info->select_len);
	init_selection(av, select_list, t_info);
	signal_handler();
	read_term(select_list, t_info);
	display_result(select_list, t_info);
	return (FALSE);
}
