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

#include "../../headers/minishell.h"

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
	static char	error_path[300];

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

int	generate_error(char *message, int error_code)
{
	if (last_return_code(get, 0) == 0 && error_code != IGNORE_ERROR)
	{
		last_return_code(set, error_code);
	}
	ft_putendl_fd(message, g_err(get, 0));
	return (-1);
}

int	is_there_an_error(void)
{
	char	*str;

	str = get_buffer_content();
	if (str == 0 || ft_strlen(str) == 0)
	{
		free(str);
		return (FALSE);
	}
	free(str);
	return (TRUE);
}

int	initialize_path_to_buffer(void)
{
	int	fd;

	fd = open(path_to_buffer(set), O_TRUNC | O_RDWR);
	if (fd < 0)
		return (-1);
	g_err(set, fd);
	dup2(g_err(get, 0), 2);
	return (0);
}
