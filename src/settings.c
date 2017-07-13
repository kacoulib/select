/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 17:07:10 by kacoulib          #+#    #+#             */
/*   Updated: 2017/07/12 17:07:11 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../select.h"

int					keyboard_events(char keyCode[], t_select select[], int len)
{
	char				*tmp;
	int				lastpos;
	static int	x = 0;
	static int	y = 0;

	if (!keyCode)
		return (FALSE);
	lastpos = x;
	if (keyCode[2] == 65)
		x = (x > 0) ? x - 1 : len;
	if (keyCode[2] == 66)
		x = (x < len) ? x + 1 : 0;
	tmp = tgetstr("cm", 0);
	tputs(tgetstr("ue", 0), 1, display_on_screen);
	tputs(tgoto(tmp, y, lastpos), 1, display_on_screen);
	printf("%s\n", select[lastpos].content);
	tputs(tgoto(tmp, y, x), 1, display_on_screen);
	tputs(tgetstr("us", 0), 1, display_on_screen);
	ft_putendl(select[x].content);
	// printf("%d\n", x);
	return (1);
}

int					arr_len(char **arr)
{
	int				i;

	if (!arr)
		return (0);
	i = -1;
	while (arr[++i])
		;
	return (i);
}