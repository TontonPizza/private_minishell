/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vo-nguye <vo-nguye@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 08:18:38 by vo-nguye          #+#    #+#             */
/*   Updated: 2021/01/06 08:18:38 by vo-nguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int mainc()
{
	char *cm_1[] = {"/usr/bin/ping", "-c", "2", "google.com", NULL};
	char *cm_2[] = {"/bin/grep", "packets", NULL};
	char *cm_3[] = {"/bin/grep", "0", NULL};
	char *cm_4[] = {"/bin/grep", "0", NULL};

	char **cmd_pipe[] = {cm_1, cm_2, cm_3, NULL};

	char **cmd_err[] = {cm_1, cm_4, cm_3, NULL};

	errno = 0;
	g_stdout_copy = dup(1);

	dup2(g_stdout_copy, 2);

	execute_cmd_pipe(cmd_pipe, -1);
	return 0;
}

int 	is_valid(char ***cmds) // exemple
{
	// replace ENV check if file exist qnd is executable

	return (0);
}

int 	exec_cmd(char ***cmd)
{
	// treat redirections
	execve(cmd[0][0], cmd[0], 0);
	exit(0);
}

int		exec_fork(char ***cmds, int pipe_fd)
{
	pid_t	pid;
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == CHILD_PROCESS && close(pipe_fd) == 0)
		exec_cmd(cmds);
	return (0);
}

int 	execute_cmd_pipe(char ***cmds, int source)
{
	pid_t		pid;
	int 		pipe_fd[2];

	if (cmds[0] == NULL)
		return (close(source));
	if (pipe(pipe_fd) < 0)
		return (-1);
	if (cmds[1] == NULL) // if it's the last command of the list => output = stdout
		dup2(g_stdout_copy, 1);
	else
		dup2(pipe_fd[1], 1);
	dup2(source, 0);
	if (is_valid(cmds) == 0)
		exec_fork(cmds, pipe_fd[0]);
	else
	{
		close(source);
		return (-1);
	}
	wait(0);
	close(pipe_fd[1]);
	close(source);
	return (execute_cmd_pipe(cmds + 1, pipe_fd[0]));
}