/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_to_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vo-nguye <vo-nguye@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 07:15:02 by vo-nguye          #+#    #+#             */
/*   Updated: 2021/01/07 07:15:02 by vo-nguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int 		token_type(char *word)
{
	int i;

	i = ft_strlen(word);
	if (ft_strncmp(word, "|", i) == 0)
		return (TYPE_PIPE);
	if (ft_strncmp(word, ";", i) == 0)
		return (TYPE_END);
	if (ft_strncmp(word, "<", i) == 0)
		return (TYPE_IN);
	if (ft_strncmp(word, ">", i) == 0)
		return (TYPE_OUT);
	if (ft_strncmp(word, ">>", i) == 0)
		return (TYPE_APPEND);
	return (TYPE_WORD);
}

t_token		*word_to_token(char *word)
{
	t_token	*token;

	token = malloc(sizeof (token));
	if (token == 0)
		return (0);
	token->token = ft_strdup(word);
	token->type = token_type(word);
	token->next = 0;
	return (token);
}

t_token 	*words_to_token_list_and_free_words(char **words)
{
	t_token 	*first_token;
	first_token = (0);
	int 		i;

	while (words[i])
	{
		token_add_back(&first_token, word_to_token(words[i]));
		i++;
	}
	free_split(words);
	return (first_token);
}

void 	print_content(void *content)
{
	t_token *token;

	token = (t_token *)content;
	printf("%s %d\n", token->token, token->type);
}



int main_wtk()
{
	t_token *first_token;
	t_token *cursor;
	int i;

	first_token = 0;
	i = 0;
	char **words = get_words("salut \"e·\"  copains ; ;");

	// clean words up to ;

	first_token = words_to_token_list_and_free_words(words);

	// exec cmd up to ;


	cursor = first_token;
	while (cursor)
	{
		print_content(cursor);
		cursor = cursor->next;
	}
	return (0);
}











