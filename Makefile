# enlever le relink

NAME = ircserv
CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98 -g3
RM = rm -rf

SRCS = srcs/main.cpp\
	srcs/utils.cpp\
	srcs/client/Client.cpp\
	srcs/client/ClientConnexion.cpp\
	srcs/chanel/Chanel.cpp\
	srcs/server/Server.cpp\
	srcs/server/poll.cpp\
	srcs/server/processmessages.cpp\
	srcs/commands/JOIN.cpp\
	srcs/commands/NAMES.cpp\
	srcs/commands/KICK.cpp\
	srcs/commands/TOPIC.cpp\
	srcs/commands/PRIVMSG.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(LIBS)
	make clean

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all clean

.PHONY: all fclean clean re