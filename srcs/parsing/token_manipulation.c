/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vo-nguye <vo-nguye@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 01:19:38 by vo-nguye          #+#    #+#             */
/*   Updated: 2021/01/25 01:19:38 by vo-nguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int 	token_list_size(t_token *list)
{
	int	i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

void	token_list_add_last(t_token **first_element, t_token *item)
{
	t_token	*cursor;

	cursor = *first_element;
	if (*first_element == 0)
	{
		*first_element = item;
		return ;
	}
	while (cursor && cursor->next)
		cursor = cursor->next;
	cursor->next = item;
	item->next = 0;
	return ;
}

t_token	*token_constructor(char *name, int type, int free_val)
{
	t_token	*a;

	a = x_malloc(sizeof(t_token));
	a->token = ft_strdup(name);
	a->type = type;
	a->next = 0;
	if (free_val == FREE_ARG)
		free(name);
	return (a);
}

void	token_destructor(t_token *item)
{
	free(item->token);
	free(item);
	item = NULL;
}

void	destroy_token_list(t_token *item)
{
	if (item == 0)
		return ;
	destroy_token_list(item->next);
	token_destructor(item);
}
