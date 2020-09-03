SRCS			= free.c init.c main.c messages.c start.c status.c utils.c sem.c
OBJS			= $(SRCS:.c=.o)

CXX				= clang
RM				= rm -f
CXXFLAGS		= -Wall -Wextra -Werror -I. -lpthread

NAME			= philo_two

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re test