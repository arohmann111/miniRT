

NAME		= miniRT

CFLAGS		= -Wall -Wextra -Werror -O2

CC			= cc

SRC			:= main.c read_file.c vec_math.c window.c send_rays.c trace_rays.c \
				multisample.c\

LDLIBS		:= -lft -lglfw -L "/Users/$(USER)/goinfre/.brew/opt/glfw/lib/" -lMLX42

LIBDIRS		:= $(wildcard libs/*)
LDLIBS		:= $(addprefix -L./, $(LIBDIRS)) $(LDLIBS)
INCLUDES	:= -I./include/ $(addprefix -I./, $(addsuffix /include, $(LIBDIRS)))

SDIR		:= src
ODIR		:= obj
OBJS		:= $(addprefix $(ODIR)/, $(SRC:.c=.o))

RM			= rm -rf

all: $(NAME)

$(NAME): $(ODIR) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDLIBS)

$(ODIR)/%.o: $(SDIR)/%.c
	mkdir -p $(ODIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(ODIR)
	$(RM) -r *.dSYM $(SDIR)/*.dSYM $(SDIR)/$(NAME)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)



.PHONY: all clean fclean re
