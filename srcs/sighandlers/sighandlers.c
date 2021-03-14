/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandlers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vo-nguye <vo-nguye@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/65 14:21:39 by vo-nguye          #+#    #+#             */
/*   Updated: 2021/03/65 14:21:39 by vo-nguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

//void	custom_msg_exit_code(int code)
//{
//	if (code == 214)
//		write(g_new_stdout, " trop d'arguments", 17);
//	if (code == 131 && get_quit_flag(get, 0) == 1)
//		write(g_new_stdout, " (core dumped)", 14);
//	write(g_new_stdout, "\n", 1);
//}

int	get_pid(int op, int val)
{
	static int	pid;

	if (op == set)
		pid = val;
	return (pid);
}

void	sighandler_int(int signum)
{
	last_return_code(set, 128 + signum);
	write(1, "\n", 1);
	write_prompt();
}

int 	get_quit_flag(int op, int val)
{
	static int	pid;

	if (op == set)
		pid = val;
	return (pid);
}

void	sighandler_quit(int signum)
{
	if (get_pid(get, 0) < 0)
	{
		write(g_new_stdout, "\b\b  \b\b", 6);
		return ;
	}
	(void)signum;
	get_quit_flag(set, 1);
	last_return_code(set, 131);
}
