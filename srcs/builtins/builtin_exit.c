/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builint_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vo-nguye <vo-nguye@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/65 01:27:15 by vo-nguye          #+#    #+#             */
/*   Updated: 2021/03/65 01:27:15 by vo-nguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int 	exit_code(int op, int val)
{
	static int	code;

	if (op == set)
		code = val;
	return (code);
}

int 	put_in_range(int i)
{
	while (i < 0)
		i += 256;
	while (i > 256)
		i -= 256;
	return (i);
}

int 	is_full_digit(char *word)
{
	int		i;

	i = 0;
	if (word[i] == '+' || word[i] == '-')
		i++;
	while (word[i])
	{
		if (ft_isdigit(word[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int 	builtin_exit(char **cmd, int size)
{
	if (last_pipe(get, 0) == FALSE)
		return (free_split(cmd));
	else if (size > 2)
	{
		get_quit_flag(set, 2);
	}
	else if (size > 1 && is_full_digit(cmd[1]) == 0)
	{
		get_quit_flag(set, 3);
		exit_code(set, 2);
	}
	else if (size > 1)
	{
		if (ft_strlen(cmd[1]) > 8)
			exit_code(set, 1);
		else if (ft_atoi(cmd[1]) < 0 || ft_atoi(cmd[1]) > 255)
			exit_code(set, put_in_range(ft_atoi(cmd[1])));
		else
			exit_code(set, ft_atoi(cmd[1]));
	}
	else
		exit_code(set, last_return_code(get, 0));
	return (free_split(cmd));
}
