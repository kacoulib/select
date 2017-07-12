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

int			keyboard_events(char keyCode[])
{
	if (!keyCode)
		return (FALSE);

	if (keyCode[2] == 65)
		printf("up\n");
	if (keyCode[2] == 66)
		printf("down\n");
	if (keyCode[2] == 67)
		printf("right\n");
	if (keyCode[2] == 68)
		printf("left\n");
	return (1);
}