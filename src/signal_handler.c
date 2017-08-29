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
	char	cp[3];
	int		i;

	i = signum;
	term = get_or_init_term(NULL, NULL);
	reset_term(term->term);
	cp[0] = term->term->c_cc[VSUSP];
	cp[1] = '\n';
	cp[2] = '\0';
	ioctl(isatty(STDOUT_FILENO), TIOCSTI, &cp);
	// signal(SIGCONT, SIG_DFL);
}

static void		continue_signal(int signum)
{
	t_term_info *term;

	(void)signum;
	term = get_or_init_term(NULL, NULL);
	(void )term;
	reset_term(term->term);
	read_term(term, term->select);
	ioctl(STDOUT_FILENO, TIOCNOTTY, NULL);
	
	// signal(SIGTSTP, stop_signal);
	// signal(SIGCONT, continue_signal);
	// display_result(term, term->select);
}

static void		kill_signal(t_term_info *term, int signum)
{
	reset_term(term->term);
	signal(signum, SIG_DFL);
	exit(1);
}

static void		handle_signal(int signum)
{
	t_term_info *term;

	term = get_or_init_term(NULL, NULL);
	if (signum == SIGWINCH)
		display_all_elem();
	else if (signum == SIGINT)
		kill_signal(term, signum);
	else if (signum == SIGQUIT)
		kill_signal(term, signum);
	else if (signum == SIGTERM)
		kill_signal(term, signum);
	else
	{
		reset_term(term->term);
		signal(signum, SIG_DFL);
		printf("This %d signal has been captured but not handler :(", signum);
	}
}

int				signal_handler(void)
{
	// int			i;


	if (signal(SIGTSTP, SIG_IGN) != SIG_IGN)
		signal(SIGTSTP, stop_signal);
	if (signal(SIGCONT, SIG_IGN) != SIG_IGN)
		signal(SIGCONT, continue_signal);
	signal(SIGTERM, handle_signal);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	signal(SIGWINCH, handle_signal);

	// i = -1;
	// while (++i < 32)
	// 	signal(i, handle_signal);
	// signal(SIGWINCH, handle_signal);
	// // signal(SIGCONT, handle_signal);
	// signal(SIGINT, handle_signal);
	// signal(SIGTSTP, handle_signal);
	return (1);
}
