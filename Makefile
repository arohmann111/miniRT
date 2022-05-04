# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afrasch <afrasch@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/03 09:52:37 by afrasch           #+#    #+#              #
#    Updated: 2022/05/03 19:36:28 by afrasch          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= miniRT

CFLAGS		= -Wall -Wextra -Werror

CC			= cc

SRC			:= main.c read_file.c \

LDLIBS		:= -lft

LIBDIRS		:= $(wildcard libs/*)
LDLIBS		:= $(addprefix -L./, $(LIBDIRS)) $(LDLIBS)
INCLUDES	:= -I./include/ $(addprefix -I./, $(addsuffix /include, $(LIBDIRS)))

SDIR		:= src
ODIR		:= obj
OBJS		:= $(addprefix $(ODIR)/, $(SRC:.c=.o))


# HEADER		= miniRT.h

RM			= rm -rf

all: $(NAME)

prep:
	mkdir -p $(ODIR)

$(NAME): prep $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDLIBS)

$(ODIR)/%.o: $(SDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


clean:
	$(RM) $(ODIR)
	$(RM) -r *.dSYM $(SDIR)/*.dSYM $(SDIR)/$(NAME)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)



.PHONY: all clean fclean re


# NAME	= miniRT

# CFLAGS	= -Wall -Wextra -Werror

# LIBS	= 

# CC		= cc

# SRC		= start.c \

# OBJ		= $(SRC:.c=.o)

# HEADER	= miniRT.h

# RM		= rm -rf

# all: $(NAME)

# $(NAME): $(OBJ) $(HEADER)
# 	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBS)

# clean:
# 	$(RM) $(OBJ)

# fclean: clean
# 	$(RM) $(NAME)

# re: fclean $(NAME)

# .PHONY: all clean fclean re
