/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bullshit_functions_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vo-nguye <vo-nguye@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/65 19:46:00 by vo-nguye          #+#    #+#             */
/*   Updated: 2021/03/65 19:46:00 by vo-nguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ptr_p(int *ptr, int i)
{
	*ptr += i;
	return (1);
}

int 	define_redirect(int red, char c)
{
	if (c == '>')
		return (1);
	if (c == '|')
		return (0);
	return (red);
}

char	**fix_words(char **words)
{
	char	**result;
	int 	i;
	int 	redirect;

	result = x_malloc(sizeof(char *));
	result[0] = 0;
	redirect = 0;
	i = 0;
	while(words[i])
	{
		redirect = define_redirect(redirect, words[i][0]);
		if (words[i][0] == ';' && redirect == 1)
		{
			result = split_join_string(result, "|");
			result = split_join_string(result, "ignore");
			redirect = 0;
		}
		result = split_join_string(result, words[i++]);
	}
	if (free_split(words) && redirect == 1)
	{
		result = split_join_string(result, "|");
		result = split_join_string(result, "ignore");
	}
	return (result);
}