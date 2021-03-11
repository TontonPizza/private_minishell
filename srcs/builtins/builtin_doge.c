/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_doge.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vo-nguye <vo-nguye@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/70 20:52:02 by vo-nguye          #+#    #+#             */
/*   Updated: 2021/03/70 20:52:02 by vo-nguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char 	*path_to_curl(int op, char *val)
{
	static char path[500];
	int 		i;

	i = 0;
	if (op == set)
	{
		while (val && val[i] && i < 490)
		{
			path[i] = val[i];
			i++;
		}
		path[i] = 0;
		return (0);
	}
	return (ft_strdup(path));
}

void init_doge(void)
{
	char 	*path;

	path = path_to_binary("curl");
	path_to_curl(set, path);
	free(path);
}

int	builtin_doge(char **cmd)
{
	free_split(cmd);
	cmd = x_malloc(sizeof (char *) * 3);
	cmd[0] = path_to_curl(get, 0);
	cmd[1] = ft_strdup("https://gist.githubusercontent.com/");
	cmd[1] = ft_strjoin_and_free(cmd[1], "hoserdude/9661c9cdc4b59cf5f001/");
	cmd[1] = ft_strjoin_and_free(cmd[1], "raw/5972d4d838691c1a1f33fb");
	cmd[1] = ft_strjoin_and_free(cmd[1], "274f97fa0b403d10bd/doge.txt");
	cmd[2] = 0;
	exec_pipe(cmd);
	return (0);
}
