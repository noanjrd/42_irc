# enlever le relink

NAME = ircserv
CC = g++
FLAGS = -Wall -Wextra -Werror -std=c++98 -g3
RM = rm -rf

SRCS = srcs/main.cpp\
	srcs/utils.cpp\
	srcs/Client.cpp\
	srcs/Chanel.cpp\
	srcs/server/Server.cpp\
	srcs/server/poll.cpp\
	srcs/server/processmessages.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME) clean

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(LIBS)

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all fclean clean re