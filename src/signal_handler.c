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

#include "../ft_select.h"

static void						termination_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr("dsdsds\n");		
		// printf("(%d)\n", signum);
	}
	else if (signum == SIGSTOP)
	{
		ft_putstr("Stoped");
	}
	// printf("signal exit\n");
	// signal(signum, SIG_DFL);
	reset_term(get_terminal());

}

static void						handle_and_exit(int signum)
{
	termination_handler(signum);
	exit(1);
}
int						handle_signal(void)
{
	// struct sigaction temp;

	// ft_memset(&temp, 0, sizeof(temp));
	// temp.sa_flags = SA_NODEFER;
	// temp.sa_handler = termination_handler;
	// if (sigaction(SIGINT, &temp, NULL) != -1)
	// {
	// 	printf("SIGINT ERROR\n");
	// }else if (sigaction(SIGSTOP, &temp, NULL) != -1)
	// 	printf("SIGINT ERROR\n");
	// signal(SIGWINCH, refresh_screen);
	// signal(SIGCONT, restart_function);
	// signal(SIGTSTP, abort_no_exit);
	signal(SIGINT, handle_and_exit);

	return (1);
}
