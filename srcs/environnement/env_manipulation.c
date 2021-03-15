/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manipulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vo-nguye <vo-nguye@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 13:56:30 by vo-nguye          #+#    #+#             */
/*   Updated: 2021/01/07 13:56:30 by vo-nguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	**get_env_as_array(void)
{
	int			i;
	t_env_var	*current;
	char		*word;

	i = 0;
	current = get_meta_data(0)->env_list;
	free_split(get_meta_data(0)->all_env_as_array);
	get_meta_data(0)->all_env_as_array
	= x_malloc(sizeof (char *) * (env_var_count() + 2));
	if (get_meta_data(0)->all_env_as_array == 0)
		return (0);
	while (current)
	{
		word = ft_strdup("");
		word = ft_strjoin_and_free(word, current->name);
		word = ft_strjoin_and_free(word, "=");
		word = ft_strjoin_and_free(word, current->value);
		get_meta_data(0)->all_env_as_array[i] = ft_strdup(word);
		free(word);
		current = current->next;
		i++;
	}
	get_meta_data(0)->all_env_as_array[i] = 0;
	return (get_meta_data(0)->all_env_as_array);
}

char	*get_value_and_free_or_not(char *name, int free_name)
{
	t_env_var	*current;

	get_meta_data(60);
	current = get_meta_data(0)->env_list;
	while (current->next && ft_strncmp(current->name, name, ft_strlen(name)) != 0)
		current = current->next;
	if (ft_strncmp(current->name, name, ft_strlen(name)) == 0)
	{
		get_meta_data(0)->requested_env_var = ft_strdup(current->value);
		if (free_name == 1)
			free(name);
		if (vo_strcmp(get_meta_data(0)->requested_env_var, LORIE) == 0)
		{
			get_meta_data(60);
			return (ft_strdup(""));
		}
		return (get_meta_data(0)->requested_env_var);
	}
	get_meta_data(0)->requested_env_var = ft_strdup("");
	if (free_name == 1)
		free(name);
	return (get_meta_data(0)->requested_env_var);
}

void	unset_env(char *name)
{
	t_env_var	*current;

	current = get_meta_data(0)->env_list;
	while (current && current->next && vo_strcmp(current->name, name) != 0)
	{
		current = current->next;
	}
	if (vo_strcmp(current->name, name) == 0)
	{
		free(current->value);
		current->value = ft_strdup("");
	}
}

void	export_var(char *name, char *value)
{
	t_env_var	*current;
	t_env_var	*item;

	current = get_meta_data(0)->env_list;
	while (current && current->next && vo_strcmp(name, current->name) != 0)
		current = current->next;
	if (vo_strcmp(name, current->name) != 0)
	{
		item = malloc(sizeof(t_env_var));
		if (item == 0)
			return ;
		item->name = ft_strdup(name);
		item->value = ft_strdup(value);
		item->next = 0;
		current->next = item;
	}
	else if (vo_strcmp(name, current->name) == 0)
	{
		free(current->value);
		current->value = ft_strdup(value);
	}
}
