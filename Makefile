SRCS			= main.c utils.c philosophers.c status.c logs.c free.c
OBJS			= $(SRCS:.c=.o)

CXX				= clang
RM				= rm -f
CXXFLAGS		= -Wall -Wextra -Werror -I. -lpthread

NAME			= philo_one

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)


.PHONY:			all clean fclean re test