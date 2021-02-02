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

#include "../../minishell.h"


t_token		*words_to_tokens_and_offset_words(char ***words)
{
	t_token	*token;
	int 	i;

	i = 0;
	while ((*words)[i] && token_type((*words)[i]) != TYPE_END)
	{
		/*
		 *  ajoute le resultat de l'expand à la liste chainée
		 *
		 */
		i++;
		if (i == 3)
			break;
	}
	*words = offset_word(*words, i);
	return (token);
}