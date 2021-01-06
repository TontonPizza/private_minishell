//
// Created by lolito on 05/01/2021.
//

#ifndef MINISHELL_MINISHELL_H
#define MINISHELL_MINISHELL_H

#	ifndef CHILD_PROCESS
#		define CHILD_PROCESS 0
#	endif

#include "libft/libft.h"

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>

int		g_stdout_copy;

int 	execute_cmd_pipe(char ***cmds, int source);


#endif //MINISHELL_MINISHELL_H
