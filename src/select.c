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

int					color_select()
{
	char	*res;

	if (!(res = tgetstr("cl", NULL)))
		return (FALSE);
	return (FALSE);
}

int					reset_term(struct termios *term)
{
	if (tcgetattr(0, term) == -1)
		return (FALSE);
	term->c_lflag = (ICANON | ECHO);
	if (tcsetattr(0, 0, term) == -1)
		return (FALSE);
	return (FALSE);
}

int					read_term(t_select select[], int select_len)
{
	char			buff[PATH_MAX];
	char			*res;
	int				i;
	// int				num;
	// struct winsize w;

	res = tgetstr("cl", 0);
	tputs(res, 0, display_on_screen);
	i = -1;
	while (++i < select_len)
		ft_putendl(select[i].content);
	while (read(0, buff, PATH_MAX) > 0)
	{
		// printf("%c", buff[0]);
		if (buff[0] == 27)
		{
			res = NULL;
			// if (buff[2] == 65)
			// {
			// 	res = tgetstr("cm", 0);
			// 	tputs(tgoto(res, 12, 13), 1, display_on_screen);
			// }
			// else if (buff[2] == 66)
			// {
			// 	res = tgetstr("ll", 0);
			// 	tputs(tgoto(res, 0, 0), 1, display_on_screen);
			// 	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
			// 	// printf("(window size = %d %d)\n", w.ws_col, tgetnum("co"));
			// }
			// else
			
			keyboard_events(buff, select, select_len - 1);
		}
		// else if (buff[0] == 4)
		// 	printf("_ctr+d_");
		// else
		// 	printf("%s", buff);
	}
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

	if ((!av || ac == 1) || !(av = &av[1]))
		return (FALSE);
	if (!(term = malloc(sizeof(struct termios) + 1)))
		return (FALSE);
	if (!set_cannic_mode(term))
		return (FALSE);
	ft_bzero(select_list, arr_len(av));
	init_selection(av, select_list);
	read_term(select_list, arr_len(av));
	reset_term(term);
	delete_selection(&select_list[0]);
	return (FALSE);
} 






