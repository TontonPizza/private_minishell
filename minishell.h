//
// Created by lolito on 05/01/2021.
//

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef CHILD_PROCESS
#  define CHILD_PROCESS 0
# endif

# include "libft/libft.h"
# include "srcs/tests/tests.h"

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>

# ifndef FREE_ARG
#  define FREE_ARG 1
# endif

# ifndef SIMPLE_QUOTE
#  define SIMPLE_QUOTE 43
# endif

# ifndef DOUBLE_QUOTE
#  define DOUBLE_QUOTE 126
# endif

enum e_error_type
{
	CODE_OK,
	CODE_NO_SUCH_FILE_OR_DIRECTORY,
	CODE_SYNTAX_ERROR

};

enum e_bool_type
{
	FALSE,
	TRUE,
};

enum e_token_type_code
{
	TYPE_WORD,
	TYPE_PIPE,
	TYPE_OUT,
	TYPE_APPEND,
	TYPE_IN,
	TYPE_END
};

enum e_operation_type
{
	get,
	set,
	op_close
};

typedef struct s_token
{
	char				*token;
	int					type;
	struct s_token		*next;
}					t_token;

typedef struct s_env_var
{
	char				*name;
	char				*value;
	struct s_env_var	*next;
}					t_env_var;

typedef struct s_env_data
{
	t_env_var	*env_list;
	char		*requested_env_var;
	char		**all_env_as_array;
}					t_env_data;

int         g_new_stderr;
int 		g_new_stdin;
int			g_new_stdout;


int 		debug_loop;
int 		log_file;

// ENV MANIPULATION
void		init_env_list(void);
void		destroy_env(void);

char		**get_env_as_array(void);
char		*get_value_and_free_or_not(char *name, int free_or_not);
int			env_var_count(void);
t_env_data	*get_meta_data(int first_call);
int			last_return_code(int op, int value);

void		export_var(char *name, char *value);
void		unset_env(char *name);

// PARSING

char		**get_words_and_free(char *line);
char		**get_words(char *line);
char		*clean_word(char *word);
int			token_type(char *word);

// TOKENS
t_token		*token_constructor(char *name, int type, int free_val);
void		token_list_add_last(t_token **first_element, t_token *item);
void		token_destructor(t_token *item);
void		destroy_token_list(t_token *item);
int			token_list_size(t_token *list);

// EXPANDER
char 		*expand_env_variable(char *word, int *cursor);
char 		**expand_word(char *word);
char		*expand_backslash_and_parameters(char *word);
int 		next_cut(char *word);
char 		**word_split(char *word);
char 		*remove_quote(char *word);

// TOKENIZER
void		words_to_tokens_and_offset_words(char ***words, t_token **list);
void		add_words_to_token_list(t_token **list, char **words);


// EXECUTION LOOP

int			check_conformity(t_token *list);
char 		**export_token_to_command(t_token *list);
int 		execution_loop(t_token *list, int source);

int 		source_fd(int source, t_token *list);
int 		dest_fd(int pipe_fd, t_token *list);
// ERROR BUFFER
int		initialize_path_to_buffer(void);
void 	generate_error(char *message);
void 	display_error();
//int		g_new_stderr(int op, int value);
char	*path_to_buffer(int op);
int		clear_error_buffer(void);
char	*get_buffer_content(void);
int		is_there_an_error(void);


// BUILD INS

char		*path_to_binary(char *word);
int 		search_binary_or_builtin_and_exec(char **cmd);
int			exec_pipe(char **cmd);
int 		builtin_env(void);
/***********************************/
/***********************************/


void 	log_error(char *msg, char *complement);


#endif //MINISHELL_MINISHELL_H
