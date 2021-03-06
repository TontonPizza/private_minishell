NAME = minishell


SRCS	=	minishell.c \
			./srcs/environnement/env_manipulation.c \
			./srcs/environnement/env_manipulation_2.c \
			./srcs/environnement/last_return_code.c \
			./srcs/parsing/lexer.c\
			./srcs/parsing/lexer_2.c\
			./srcs/parsing/tokenizer.c\
			./srcs/parsing/expander.c\
			./srcs/parsing/expander_2.c\
			./srcs/parsing/token_manipulation.c\
			./srcs/execution/execution_loop.c \
			./srcs/execution/execution_loop_2.c \
			./srcs/error_buffer/error_buffer.c \
			./srcs/error_buffer/error_buffer_2.c \
			./srcs/builtins/path_to_binary.c \
			./srcs/execution/fd_manipulation.c \
			./srcs/execution/exec_binary.c \
			./srcs/builtins/builtin_env.c \
			./srcs/builtins/builtin_export_unset.c \
			./srcs/builtins/builtin_echo.c \
			./srcs/builtins/builtin_cd.c \
			./srcs/builtins/builtin_exit.c \
			./srcs/bullshit_functions/bullshit_functions.c \
			./srcs/bullshit_functions/bullshit_functions_2.c \
			./srcs/sighandlers/sighandlers.c \
        	./libft/libft.a \


all: $(NAME)

./libft/libft.a:
					make -C ./libft/
					make clean -C ./libft

$(NAME): $(SRCS) minishell.h Makefile
		clang $(SRCS) ./libft/libft.a -o minishell


clear:	$(NAME)
		clear