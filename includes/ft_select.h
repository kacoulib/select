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
# define FALSE 0
# define TRUE 1
# define PATH_MAX 3

typedef struct			s_select
{
	char				*content;
	int					id;
	int					is_select;
	int					is_show;
	int					is_underline;
}						t_select;

typedef struct			s_term_info
{
	int					index;
	int					last_pos;
	int					nb_select;
	int					select_len;
	int					x_pos;
	int					y_pos;
	int					col_space;
	int					height;
	int					width;
	int					nb_col;
	struct termios	*term;
}						t_term_info;

int						arr_len(char **arr);
t_select				*delete_selection(t_select *head);
int						display_on_screen(t_select select);

int						tputs_display_function(int c);
int						display_result(t_select select[],
	t_term_info *term_info);
int						signal_handler();
void					init_selection(char **av, t_select list[]);
int						init_screen(t_select select[], t_term_info *term_info);
t_term_info				*get_or_init_term(char **av, struct termios	*term);
int						keyboard_events(char keycode[], t_select select[],
	t_term_info *term_info);
int						keycode_delete(t_select select[],
	t_term_info *term_info);
int						move_down(t_select select[], t_term_info *term_info);
int						move_up(t_select select[], t_term_info *term_info);
int						reset_term(struct termios *term);
int						toggle_underline(t_select select[], int index,
	int y_pos);
int						underline_and_deplace(t_select select[],
	t_term_info *term_info);
int						set_cannic_mode(struct termios *term);
int						reset_term(struct termios *term);
struct termios			*get_terminal();
int						resize_handle(t_term_info *t_info);

#endif
