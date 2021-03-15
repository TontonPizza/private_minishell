/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_buffer_2.                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vo-nguye <vo-nguye@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/64 20:31:15 by vo-nguye          #+#    #+#             */
/*   Updated: 2021/03/64 20:31:15 by vo-nguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void 	set_error_num_according_to_msg(char *msg)
{
	last_return_code(set, 1);
	if (search_word(msg, "such") == 1)
		last_return_code(set, 2);
	if (search_word(msg, "found") == 1)
		last_return_code(set, 127);
	return ;
}

void 	display_error(void)
{
	char	*error_msg;

	error_msg = get_buffer_content();
	if (error_msg == 0 || ft_strlen(error_msg) == 0)
	{
		last_return_code(set, 0);
		free(error_msg);
		return ;
	}
	else
		set_error_num_according_to_msg(error_msg);
	ft_putstr_fd(error_msg, g_new_stdout);
	free(error_msg);
	clear_error_buffer();
}

int	clear_error_buffer(void)
{
	int	fd;

	fd = open(path_to_buffer(get), O_TRUNC);
	if (fd < 0)
		return (-1);
	close(fd);
	return (0);
}
