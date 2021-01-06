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

int main()
{
	char *cm_1[] = {"/bin/cat", "minishell.c", NULL};
	char *cm_2[] = {"/bin/grep", "if", NULL};
	char *cm_3[] = {"/bin/grep", "=", NULL};
	char *cm_4[] = {"/bin/grep", "0", NULL};
	char **cmd_pipe[] = {cm_1, cm_2, cm_3, cm_4, NULL};

	g_stdout_copy = dup(1);
	int k = execute_cmd_pipe(cmd_pipe, -1);

	ft_putnbr_fd(k, 1);
	ft_putchar_fd('\n', 1);
}