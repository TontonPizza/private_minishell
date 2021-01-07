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

char		**get_env_as_words()
{
	char	**env;

	return (env);
}

void 		init_env_list(void)
{
	env_list = malloc(sizeof(t_env_var*));
	env_list->name = ft_strdup("author");
	env_list->value = ft_strdup("vo-nguye");
	env_list->next = 0;
}

char 		*get_value(char *name)
{
	t_env_var	*current;

	current = env_list;
	while (current->next && ft_strncmp(current->name, name, ft_strlen(name)) != 0)
	{
		current = current->next;
	}
	if (ft_strncmp(current->name, name, ft_strlen(name)) == 0)
	{
		return (ft_strdup(current->value));
	}
	return (ft_strdup(""));
}

void 		unset_env(char *name)
{
		t_env_var	*current;

		current = env_list;
		while (current->next && ft_strncmp(current->name, name, ft_strlen(name)) != 0)
		{
			current = current->next;
		}
		if (ft_strncmp(current->name, name, ft_strlen(name)) == 0)
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
		while (current->next && ft_strncmp(current->name, name, ft_strlen(name)) != 0)
		{
			current = current->next;
		}
		if (current->next == 0 && ft_strncmp(current->name, name, ft_strlen(name)) != 0)
		{
			item = malloc(sizeof(t_env_var));
			if (current == 0)
				return ;
			item->name = ft_strdup(name);
			item->value = ft_strdup(value);
			item->next = 0;
			current->next = item;
		}
		else
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

int		main()
{
	init_env_list();

	print_var();

	export_var("salut", "copain");
	printf("\n\n---\n\n");

	print_var();
	printf("\n\n---\n\n");
	unset_env("salut");
	print_var();
	printf("\n\n---\n\n");
	unset_env("salut");
	print_var();
	printf("\n\n---\n\n");
	printf("-%s\n", get_value("author"));
	printf("-%s\n", get_value("salut"));
	printf("-%s\n", get_value("NTM"));

	return (0);
}


