NAME = minishell


SRCS	=	minishell.c \
			./srcs/execute_cmd_pipe.c \
			./srcs/line_to_words.c \
			./srcs/words_to_token.c \
			./srcs/t_token_list_manipulation.c \
			./srcs/env_manipulation.c \
			./srcs/env_manipulation_2.c \
			./srcs/parsing_token_list.c \
        	./libft/libft.a \


all: $(NAME)

./libft/libft.a:
					make -C ./libft/
					make clean -C ./libft

$(NAME): $(SRCS) minishell.h
		clang $(SRCS) ./libft/libft.a -o minishell


clear:	$(NAME)
		clear