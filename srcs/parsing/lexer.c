/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vo-nguye <vo-nguye@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/31/12 03:50:45 by vo-nguye          #+#    #+#             */
/*   Updated: 2020/31/12 03:50:45 by vo-nguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*check_for_separator(char *text, int *cursor)
{
	char	buffer[3];
	char	c;

	buffer[0] = 0;
	buffer[1] = 0;
	buffer[2] = 0;
	c = text[0];
	if (c == PIPE_C || c == SEMI_COLON || c == ARROW_RIGHT || c == ARROW_LEFT)
	{
		buffer[0] = text[0];
		if (text[1] == ARROW_RIGHT && text[0] == ARROW_RIGHT)
			buffer[1] = ARROW_RIGHT;
	}
	*cursor += ft_strlen(buffer);
	return (ft_strdup(buffer));
}

char	*get_next_word(char *text, int *cursor, int i)
{
	char	*new_text;
	char	sep;

	while ((text[i] == ' ' || text[i] == '\t') && text[i])
		i++;
	new_text = check_for_separator(text + i, &i);
	if (new_text && ft_strlen(new_text) > 0 && (ptr_p(cursor, i)))
		return (new_text);
	while (new_text && text[i] && is_char_in_set(text[i], "\x11\x12\x13\x14 ") == 0)
	{
		if (text[i] == '\"' || text[i] == '\'')
		{
			sep = text[i];
			new_text = join_char_and_free(new_text, text[i++]);
			while (text[i] && text[i] != sep && i < (int)ft_strlen(text))
			{
				if (text[i] == '\\' && text[i + 1] == '"' && sep == '"')
					new_text = join_char_and_free(new_text, text[i++]);
				new_text = join_char_and_free(new_text, text[i++]);
			}
		}
		new_text = join_char_and_free(new_text, text[i++]);
	}
	*cursor += i;
	return (new_text);
}

char	**get_words(char *line)
{
	char	**result;
	int		cursor;
	int		word_count;

	replace_free_sep(line, 0, -1, -1);
	result = x_malloc(sizeof(char *) * (ft_strlen(line) + 2));
	result[0] = 0;
	cursor = 0;
	word_count = 0;
	while (cursor < (int)ft_strlen(line))
	{
		result[word_count] = get_next_word(line + cursor, &cursor, 0);
		word_count++;
	}
	result[word_count] = ft_strdup("\x14"); // DANGER
	result[word_count + 1] = (NULL);
	return (result);
}

char 	**get_words_and_free(char *line)
{
	char	**result;

	result = get_words(line);
	free(line);
	return (result);
}
