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

#include "../minishell.h"

char		**get_env_as_array()
{
	int 		i;
	t_env_var 	*current;
	char 		*word;

	i = 0;
	current = env_list;
	free_split(all_env_as_array);
	all_env_as_array = malloc(sizeof (char *) * env_var_count() + 1);
	if (all_env_as_array == 0)
		return (0);
	while(current)
	{
		word = ft_strdup("");
		word = ft_strjoin_and_free(word, current->name);
		word = ft_strjoin_and_free(word, "=");
		word = ft_strjoin_and_free(word, current->value);
		all_env_as_array[i] = ft_strdup(word);
		free(word);
		current = current->next;
		i++;
	}
	all_env_as_array[i] = 0;
	return (all_env_as_array);
}

void 		init_env_list(void)
{
	env_list = malloc(sizeof(t_env_var*));
	env_list->name = ft_strdup("author");
	env_list->value = ft_strdup("vo-nguye");
	env_list->next = 0;
	requested_env_var = ft_strdup("");
	all_env_as_array = ft_split("yolo yolo", ' ');
}

char 		*get_value_and_free_or_not(char *name, int free_name)
{
	t_env_var	*current;

	free(requested_env_var);
	current = env_list;
	while (current->next && ft_strncmp(current->name, name, ft_strlen(name)) != 0)
	{
		current = current->next;
	}
	if (ft_strncmp(current->name, name, ft_strlen(name)) == 0)
	{
		requested_env_var = ft_strdup(current->value);
		if (free_name == 1)
			free(name);
		return (requested_env_var);
	}
	requested_env_var = ft_strdup("");
	if (free_name == 1)
		free(name);
	return (requested_env_var);
}

void 		unset_env(char *name)
{
		t_env_var	*current;

		current = env_list;
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

void 		export_var(char *name, char *value)
{
		t_env_var *current;
		t_env_var *item;

		current = env_list;
		while (current && current->next && vo_strcmp(name, current->name) != 0)
		{
			current = current->next;
		}
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

void 	print_var()
{
	t_env_var		*current;
	int i;

	i = 0;
	current = env_list;
	while (current)
	{
		if (ft_strlen(current->name) < 1)
		{
			current = current->next;
			continue;
		}
		printf("%s=%s\n", current->name, current->value);
		current = current->next;
		i++;
	}
}

int		main__()
{
	init_env_list();
	print_split(get_env_as_array());

	export_var("1", "val");
	print_split(get_env_as_array());
	print_split(get_env_as_array());
	export_var("2", "val");
	print_split(get_env_as_array());
	print_split(get_env_as_array());
	export_var("3", "val");
	print_split(get_env_as_array());

	destroy_env();

	return (0);
}


