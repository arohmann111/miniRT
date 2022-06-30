# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afrasch <afrasch@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/30 11:47:42 by arohmann          #+#    #+#              #
#    Updated: 2022/06/30 14:29:08 by afrasch          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= miniRT

CFLAGS		= -Wall -Wextra -Werror -O2

CC			= cc

SRC			:= main.c read_file.c read_utils.c read_elements.c \
				read_items.c read_objs.c read_objs_2.c light.c error.c \
				vec_math.c vec_math2.c window.c send_rays.c trace_rays.c \
				colors.c colors2.c find_t.c find_t2.c intersect.c multisample.c\

LLIB		:= -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/" -L libs/MLX42 -lMLX42

LIBRARIES	= -L libs/libft -lft $(LLIB)
INCLUDES	= ./include/

SDIR		:= src
ODIR		:= obj
OBJS		:= $(addprefix $(ODIR)/, $(SRC:.c=.o))

RM			= rm -rf

all: $(NAME)

$(NAME): libs/libft/libft.a $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBRARIES) -o $(NAME)

$(ODIR)/%.o: $(SDIR)/%.c
	mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

clean:
	@make -C libs/libft clean
	$(RM) $(ODIR)
	$(RM) -r *.dSYM $(SDIR)/*.dSYM $(SDIR)/$(NAME)

fclean: clean
	@make -C libs/libft fclean
	$(RM) $(NAME)

re: fclean $(NAME)

libs/libft/libft.a:
	@make -C ./libs/libft all

.PHONY: all clean fclean re