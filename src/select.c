/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 14:36:16 by kacoulib          #+#    #+#             */
/*   Updated: 2017/07/11 14:36:32 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../select.h"

int			color_select()
{
	char	*res;

	if (!(res = tgetstr("cl", NULL)))
		return (FALSE);
	return (FALSE);
}

int			reset_term(struct termios *term)
{
	if (tcgetattr(0, term) == -1)
		return (FALSE);
	term->c_lflag = (ICANON | ECHO);
	if (tcsetattr(0, 0, term) == -1)
		return (FALSE);
	return (FALSE);
}

int			read_term()
{
	char	buff[PATH_MAX];


	while (read(0, buff, PATH_MAX) > 0)
	{
		// printf("%c", buff[0]);
		if (buff[0] == 27)
		{
			if (buff[2] == 65)
				printf("up\n");
			if (buff[2] == 66)
				printf("down\n");
			if (buff[2] == 67)
				printf("right\n");
			if (buff[2] == 68)
				printf("left\n");

			// printf("touch pressed\n");
			// printf("%d\n", buff[2]);
		}
		else if (buff[0] == 4)
			printf("_ctr+d_");
		else
			printf("%s", buff);
	}
	return (TRUE);
}

int			set_cannic_mode(struct termios *term)
{
	char	*term_name;
	char	*tmp;

	tmp = NULL;
	if (!(term_name = getenv("TERM")))
		return (FALSE);

/*
	// not working for some reason

	if (tgetent(NULL, term_name) == 0)
		return (-1);
*/
	if (tcgetattr(0, term) < 0)
		return (FALSE);
	printf("%s\n", term_name);
	term->c_lflag &= ~(ICANON | ECHO);
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, term) < 0)
		return (FALSE);
	return (TRUE);
}

int			main(int ac, char **av)
{
	struct termios *term;

	if (!av || ac == 1)
		return (FALSE);
	if (!(term = malloc(sizeof(struct termios) + 1)))
		return (FALSE);
	set_cannic_mode(term);
	read_term();
	reset_term(term);
	return (FALSE);
} 