/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vo-nguye <vo-nguye@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 23:16:11 by vo-nguye          #+#    #+#             */
/*   Updated: 2021/01/28 23:16:11 by vo-nguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*next_split(char *word, char **result)
{
	int		i;
	char	c;

	i = 0;
	while (word[i] == ' ')
		i++;
	(*result) = ft_strdup(word + i);
	while (word[i] && word[i] != ' ')
	{
		if (word[i] == DOUBLE_QUOTE || word[i] == SIMPLE_QUOTE)
		{
			c = word[i++];
			while (word[i] && word[i] != c)
				i++;
			if (word[i])
				i++;
		}
		while (word[i] && word[i]
			!= DOUBLE_QUOTE && word[i] != SIMPLE_QUOTE && word[i] != ' ')
			i++;
	}
	(*result)[i] = 0;
	return (word + i);
}

char 	**word_split(char *word)
{
	char	**result;
	char	*ptr;
	int		i;

	i = 0;
	result = x_malloc(sizeof(char *) * ft_strlen(word));
	while (word[0])
	{
		word = next_split(word, &result[i]);
		if (ft_strlen(result[i]) == 0)
		{
			free(result[i]);
			break ;
		}
		i++;
	}
	result[i] = 0;
	return (result);
}
