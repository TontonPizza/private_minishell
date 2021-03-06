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

#include "../../minishell.h"

void	sighandler_int(int signum)
{
	last_return_code(set, 128 + signum);
	write(0, "\n", 1);
	write_prompt();
}

void	sighandler_quit(int signum)
{
	last_return_code(set, 128 + signum);
	write(g_new_stdout, "s-exit\n", 6);
	builtin_exit(0);
}
