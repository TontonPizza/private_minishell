/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_unset.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vo-nguye <vo-nguye@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/64 11:49:28 by vo-nguye          #+#    #+#             */
/*   Updated: 2021/03/64 11:49:28 by vo-nguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int 	is_argument_valid(char *word)
{
	return (0);
}

int 	export_word(char *word)
{
	char 	*name;
	char 	*val;
	int 	i;

	name = ft_strdup(word);
	i = 0;
	while (word[i] && word[i] != '+' && word[i] != '=')
		;
	return (0);
}

int 	builtin_export(char **cmd)
{
	int 	i;
	int 	k;

	i = 1;
	while (cmd[i])
	{

		i++;
	}
	return (0);
}

int 	builtin_unset(char **cmd)
{
		int 	i;

		i = 1;
		while (cmd[i])
		{
			unset_env(cmd[i]);
			i++;
		}
		return (0);
}