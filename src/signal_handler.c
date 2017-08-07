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

static void						handle_signal(int signum)
{
	t_term_info *term;

	term = get_or_init_term(NULL, NULL);
	if (signum == SIGINT)
	{
		ft_putstr("dsdsds\n");		
	}
	else if (signum == SIGWINCH)
	{
		resize_handle(term);
		// ft_putstr("Windows resized");
	}
	else if (signum == SIGTSTP)
	{
		ft_putstr("Signal paused");
	}
	else if (signum == SIGSTOP)
	{
		ft_putstr("Stoped");
	}
	reset_term(term->term);
}

static void						handle_signal_and_exit(int signum)
{
	handle_signal(signum);
	exit(1);
}

int						signal_handler(void)
{
	// struct sigaction temp;

	// ft_memset(&temp, 0, sizeof(temp));
	// temp.sa_flags = SA_NODEFER;
	// temp.sa_handler = signal_handler;
	// if (sigaction(SIGINT, &temp, NULL) != -1)
	// {
	// 	printf("SIGINT ERROR\n");
	// }else if (sigaction(SIGSTOP, &temp, NULL) != -1)
	// 	printf("SIGINT ERROR\n");
	// signal(SIGWINCH, refresh_screen);
	// signal(SIGCONT, restart_function);
	signal(SIGWINCH, handle_signal);
	signal(SIGQUIT, handle_signal_and_exit);
	signal(SIGTSTP, handle_signal_and_exit);
	signal(SIGINT, handle_signal_and_exit);

	return (1);
}
