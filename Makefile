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
	srcs/server/signals.cpp\
	srcs/commands/JOIN.cpp\
	srcs/commands/NAMES.cpp\
	srcs/commands/KICK.cpp\
	srcs/commands/TOPIC.cpp\
	srcs/commands/PRIVMSG.cpp\
	srcs/commands/QUIT.cpp\
	srcs/commands/PART.cpp\
	srcs/commands/MODE.cpp\
	srcs/commands/INVITE.cpp\
	srcs/commands/PING.cpp\

OBJS = $(SRCS:.cpp=.o)

BOT_NAME = bot
BOT_SRCS = srcs/bot/bot_ping.cpp

all: $(NAME) $(BOT_NAME)

$(BOT_NAME):
	$(CC) $(FLAGS) $(BOT_SRCS) -o $(BOT_NAME)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(LIBS)
	make clean

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME) $(BOT_NAME)

re: fclean all

.PHONY: all fclean clean re
