/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_handlers_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vo-nguye <vo-nguye@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 10:44:12 by vo-nguye          #+#    #+#             */
/*   Updated: 2021/01/15 10:44:12 by vo-nguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char 	**split_join_string(char **split, char *word)
{
	char	**result;
	int 	i;

	i = 0;
	result = malloc(sizeof(char *) * (split_size(split) + 2));
	if (result == 0)
		return (0);
	while (split[i])
	{
		result[i] = ft_strdup(split[i]);
		i++;
	}
	result[i++] = ft_strdup(word);
	result[i] = 0;
	free_split(split);
	return (result);
}

char 	**copy_split(char **split)
{
	char 	**result;
	int 	i;

	result = malloc(sizeof (char *) * (split_size(split) + 2));
	if (result == 0)
		return (0);
	while (split && split[i])
	{
		result[i] = ft_strdup(split[i]);
		i++;
	}
	result[i] = 0;
	return (result);
}

char 	**offset_word(char **words, int offset)
{
	char	**result;
	int		i;
	int 	k;

	if (offset > split_size(words))
		return (0);
	result = x_malloc(sizeof (char *) * split_size(words));
	i = 0;
	k = 0;
	while (i < offset)
		i++;
	while (words[i + k])
	{
		result[k] = ft_strdup(words[i + k]);
		k++;
	}
	result[k] = 0;
	free_split(words);
	return (result);
}
