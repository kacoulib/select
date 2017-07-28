/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/22 19:21:25 by kacoulib          #+#    #+#             */
/*   Updated: 2017/07/22 19:21:51 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_select.h"

struct	termios		*get_terminal(void)
{
	static	struct termios *term = NULL;

	if (!term)
		term = malloc(sizeof(struct termios) + 1);
	return (term);
}

int					reset_term(struct termios *term)
{
	char					*tmp;

	if (tcgetattr(0, term) == -1)
		return (FALSE);
	term->c_lflag = (ICANON | ECHO | ISIG);
	if (!(tmp = tgetstr("te", 0)))
		return (FALSE);
	tputs(tmp, 0, display_on_screen);
	if (!(tmp = tgetstr("ve", 0)))
		return (FALSE);
	tputs(tmp, 0, display_on_screen);
	if (!(tmp = tgetstr("se", 0)))
		return (FALSE);
	tputs(tmp, 0, display_on_screen);
	if (!(tmp = tgetstr("ue", 0)))
		return (FALSE);
	tputs(tmp, 0, display_on_screen);
	if (tcsetattr(0, TCSADRAIN, term) < 0)
		return (FALSE);
	return (TRUE);
}

int					set_cannic_mode(struct termios *term)
{
	char					*term_name;
	char					*tmp;

	tmp = NULL;
	if (!(term_name = getenv("TERM")))
		return (FALSE);
	if (tgetent(0, term_name) < 1)
		return (FALSE);
	if (tcgetattr(0, term) < 0)
		return (FALSE);
	term->c_lflag &= ~(ICANON | ECHO);
	// term->c_cc[VMIN] = 1;
	// term->c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, term) < 0)
		return (FALSE);
	return (TRUE);
}
