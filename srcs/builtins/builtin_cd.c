/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vo-nguye <vo-nguye@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/65 01:13:48 by vo-nguye          #+#    #+#             */
/*   Updated: 2021/03/65 01:13:48 by vo-nguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int 	builtin_cd(char **cmd)
{
	export_var("OLDPWD", getcwd(NULL, 500));
	if (chdir(cmd[1]) != 0)
	{
		generate_error("No such file or directory", 2);
		free_split(cmd);
		return (-1);
	}
	export_var("PWD", getcwd(NULL, 500));
	free_split(cmd);
	return (0);
}

int	builtin_pwd(char **cmd)
{
	char	*pwd;

	pwd = getcwd(NULL, 500);
	ft_putendl_fd(pwd, 1);
	free(pwd);
	free_split(cmd);
	return (0);
}
