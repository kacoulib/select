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



static void						stop_signal(t_term_info *term)
{
	// char	buff[2];

	reset_term(term->term);
	signal(SIGSTOP, SIG_DFL);
	// buff[0] = term->term->c_cc[VSUSP];
	// buff[1] = 0;
	// ioctl(0, TIOCSTI, buff);
}

static void						continue_signal(t_term_info *term)
{
	reset_term(term->term);
	signal(SIGCONT, SIG_DFL);

}

static void						kill_signal(t_term_info *term)
{
	reset_term(term->term);
	printf("signall killed\n");
	exit(0);
}

static void						handle_signal(int signum)
{
	t_term_info *term;

	term = get_or_init_term(NULL, NULL);
	if (signum == SIGWINCH)
		resize_handle(term);
	else if (signum == SIGCONT)
		continue_signal(term);
	else if (signum == SIGINT)
		stop_signal(term);
	else if (signum == SIGTSTP)
		stop_signal(term);
	else if (signum == SIGKILL)
		kill_signal(term);
	else if (signum == SIGQUIT)
		kill_signal(term);
	else if (signum == SIGTERM)
		kill_signal(term);
	else if (signum == SIGSTOP)
		kill_signal(term);
	else
		ft_putstr("This signal has been captured but not handler :(");
}

int						signal_handler(void)
{
	int			i;

	i = 0;
	while (++i < 32)
		signal(i, handle_signal);
	return (1);
}
