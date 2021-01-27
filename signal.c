/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 14:52:43 by nagresel          #+#    #+#             */
/*   Updated: 2021/01/27 16:31:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void    handle_sig(int sig_val)
{
    if (sig_val == SIGINT)
    {
        last_return_code(set, 128 + sig_val);
        write(2, "\n", 1);
        ft_put_str_fd("tontonPizza >", 2);
    }
    else if (sig_val == SIGQUIT)
    {
        last_return_code(set, 0);//pas sûr
        write(2, "\b\b  \b\b", 6);
    }
}

void    init_sig(void)
{
    int sig_val;

    sig_val = signal(SIGINT, handle_sig);
    if (sig_val == SIG_ERR)
        exit(EXIT_FAILURE);
    sig_val = signal(SIGQUIT, handle_sig);
    if (sig_val == SIG_ERR)
        exit(EXIT_FAILURE);
}

void    handle_sig_exec(int sig_val)
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

void    init_sig_exec(int nb)
{
    int sig_val;

    sig_val = signal(SIGINT, handle_sig_exec);
    if (sig_val == SIG_ERR)
        exit(EXIT_FAILURE);
    sig_val = signal(SIGQUIT, handle_sig_exec);
    if (sig_val == SIG_ERR)
        exit(EXIT_FAILURE);
}
