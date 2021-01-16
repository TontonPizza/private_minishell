//
// Created by lolito on 05/01/2021.
//

#ifndef MINISHELL_MINISHELL_H
#define MINISHELL_MINISHELL_H

#	ifndef CHILD_PROCESS
#		define CHILD_PROCESS 0
#	endif

#ifndef TYPE_WORD
#   define TYPE_WORD 0
#endif

#ifndef TYPE_PIPE
#   define TYPE_PIPE 1
#endif

#ifndef TYPE_OUT
#   define TYPE_OUT 2
#endif

#ifndef TYPE_APPEND
#   define TYPE_APPEND 3
#endif

#ifndef TYPE_IN
#   define TYPE_IN 4
#endif

#ifndef TYPE_END
#   define TYPE_END 5
#endif

#include "libft/libft.h"

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

typedef struct 	s_token
{
	char				*token;
	int					type;
	struct	s_token		*next;
}				t_token;

typedef struct 	s_env_var
{
	char				*name;
	char 				*value;
	struct s_env_var 	*next;
}				t_env_var;

int			g_stdout_copy;
int 		g_stderr_copy;
int 		g_last_exit_value;

t_env_var 	*env_list;
char 		*requested_env_var;
char 		**all_env_as_array;

int 		execute_cmd_pipe(char ***cmds, int source);
char		**get_words(char *line);
char 		**get_words_and_free(char *line);
int 		env_var_count(void);


// Token list
void		token_add_back(t_token **list, t_token *item);
int 		token_type(char *word);

// ENV MANIPULATION
void 		destroy_env(void);
char 		*get_value_and_free_or_not(char *name, int free_or_not);
void 		init_env_list();

// Parsing cleaning
char		*clean_word(char *word);
char 		**clean_words_up_to_semicolon(char **words);


#endif //MINISHELL_MINISHELL_H
