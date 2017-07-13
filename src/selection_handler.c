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

t_select		*create_selection(char *content, t_select *next)
{
	t_select	*new;

	if (!(new = malloc(sizeof(t_select) + 1)))
		return (NULL);
	new->content = ft_strdup(content);
	new->is_select = FALSE;
	new->next = next;
	return (new);
}

/*
** Delete the selection liste one by one
**
** @return a null
*/

t_select		*delete_selection(t_select *head)
{
	t_select	*tmp;

	if (!head)
		return (NULL);
	while (head)
	{
		tmp = head->next;
		if (head->content)
			free(head->content);
		// free(head); // @todo: can't free the current selection
		head = tmp;
	}
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
	t_select	*current;
	t_select	*head;
	t_select	*prev;

	head = NULL;
	prev = NULL;
	i = -1;
	while (av[++i])
	{
		if (!(current = create_selection(av[i], NULL)))
			return (NULL);
		if (prev)
			prev->next = current;
		list[i] = *current;
		prev = current;
	}
	return (list);
}
