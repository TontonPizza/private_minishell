/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 14:52:43 by nagresel          #+#    #+#             */
/*   Updated: 2021/02/01 11:40:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	handle_sig(int sig_val)
{
	if (sig_val == SIGINT)
	{
		last_return_code(set, 128 + sig_val);
		write(2, "\n", 1);
		ft_putstr_fd("tontonPizza >", 2);
	}
	else if (sig_val == SIGQUIT)
	{
		last_return_code(set, 0);//pas sûr
		ft_putstr_fd("\b\b  \b\b", 2);
	}
}

void	init_sig(void)
{
	if (signal(SIGINT, handle_sig) == SIG_ERR)
		exit(EXIT_FAILURE);
	if (signal(SIGQUIT, handle_sig) == SIG_ERR)
		exit(EXIT_FAILURE);
}

static void	handle_sig_exec(int sig_val)
{
	if (sig_val == SIGINT)
	{
		last_return_code(set, 128 + sig_val);
		write(2, "\n", 1);
	}
	else if (sig_val == SIGQUIT)
	{
		last_return_code(set, 128 + sig_val);//pas sûr
		//y-a-il un message a envoyer??
	}
}

void	init_sig_exec(int nb)
{
	if (signal(SIGINT, handle_sig_exec) == SIG_ERR)
		exit(EXIT_FAILURE);
	if (signal(SIGQUIT, handle_sig_exec) == SIG_ERR)
		exit(EXIT_FAILURE);
}
