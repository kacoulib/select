/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 14:35:43 by kacoulib          #+#    #+#             */
/*   Updated: 2017/07/11 14:35:45 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELLECT
# define SELLECT

# ifdef unix
	static char TERM_BUFF[2048];
# else
	# define TERM_BUFF 0
# endif

# include "lib/libft/libft.h"
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h> // to remove
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>

# include <stdio.h> // to remove

# define FALSE 0
# define TRUE 1
# define PATH_MAX 3

typedef struct 			s_select
{
	char				*content;
	int					is_select;
	struct 	s_select	*next;
}						t_select;

t_select				*create_selection(char *content, t_select *next);
t_select				*delete_selection(t_select **head);
int						display_on_screen(int c);
t_select				*init_selection(char **av);
int						keyboard_events(char keyCode[]);


#endif
