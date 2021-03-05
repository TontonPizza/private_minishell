/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bullshit_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vo-nguye <vo-nguye@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/64 15:35:55 by vo-nguye          #+#    #+#             */
/*   Updated: 2021/03/64 15:35:55 by vo-nguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"

/*
 *		ternary
 */
char 	tr(char a, char b, char c)
{
	if (a == b)
		return (c);
	return (a);
}

char 	*place_zero(char *result, int i)
{
	result[i] = 0;
	return (result);
}
