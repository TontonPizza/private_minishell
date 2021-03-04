/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vo-nguye <vo-nguye@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/63 14:58:49 by vo-nguye          #+#    #+#             */
/*   Updated: 2021/03/63 14:58:49 by vo-nguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int 	search_binary_or_builtin_and_exec(char **cmd)
{
	if (vo_strcmp(cmd[0], "echo") == 0)
		;
	if (vo_strcmp(cmd[0], "export") == 0)
		;
	if (vo_strcmp(cmd[0], "unset") == 0)
		;
	if (vo_strcmp(cmd[0], "cd") == 0)
		;
	if (vo_strcmp(cmd[0], "ls") == 0)
		;
	if (vo_strcmp(cmd[0], "pwd") == 0)
		;
	if (vo_strcmp(cmd[0], "env") == 0)
		;
	if (vo_strcmp(cmd[0], "exit") == 0)
		;

	return 0;
}
