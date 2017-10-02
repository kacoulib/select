/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 18:14:40 by kacoulib          #+#    #+#             */
/*   Updated: 2017/07/18 18:14:56 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		stop_signal(int signum)
{
	t_term_info *term;
	char		cp[2];

	(void)signum;
	signal(SIGTSTP, SIG_DFL);
	term = get_or_init_term(NULL, NULL);
	reset_term(term->term);
	cp[0] = term->term->c_cc[VSUSP];
	cp[1] = '\0';
	ioctl(isatty(STDOUT_FILENO), TIOCSTI, &cp);
}

static void		continue_signal(int signum)
{
	t_term_info *term;
	char		*tmp;

	(void)signum;
	signal(SIGTSTP, stop_signal);
	term = get_or_init_term(NULL, NULL);
	(void)term;
	term->term = get_terminal();
	if (!set_cannic_mode(term->term))
		return ;
	if (!(tmp = tgetstr("ti", 0)))
		return ;
	tputs(tmp, 0, tputs_display_function);
	if (!(tmp = tgetstr("vi", 0)))
		return ;
	tputs(tmp, 0, tputs_display_function);
	display_all_elem();
}

static void		kill_signal(t_term_info *term, int signum)
{
	reset_term(term->term);
	(void)signum;
	exit(1);
}

static void		handle_signal(int signum)
{
	t_term_info *term;

	term = get_or_init_term(NULL, NULL);
	if (signum == SIGWINCH)
		display_all_elem();
	else if (signum == SIGCONT)
		continue_signal(signum);
	else if (signum == SIGTSTP)
		stop_signal(signum);
	else
		kill_signal(term, signum);
}

int				signal_handler(void)
{
	int			i;

	i = 0;
	while (++i < 32)
		signal(i, handle_signal);
	return (1);
}
