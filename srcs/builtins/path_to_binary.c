/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_to_binary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vo-nguye <vo-nguye@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/47 08:22:26 by vo-nguye          #+#    #+#             */
/*   Updated: 2021/02/47 08:22:26 by vo-nguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*path_to_binary(char *word)
{
	char			*path;
	char			**split_path;
	struct stat		stat_p;
	int				i;

	path = get_value_and_free_or_not("PATH", 0);
	split_path = ft_split(path, ':');
	free(path);
	path = NULL;
	i = 0;
	while (split_path[i])
	{
		split_path[i] = ft_strjoin_and_free(split_path[i], "/");
		split_path[i] = ft_strjoin_and_free(split_path[i], word);
		if (stat(split_path[i], &stat_p) == 0 && path == NULL)
			path = ft_strdup(split_path[i]);
		free(split_path[i]);
		i++;
	}
	free(split_path);
	if (stat(path, &stat_p) == 0)
		return (path);
	return (NULL);
}
