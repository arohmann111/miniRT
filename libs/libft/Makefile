# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afrasch <afrasch@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/21 16:25:20 by afrasch           #+#    #+#              #
#    Updated: 2022/05/30 16:57:04 by afrasch          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_atod.c \
ft_atoi.c \
ft_bzero.c \
ft_calloc.c \
ft_free_array.c \
ft_intlen.c \
ft_isalnum.c \
ft_isalpha.c \
ft_isascii.c \
ft_isdigit.c \
ft_isprint.c \
ft_itoa.c \
ft_memchr.c \
ft_memcmp.c \
ft_memcpy.c \
ft_memmove.c \
ft_memset.c \
ft_putchar_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c \
ft_putstr_fd.c \
ft_split.c \
ft_strchr.c \
ft_strcmp.c \
ft_strdup.c \
ft_striteri.c \
ft_strjoin.c \
ft_strlcat.c \
ft_strlcpy.c \
ft_strlen.c \
ft_strmapi.c \
ft_strncmp.c \
ft_strnstr.c \
ft_strrchr.c \
ft_strrncmp.c \
ft_strtrim.c \
ft_substr.c \
ft_tolower.c \
ft_toupper.c \
get_next_line.c \

OBJ	=	$(SRC:.c=.o)

BONUS_SRC	=	ft_lstnew.c \
				ft_lstadd_front.c \
				ft_lstsize.c \
				ft_lstlast.c \
				ft_lstadd_back.c \
				ft_lstdelone.c \
				ft_lstclear.c \
				ft_lstiter.c \
				ft_lstmap.c \

BONUS_OBJ	=	$(BONUS_SRC:.c=.o)

CC		=		gcc

CFLAGS	=		-Wall -Wextra -Werror

AR		=		ar rc

RM		=		rm -f

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all:	bonus

$(NAME):	$(OBJ)
	@$(AR) $(NAME) $(OBJ)

bonus:	$(NAME) $(BONUS_OBJ)
	@$(AR) $(NAME) $(BONUS_OBJ)

clean:
	@$(RM) $(OBJ) $(BONUS_OBJ)

fclean:	clean
	@$(RM) $(NAME)

re:	fclean all
