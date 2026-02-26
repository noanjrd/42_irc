_This project has been created as part of the 42 curriculum by **njard**, **naankour**, **ilhasnao**._

## Description

**ft_irc** is a fully functional Internet Relay Chat (IRC) server implementation written in C++98. The project aims to provide a deep understanding of network programming, socket handling, and the IRC protocol.

The server supports multiple simultaneous client connections using `poll()` for I/O multiplexing, and implements core IRC functionalities including channel management, private messaging, user authentication, and various channel modes. The implementation follows the IRC RFC specifications to ensure compatibility with standard IRC clients.

### Key Features

- Multi-client support with non-blocking I/O
- User authentication with password protection
- Channel creation and management
- Channel modes: invite-only (+i), topic protection (+t), password (+k), user limit (+l), operator privileges (+o)
- Private messaging between users
- Channel operator commands (KICK, INVITE, TOPIC, MODE)
- Signal handling for graceful shutdown
- Bonus: Simple responding bot

## Instructions

### Compilation

To compile the IRC server:
```bash
make
```

This will generate two executables:
- ircserv: The IRC server
- bot: A bot that responds to a simple message after joining a channel #test

To clean object files:
```bash
make clean
```

To remove all compiled files:
```bash
make fclean
```

To recompile everything:
```bash
make re
```

### Execution

**Starting the server:**
```bash
./ircserv <port> <password>
```
- `<port>`: The port number on which the server will listen (must be between 1024 and 65535)
- `<password>`: The connection password required for clients to connect

Example:
```bash
./ircserv 6667 mypassword
```

**Starting the bot:**
```bash
./bot <server_ip> <port> <password>
```

Example:
```bash
./bot 127.0.0.1 6667 mypassword
```

**Connecting with an IRC client:**

You can connect to the server using any standard IRC client (e.g., irssi, WeeChat, HexChat, or nc for testing):

```bash
nc localhost 6667
```

Then authenticate:
```
PASS mypassword
NICK mynickname
USER myusername 0 * :My Real Name
```

**Stopping the server:**

Press `Ctrl+C` to gracefully shut down the server.

### Supported Commands

- `PASS <password>` - Authenticate with the server
- `NICK <nickname>` - Set your nickname
- `USER <username> 0 * :<realname>` - Register your user information
- `JOIN <#channel> [password]` - Join or create a channel
- `PART <#channel> [message]` - Leave a channel
- `PRIVMSG <target> <message>` - Send a private message to a user or channel
- `KICK <#channel> <user> [reason]` - Kick a user from a channel (operators only)
- `INVITE <nickname> <#channel>` - Invite a user to a channel (operators only)
- `TOPIC <#channel> [topic]` - View or set the channel topic
- `MODE <#channel> <mode> [parameters]` - Change channel modes (operators only)
- `NAMES <#channel>` - List all users in a channel
- `QUIT [message]` - Disconnect from the server

### Channel Modes

- `+i`/`-i` : Set/remove invite-only channel
- `+t`/`-t`: Set/remove restrictions on TOPIC command
- `+k <password>`/ `-k <password>` : Set/remove channel password
- `+o <nickname>`/`-o <nickname>` : Give/take channel operator privileges
- `+l <limit>`/`-l <limit>` : Set/remove user limit to channel

## Resources

### Documentation & Specifications
- [IRC Protocol - Wikipedia](https://en.wikipedia.org/wiki/IRC)
- [List of IRC Commands - Wikipedia](https://en.wikipedia.org/wiki/List_of_IRC_commands)
- [RFC 1459 - Internet Relay Chat Protocol](https://datatracker.ietf.org/doc/html/rfc1459)
- [RFC 2812 - IRC Client Protocol](https://datatracker.ietf.org/doc/html/rfc2812)

### AI Usage

AI assistance (ChatGPT/Claude) was used for the following tasks:
- **Error message formatting**: Generating RFC-compliant error response syntax and numeric reply codes
- **Code review**: Identifying potential memory leaks and suggesting improvements for error handling
- **Understanding**: Assistance with understanding socket programming edge cases and signal handling

All core logic, architecture decisions, and implementations were designed and written by the project authors.

---

**Project Structure:**
```
.
├── includes/           # Header files
│   ├── Channel.hpp
│   ├── Client.hpp
│   ├── ClientConnexion.hpp
│   ├── IRC.hpp
│   └── Server.hpp
├── srcs/              # Source files
│   ├── bot/          # Bot implementation
│   ├── channel/       # Channel management
│   ├── client/       # Client management
│   ├── commands/     # IRC command implementations
│   ├── server/       # Server core functionality
│   └── main.cpp
├── Makefile
└── README.md
```