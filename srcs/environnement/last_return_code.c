/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_return_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vo-nguye <vo-nguye@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 06:18:19 by vo-nguye          #+#    #+#             */
/*   Updated: 2021/01/23 06:18:19 by vo-nguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
 * op = set => set last_return_code to value
 * op == get => ignore value
 */

int 	last_return_code(int op, int value)
{
	static int	last_return_code;

	if (op == set)
		last_return_code = value;
	return (last_return_code);
}
