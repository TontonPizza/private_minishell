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
        	./libft/libft.a \


all: $(NAME)

./libft/libft.a:
					make -C ./libft/
					make clean -C ./libft

$(NAME): $(SRCS) minishell.h
		clang $(SRCS) ./srcs/tests/*.c ./libft/libft.a -o minishell


clear:	$(NAME)
		clear