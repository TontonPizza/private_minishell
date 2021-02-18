/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_manipulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vo-nguye <vo-nguye@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/48 10:01:13 by vo-nguye          #+#    #+#             */
/*   Updated: 2021/02/48 10:01:13 by vo-nguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		error_msg(char *msg)
{
	ft_putstr_fd("Error opening file : ", 2);
	ft_putendl_fd(msg, 2);
	return (-1);
}

int 	source_fd(int source, t_token *list)
{
	t_token *cursor;
	int 	last_fd;

	cursor = list;
	last_fd = source;
	while (cursor && cursor->type != TYPE_PIPE)
	{
		printf("token = %s\n", cursor->token);
		if (cursor->type == TYPE_IN)
		{
			close(last_fd);
			cursor = cursor->next;
			last_fd = open(cursor->token, O_RDONLY);
			if (last_fd < 0)
				return (error_msg(cursor->token));
		}
		cursor = cursor->next;
	}
	dup2(last_fd, 0);
	return (last_fd);
}

int 	dest_fd(int pipe_fd, t_token *list)
{
	return 0;
}