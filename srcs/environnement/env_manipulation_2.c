/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manipulation_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vo-nguye <vo-nguye@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 08:43:04 by vo-nguye          #+#    #+#             */
/*   Updated: 2021/01/08 08:43:04 by vo-nguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	destroy_env_list(t_env_var **item)
{
	if (*item == NULL)
		return (0);
	destroy_env_list(&((*item)->next));
	free((*item)->value);
	free((*item)->name);
	free(*item);
	return (0);
}

t_env_data	*get_meta_data(int first_call)
{
	static t_env_data	metadata;

	if (first_call == -1)
	{
		free_split(metadata.all_env_as_array);
		get_meta_data(60);
		destroy_env_list(&(metadata.env_list));
		return (0);
	}
	if (first_call == 1)
	{
		metadata.env_list = x_malloc(sizeof(t_env_var));
		metadata.env_list->name = ft_strdup("author");
		metadata.env_list->value = ft_strdup("vo-nguye");
		metadata.env_list->next = 0;
		metadata.requested_env_var = 0;
		metadata.all_env_as_array = ft_split("yolo yolo", ' ');
	}
	if (first_call == 60 && metadata.requested_env_var != 0)
	{
		free(metadata.requested_env_var);
		metadata.requested_env_var = 0;
	}
	return (&metadata);
}

void	init_env_list(void)
{
	last_return_code(set, 0);
	get_meta_data(1);
}

int	env_var_count(void)
{
	int			i;
	t_env_var	*current;

	i = 0;
	current = get_meta_data(0)->env_list;
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i);
}

void	destroy_env(void)
{
	get_meta_data(-1);
}
