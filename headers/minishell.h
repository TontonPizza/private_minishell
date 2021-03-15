//
// Created by lolito on 05/01/2021.
//

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef CHILD_PROCESS
#  define CHILD_PROCESS 0
# endif

# include "../libft/libft.h"

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
# include <curses.h>
# include <term.h>

# ifndef FREE_ARG
#  define FREE_ARG 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef NO_FREE
#  define NO_FREE 0
# endif

# ifndef SIMPLE_QUOTE
#  define SIMPLE_QUOTE 11
# endif

# ifndef DOUBLE_QUOTE
#  define DOUBLE_QUOTE 12
# endif

# ifndef ARROW_LEFT
#  define ARROW_LEFT '\x11'
# endif

# ifndef ARROW_RIGHT
#  define ARROW_RIGHT '\x12'
# endif

# ifndef PIPE_C
#  define PIPE_C '\x13'
# endif

# ifndef SEMI_COLON
#  define SEMI_COLON '\x14'
# endif

# ifndef SPACE_C
#  define SPACE_C '\x15'
# endif

# ifndef IGNORE_ERROR
#  define IGNORE_ERROR -42
# endif

# ifndef LORIE
#  define LORIE "Xx_Lorie4ever69@$_xX"
# endif

# ifndef PROMPT
#  define PROMPT " ༼ つ°ᴥ° ༽つ "
# endif

enum e_error_type
{
	CODE_OK,
	CODE_NO_SUCH_FILE_OR_DIRECTORY,
	CODE_SYNTAX_ERROR
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
	op_close,
	first_call,
	add,
	del,
	hashtag
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

//int		g_new_stderr;
//int		g_new_stdin;
int			g_new_stdout;

int			g_out(int op, int val);
int			g_in(int op, int val);
int			g_err(int op, int val);

// ENV MANIPULATION

void		init_env_list(void);
void		destroy_env(void);
void		import_all_env(char **env);
char		**get_env_as_array(void);
char		*get_value_and_free_or_not(char *name, int free_or_not);
int			env_var_count(void);
t_env_data	*get_meta_data(int first_call);
int			last_return_code(int op, int value);

void		export_var(char *name, char *value);
void		unset_env(char *name);

// PARSING
void		replace_free_sep(char *line, int bs, int dq, int sq);
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
char		*get_argv(int op, int index, char **argv);
char		*expand_env_variable(char *word, int *cursor);
char		**expand_word(char *word);
char		*expand_backslash_and_parameters(char *word);
int			next_cut(char *word);
char		**word_split(char *word);
char		*remove_quote(char *word);

// TOKENIZER
void		words_to_tokens_and_offset_words(char ***words, t_token **list);
void		add_words_to_token_list(t_token **list, char **words);

// EXECUTION LOOP

void		write_prompt(void);
void		routine(char *line);
int			check_conformity(t_token *list);
char		**export_token_to_command(t_token *list);
int			execution_loop(t_token *list, int source);

int			source_fd(int source, t_token *list);
int			dest_fd(int pipe_fd, t_token *list);
// ERROR BUFFER
int			initialize_path_to_buffer(void);
int			generate_error(char *message, int error_code);
void		display_error(void);
//int		g_new_stderr(int op, int value);
char		*path_to_buffer(int op);
int			clear_error_buffer(void);
char		*get_buffer_content(void);
int			is_there_an_error(void);

// BUILD INS

char		*path_to_binary(char *word);
int			search_binary_or_builtin_and_exec(char **cmd);
int			exec_pipe(char **cmd);
int			builtin_env(char **cmd);
int			builtin_export(char **cmd);
int			export_word(char *word);
int			builtin_unset(char **cmd);
int			builtin_echo(char **cmd);
int			builtin_cd(char **cmd);
int			isfile(char *path);
int			builtin_pwd(char **cmd);
int			builtin_exit(char **cmd, int size);
int			exit_code(int op, int val);
void		write_with_double_quotes(char *word);
// SIGNALS
void		custom_msg_exit_code(int code);
int			get_quit_flag(int op, int val);
void		sighandler_int(int signum);
void		sighandler_quit(int signum);

/***********************************/
/***********************************/
// BULLSHIT

char		*join_2_char_bullshit(char *src, char *word, int *i);
int			get_pid(int op, int val);
int			ptr_p(int *ptr, int i);
char		**fix_words(char **words);
int			has_out(t_token *list);
void		free_at_exit(int op, char **p1, t_token *p2);
void		free_if_not_null(void *ptr);
int			last_pipe(int op, int value);
char		*place_zero(char *result, int i);
char		tr(char a, char b, char c);

void		log_error(char *msg, char *complement);

#endif //MINISHELL_MINISHELL_H
