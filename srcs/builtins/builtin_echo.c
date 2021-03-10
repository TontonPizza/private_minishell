/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vo-nguye <vo-nguye@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/64 20:02:18 by vo-nguye          #+#    #+#             */
/*   Updated: 2021/03/64 20:02:18 by vo-nguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	echo_n(char **cmd)
{
	int		i;

	i = 2;
	while (cmd[i])
	{
		if (i != 2)
			ft_putstr_fd(" \0", 1);
		if (i > 1)
			ft_putstr_fd(cmd[i], 1);
		i++;
	}
	return (0);
}

int	echo_vanilla(char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (i != 1)
			ft_putstr_fd(" \0", 1);
		if (ft_strlen(cmd[i]))
			ft_putstr_fd(cmd[i], 1);
		i++;
	}
	ft_putstr_fd("\n\0", 1);
	return (0);
}

int	builtin_echo(char **cmd)
{
	if (cmd[0] && cmd[1] && ft_strncmp(cmd[1], "-n", 2) == 0)
		echo_n(cmd);
	else
		echo_vanilla(cmd);
	free_split(cmd);
	return (0);
}
