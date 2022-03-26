NAME		= libft.a

SRCS		= $(shell find . -name '*.c')

OBJS		= $(SRCS:.c=.o)

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

INCLUDES	= -I../../includes

RM			= rm -f

.c.o:
			@${CC} ${CFLAGS} $(INCLUDES) -c $< -o ${<:.c=.o}

all:		$(NAME)

$(NAME):	$(OBJS)
			@ar rc $(NAME) $(OBJS)
			@ranlib $(NAME)

clean:
			@${RM} ${OBJS}

fclean:		clean
			@${RM} ${NAME}
	
re:			fclean all

.PHONY:		all clean fclean re
