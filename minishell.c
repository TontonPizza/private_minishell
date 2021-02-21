/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vo-nguye <vo-nguye@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 08:16:55 by vo-nguye          #+#    #+#             */
/*   Updated: 2021/01/06 08:16:55 by vo-nguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//void test_env();
//void test_parsing();

void	test_thing(t_token *list)
{
	int i = source_fd(-1, list);

	printf("%d\n", i);
}

int main(int argc, char **argv)
{
	initialize_path_to_buffer();
	init_env_list();

	int fd = open(argv[1], O_CREAT | O_RDWR, 0777);

	printf("fd = %d\n", fd);

	write(fd, "ssxx", 3);

//	clear_error_buffer();
}