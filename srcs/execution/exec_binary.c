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

#include "../../headers/minishell.h"

int	isfile(char *path)
{
	struct stat	sb;
	int			i;

	i = 0;
	if (stat(path, &sb) == 0 && sb.st_mode & S_IXUSR)
		return (1);
	if (stat(path, &sb) == 0 && sb.st_mode & S_IFREG)
		return (126);
	return (127);
}

int	search_binary_or_builtin_and_exec(char **cmd)
{
	if (vo_strcmp(cmd[0], "ignore") == 0)
		return (0);
	if (vo_strcmp(cmd[0], "echo") == 0)
		return (builtin_echo(cmd));
	if (vo_strcmp(cmd[0], "export") == 0)
		return (builtin_export(cmd));
	if (vo_strcmp(cmd[0], "unset") == 0)
		return (builtin_unset(cmd));
	if (vo_strcmp(cmd[0], "cd") == 0)
		return (builtin_cd(cmd));
	if (vo_strcmp(cmd[0], "pwd") == 0)
		return (builtin_pwd(cmd));
	if (vo_strcmp(cmd[0], "env") == 0)
		return (builtin_env(cmd));
	if (vo_strcmp(cmd[0], "exit") == 0)
		return (builtin_exit(cmd));
	exec_pipe(cmd);
	return (0);
}

int	exec_pipe(char **cmd)
{
	pid_t	pid;
	char	*path;

	path = cmd[0];
	if (ft_strchr(cmd[0], '/') == 0)
		path = path_to_binary(cmd[0]);
	if (isfile(path) != 1)
	{
		free_split(cmd);
		return (generate_error("Command not found", isfile(path)));
	}
	pid = fork();
	if (get_pid(set, 10) && pid < 0)
		return (0);
	if (pid == CHILD_PROCESS)
	{
		if (ft_strchr(cmd[0], '/') == 0)
			cmd[0] = path_to_binary(cmd[0]);
		execve(cmd[0], cmd, get_env_as_array());
		free_split(cmd);
		exit(0);
	}
	waitpid(0, 0, 0);
	free_split(cmd);
	return (0);
}
