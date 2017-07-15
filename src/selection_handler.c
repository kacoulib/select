/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 20:40:50 by kacoulib          #+#    #+#             */
/*   Updated: 2017/07/12 20:41:01 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../select.h"

/*
** Create a single selection
**
** @return the new selection
*/

t_select		*create_selection(char *content)
{
	t_select	*new;

	if (!(new = malloc(sizeof(t_select) + 1)))
		return (NULL);
	new->content = ft_strdup(content);
	new->is_select = FALSE;
	new->is_underline = FALSE;
	new->is_show = TRUE;
	return (new);
}

/*
** Delete the selection liste one by one
**
** @return a null
*/

t_select		*delete_selection(t_select *head)
{
	// t_select	*tmp;

	if (!head)
		return (NULL);
	// while (head)
	// {
	// 	tmp = head->next;
	// 	if (head->content)
	// 		free(head->content);
	// 	break;
	// 	free(head); // @todo: can't free the current selection
	// 	head = tmp;
	// }
	return (head);
}

/*
** Create a liste of selection
**
** @return return the top head of created selection
*/

t_select		*init_selection(char **av, t_select list[])
{
	int			i;
	int			*nb_select;
	t_select	*current;

	i = -1;
	nb_select = 0;
	while (av[++i])
	{
		if (!(current = create_selection(av[i])))
			return (NULL);
		list[i] = *current;
	}
	return (list);
}