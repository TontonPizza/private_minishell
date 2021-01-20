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

char 		**words_after_semicolon(char **words)
{
	char	**result;
	int 	i;
	int 	k;

	result = x_malloc(sizeof(char *) * (split_size(words) + 2));
	i = 0;
	k = 0;
	while (words[i] && token_type(words[i]) !=  TYPE_END)
	{
		i++;
	}
	if (words[i])
		i++;
	while (words[i])
	{
		result[k++] = words[i++];
	}
	result[k] = 0;
	return (result);
}

t_token		*word_to_token(char *word)
{
	t_token	*token;

	token = malloc(sizeof (t_token));
	if (token == 0)
		return (0);
	token->token = ft_strdup(word);
	token->type = token_type(word);
	token->next = 0;
	return (token);
}

void		words_to_token_list_and_free_words(char **words, t_token **first_token)
{
	int 		i;

	i = 0;
	while (words[i])
	{
		token_add_back(first_token, word_to_token(words[i]));
		i++;
	}
	free_split(words);
}

void 	print_content(void *content)
{
	t_token *token;

	token = (t_token *)content;
	printf("%s %d\n", token->token, token->type);
}











