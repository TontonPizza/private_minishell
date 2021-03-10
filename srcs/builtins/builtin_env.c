/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vo-nguye <vo-nguye@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/63 18:22:43 by vo-nguye          #+#    #+#             */
/*   Updated: 2021/03/63 18:22:43 by vo-nguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int 	builtin_env(char **cmd)
{
	char	**env_array;
	int		i;
	char	**split;

	i = 0;
	env_array = get_env_as_array();
	while (env_array && env_array[i])
	{
		split = ft_split(env_array[i], '=');
		if (vo_strcmp(split[split_size(split) - 1], LORIE) != 0)
			ft_putendl_fd(env_array[i], 1);
		free_split(split);
		i++;
	}
	free_split(cmd);
	return (0);
}
