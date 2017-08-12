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

#ifndef FT_SELECT
# define FT_SELECT

# include "libft.h"
# include <unistd.h>
# include <stdio.h> // to remove
# include <signal.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <sys/stat.h>
# define FALSE 0
# define TRUE 1
# define PATH_MAX 3
# define SETCOLOR 0
# define ANSI_COLOR_BLACK	"\x1B[30m\x1B[42m"
# define ANSI_COLOR_RED		"\x1B[31m"
# define ANSI_COLOR_GREEN	"\x1B[32m"
# define ANSI_COLOR_YELLOW	"\x1B[33m"
# define ANSI_COLOR_BLUE	"\x1B[34m"
# define ANSI_COLOR_MAGENTA	"\x1B[35m"
# define ANSI_COLOR_CYAN	"\x1B[36m"
# define ANSI_COLOR_RESET	"\x1B[0m"


typedef struct		s_select
{
	char			*content;
	int				id;
	int				type;
	int				is_select;
	int				is_show;
	int				x_pos;
	int				y_pos;
	int				is_underline;
}					t_select;

typedef struct		s_term_info
{
	int				index;
	int				last_pos;
	int				nb_select;
	int				select_len;
	int				nb_deleted;
	int				x_pos;
	int				y_pos;
	int				col_space;
	int				height;
	int				width;
	int				*ctr_z;
	int				nb_col;
	struct termios	*term;
}					t_term_info;

int					arr_len(char **arr);
int					tputs_display_function(int c);
int					signal_handler();
void				init_selection(char **av, t_select list[],
	t_term_info *t_info);
int					display_all_elem(t_term_info *term_info, t_select select[]);
t_term_info			*get_or_init_term(char **av, struct termios	*term);
int					keyboard_events(char keycode[], t_select select[],
	t_term_info *term_info);
int					reset_term(struct termios *term);
int					toggle_underline(t_select *select);
int					underline_and_deplace(t_select select[],
	t_term_info *term_info);
void				update_selection(t_term_info *t_info, t_select list[]);
int					set_cannic_mode(struct termios *term);
int					reset_term(struct termios *term);
struct termios		*get_terminal();
int					move_cursor(t_term_info *t_info, t_select select[],
	char direction);
int					update_screen_info(void);

#endif
