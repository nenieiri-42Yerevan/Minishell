NAME		= minishell

TMP			= tmp

SRCS		= $(wildcard ./srcs/*.c)

OBJS		= $(patsubst ./srcs/%.c, ./$(TMP)/%.o, $(SRCS))

CC			= cc

CFALGS		= -Wall -Wextra -Werror

LIB			= ./libs

LIBFT		= $(LIB)/libft

LINKERS		= -lft -L$(LIBFT) -lreadline -L $(HOME)/lib

INCLUDES	= -I ./includes -I $(HOME)/include

RM			= rm -rf

.PHONY:		all clean fclean re

./tmp/%.o:	./srcs/%.c ./includes/minishell.h
			@$(CC) $(CFALGS) $(INCLUDES) -o $@ -c $<

all:		$(NAME)

$(TMP):
			@mkdir $(TMP)

$(NAME):	$(TMP) $(OBJS)
			@$(MAKE) -C $(LIBFT) all
			@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LINKERS) -o $(NAME)

clean:
			@$(MAKE) -C $(LIBFT) clean
			@$(RM) $(TMP)

fclean:		clean
			@$(MAKE) -C $(LIBFT) fclean
			@$(RM) $(NAME)

re:			fclean all
