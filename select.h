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
# define ANSI_COLOR_CYAN	"\x1B[36m"
# define ANSI_COLOR_RESET	"\x1B[0m"

typedef struct 			s_select
{
	char				*content;
	int					is_select;
	int					is_show;
	int					is_underline;
	int					*nb_select;
}						t_select;

int						arr_len(char **arr);
t_select				*create_selection(char *content);
t_select				*delete_selection(t_select *head);
int						display_on_screen(int c);
// int						display_with_video_mode(t_select select[], int *x_pos,
	// int lastpos, int *len);

t_select				*init_selection(char **av, t_select list[]);
int						keyboard_events(char keyCode[], t_select select[],
	int *len, int *nb_select);
int						keyCode_delete(t_select select[], int x_pos, int *len,
	int *nb_select);
int						move_down(t_select select[], int *x_pos, int lastpos,
	int *len);
int						move_up(t_select select[], int *x_pos, int lastpos,
	int *len);
int						toggle_underline(t_select select[], int x_pos);
int						underline_and_deplace(t_select select[], int x_pos,
	int lastpos);



#endif
