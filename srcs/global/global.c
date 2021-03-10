/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vo-nguye <vo-nguye@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/65 21:14:20 by vo-nguye          #+#    #+#             */
/*   Updated: 2021/03/65 21:14:20 by vo-nguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	g_out(int op, int val)
{
	static int	g;

	if (op == set)
		g = val;
	return (g);
}

int	g_in(int op, int val)
{
	static int	g;

	if (op == set)
		g = val;
	return (g);
}

int	g_err(int op, int val)
{
	static int	g;

	if (op == set)
		g = val;
	return (g);
}
