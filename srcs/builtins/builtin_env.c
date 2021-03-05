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

#include "../../minishell.h"

int 	builtin_env(void)
{
	char	**env_array;
	int 	i;

	i = 0;
	env_array = get_env_as_array();
	while (env_array && env_array[i])
	{
		ft_putendl_fd(env_array[i], 1);
		i++;
	}
	return (0);
}
