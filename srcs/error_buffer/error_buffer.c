/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vo-nguye <vo-nguye@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/47 07:33:58 by vo-nguye          #+#    #+#             */
/*   Updated: 2021/02/47 07:33:58 by vo-nguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void 	display_error()
{
	char *error_msg = get_buffer_content();
	if (error_msg == 0)
		return ;
	ft_putendl_fd(error_msg, g_new_stdout);
}

int		clear_error_buffer(void)
{
	int fd;

	fd = open(path_to_buffer(get), O_TRUNC);
	if (fd < 0)
		return (-1);
	close(fd);
	return (0);
}

char	*get_buffer_content(void)
{
	char	*result;
	char	buffer[2];
	int		fd;

	result = ft_strdup("\0");
	fd = open(path_to_buffer(get), O_RDONLY);
	if (fd < 0)
		return (NULL);
	while (read(fd, buffer, 1))
	{
		buffer[1] = 0;
		result = ft_strjoin_and_free(result, buffer);
	}
	if (ft_strlen(result) == 0)
	{
		free(result);
		close(fd);
		return (NULL);
	}
	close(fd);
	return (result);
}

char	*path_to_buffer(int op)
{
	static char error_path[300];

	if (op == set)
	{
		(getcwd(error_path, 100));
		ft_memcpy(error_path + (ft_strlen(error_path)),
				  "/srcs/buffers/error.txt\0", 24);
		return (error_path);
	}
	if (op == get)
		return (error_path);
	return (NULL);
}


void generate_error(char *message)
{
	ft_putendl_fd(message, g_new_stderr);
}

int	is_there_an_error(void)
{
	char 	*str;

	str = get_buffer_content();
	if (str == 0 || ft_strlen(str) == 0)
	{
		free(str);
		return (FALSE);
	}
	free(str);
	return (TRUE);
}

int initialize_path_to_buffer(void)
{
	int fd;

	fd = open(path_to_buffer(set), O_TRUNC | O_RDWR);
	if (fd < 0)
		return (-1);
	g_new_stderr = fd;
	dup2(g_new_stderr, 2);
	return (0);
}
