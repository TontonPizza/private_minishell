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
		return (builtin_export(cmd));
	if (vo_strcmp(cmd[0], "unset") == 0)
		return builtin_unset(cmd);
	if (vo_strcmp(cmd[0], "cd") == 0)
		return (0);
	if (vo_strcmp(cmd[0], "ls") == 0)
		return (0);
	if (vo_strcmp(cmd[0], "pwd") == 0)
		return (0);
	if (vo_strcmp(cmd[0], "env") == 0)
		return (builtin_env());
	if (vo_strcmp(cmd[0], "exit") == 0)
		return (0);
	exec_pipe(cmd);
	return 0;
}

int		exec_pipe(char **cmd)
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
		return (0);
	if (pid == CHILD_PROCESS)
	{
		if (ft_strchr(cmd[0], '/') == 0)
			cmd[0] = path_to_binary(cmd[0]);
		/*
		 *
		 *  if cmd[0] is not an executable file
		 *  generate_error(binary not found)
		 *
		 */
		execve(cmd[0], cmd, get_env_as_array());
		free_split(cmd);
		exit(0);
	}
	waitpid(0, 0, 0);
	free_split(cmd);
	return (0);
}