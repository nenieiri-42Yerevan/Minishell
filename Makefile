NAME		= minishell

TMP			= tmp

SRCS		= $(wildcard ./srcs/*.c)

OBJS		= $(patsubst ./srcs/%.c, ./$(TMP)/%.o, $(SRCS))

CC			= cc

CFALGS		= -Wall -Wextra -Werror

LIB			= ./libs

LIBFT		= $(LIB)/libft

LINKERS		= -lft -L$(LIBFT) -lreadline

#LDGLAGS 	= -L /Users/vismaily/lib

#CPPFLAGS	= -I /Users/vismaily/include

INCLUDES	= -I ./includes

RM			= rm -rf

.PHONY:		all clean fclean re

./tmp/%.o:	./srcs/%.c ./includes/minishell.h
			@$(CC) $(CFALGS) $(INCLUDES) -o $@ -c $<
#			@$(CC) $(CFALGS) $(INCLUDES) $(CPPFLAGS) -o $@ -c $<

all:		$(NAME)

$(TMP):
			@mkdir $(TMP)

$(NAME):	$(TMP) $(OBJS)
			@$(MAKE) -C $(LIBFT) all
			@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LINKERS) -o $(NAME)
#			@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LINKERS) $(LDFLAGS) -o $(NAME)

clean:
			@$(MAKE) -C $(LIBFT) clean
			@$(RM) $(TMP)

fclean:		clean
			@$(MAKE) -C $(LIBFT) fclean
			@$(RM) $(NAME)

re:			fclean all
