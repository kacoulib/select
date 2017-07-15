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

#include "../select.h"

int					color_select(void)
{
	char			*res;

	if (!(res = tgetstr("cl", NULL)))
		return (FALSE);
	return (FALSE);
}

int					reset_term(struct termios *term)
{
	char	*tmp;

	if (tcgetattr(0, term) == -1)
		return (FALSE);
	term->c_lflag = (ICANON | ECHO);
	if (tcsetattr(0, TCSADRAIN, term) < 0)
		return (FALSE);
	if (!(tmp = tgetstr("ve", 0))) // make cursor normal
		return (FALSE);
	tputs(tmp, 0, display_on_screen);
	return (TRUE);
}

int					read_term(t_select select[], int *len, int *nb_select)
{
	char			buff[PATH_MAX];
	char			*tmp;
	int				i;

	if (!(tmp = tgetstr("cl", 0))) // clear the screen
		return (FALSE);
	tputs(tmp, 0, display_on_screen);
	if (!(tmp = tgetstr("ti", 0)))
		return (FALSE);
	tputs(tmp, 0, display_on_screen);
	if (!(tmp = tgetstr("vi", 0))) // make cursor invisible
		return (FALSE);
	tputs(tmp, 0, display_on_screen);
	i = -1;
	while (++i < (*len + 1))
		printf("%s %d\n", select[i].content, i);
	if (!(tmp = tgetstr("cm", 0)))
		return (FALSE);
	tputs(tgoto(tmp, 0, 0), 0, display_on_screen);
	toggle_underline(select, 0);
	while (read(0, buff, PATH_MAX) > 0)
		if (!keyboard_events(buff, select, len, nb_select))
			break ;
	return (TRUE);
}

int					set_cannic_mode(struct termios *term)
{
	char			*term_name;
	char			*tmp;

	tmp = NULL;
	if (!(term_name = getenv("TERM")))
		return (FALSE);
	if (tgetent(TERM_BUFF, term_name) < 1)
		return (FALSE);
	if (tcgetattr(0, term) < 0)
		return (FALSE);
	term->c_lflag &= ~(ICANON | ECHO);
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, term) < 0)
		return (FALSE);
	return (TRUE);
}

int					main(int ac, char **av)
{
	t_select		select_list[arr_len((av[1] ? &av[1] : 0))];
	struct termios	*term;
	int				i;
	int				nb_select;

	if ((!av || ac == 1) || !(av = &av[1]))
		return (FALSE);
	if (!(term = malloc(sizeof(struct termios) + 1)))
		return (FALSE);
	if (!set_cannic_mode(term))
		return (FALSE);
	i = arr_len(av) - 1;
	nb_select = 0;
	ft_bzero(select_list, i);
	init_selection(av, select_list);
	read_term(select_list, &i, &nb_select);
	reset_term(term);
	delete_selection(&select_list[0]);
	return (FALSE);
}
