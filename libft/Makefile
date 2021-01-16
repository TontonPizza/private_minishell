# ************************************************************************** # 
#                                                                            #
#                                                        :::      ::::::::   #
#   Makefile                                           :+:      :+:    :+:   #
#                                                    +:+ +:+         +:+     #
#   By: vo-nguye <vo-nguye@42.fr>                  +#+  +:+       +#+        #
#                                                +#+#+#+#+#+   +#+           #
#   Created: 07/10/2019 13:30:56 by vo-nguye          #+#    #+#             #
#   Updated: 07/10/2019 13:30:56 by vo-nguye         ###   ########.fr       #
#                                                                            #
# ************************************************************************** #

NAME = libft.a

SRC = 	ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	  	ft_isdigit.c ft_isprint.c \
	  	ft_itoa.c ft_calloc.c x_malloc.c\
	  	ft_memccpy.c ft_memchr.c ft_memcpy.c ft_memcmp.c\
	  	ft_memmove.c ft_memset.c ft_putchar_fd.c \
	  	ft_putendl_fd.c ft_putnbr_fd.c \
	  	ft_putstr_fd.c ft_split.c ft_strchr.c\
	  	ft_strdup.c is_char_in_set.c\
	  	ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
	  	ft_strmapi.c ft_strncmp.c\
	  	ft_strnstr.c ft_strrchr.c\
	  	ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
	  	get_next_line.c special_malloc.c split_handlers.c string_handlers.c \
	  	search_word_text.c split_handlers_2.c \
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstiter.c\
		ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstmap.c


OBJ = $(subst .c,.o,$(SRC))
BONUS_OBJ = $(subst .c,.o,$(BONUS))

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

OBJ : $(subst .o,.c,$(SRC))
	gcc -c $(CFLAGS) $(SRC)

bonus :
	    gcc $(CFLAGS) -c $(BONUS)
	    ar rc $(NAME) $(BONUS_OBJ)
	    ranlib $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)


clean:
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

main : main.c libft.a
	gcc -Wall -Wextra -Werror main.c libft.a

.PHONY: clean fclean all re