/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vo-nguye <vo-nguye@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/33 06:45:08 by vo-nguye          #+#    #+#             */
/*   Updated: 2021/02/33 06:45:08 by vo-nguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 *  Ici on va récupérer les words bruts sous forme de char ** jusqu'au premier ";" si il y en a
 * 	On va les mettre sous forme de liste chaînée quand ils auront été expand
 *
 */

#include "../../headers/minishell.h"

void	add_words_to_token_list(t_token **list, char **words)
{
	int		i;

	i = 0;
	while (words[i])
	{
		token_list_add_last(list, token_constructor(words[i], TYPE_WORD, 0));
		i++;
	}
}

void	words_to_tokens_and_offset_words(char ***words, t_token **list)
{
	char	**expand;
	char	**tmp;
	int		i;
	t_token	*tok;

	i = 0;
	while ((*words)[i] && token_type((*words)[i]) != TYPE_END)
	{
		if (token_type((*words)[i]) != TYPE_WORD)
		{
			tok = token_constructor((*words)[i], token_type((*words)[i]), 0);
			token_list_add_last(list, tok);
		}
		else
		{
			expand = expand_word((*words)[i]);
			add_words_to_token_list(list, expand);
			free_split(expand);
		}
		i++;
	}
	tmp = *words;
	*words = offset_word((tmp), i + 1);
	free_split(tmp);
}
