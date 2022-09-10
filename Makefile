NAME	=	get_next_line.a
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
LIBC	=	ar rcs
RM		=	rm -rf
SRCS	=	get_next_line.c get_next_line_utils.c
OBJS	=	${SRCS:.c=.o}
BSRCS	=	get_next_line_bonus.c get_next_line_utils.c
BOBJS	=	${BSRCS:.c=.o}

all : $(NAME)

ifeq ($(filter bonus, $(MAKECMDGOALS)), bonus)
$(NAME) : $(OBJS) $(BOBJS)
	$(LIBC) $(NAME) $(OBJS) $(BOBJS)
else
$(NAME) : $(OBJS)
	$(LIBC) $(NAME) $(OBJS)
endif

bonus : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJS) $(BOBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re