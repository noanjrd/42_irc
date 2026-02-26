# IRC Server

## Introduction

This project is a custom implementation of an IRC (Internet Relay Chat) server, developed as part of the 42 school curriculum. The server is written in C++98 and aims to provide a functional IRC environment, supporting multiple clients, channels, and the most common IRC commands. The project demonstrates network programming, socket management, and real-time communication between users.

## Table of Contents

- [Features](#features)
- [Project Structure](#project-structure)
- [Build Instructions](#build-instructions)
- [Usage](#usage)
- [Supported IRC Commands](#supported-irc-commands)
- [Bot](#bot)
- [Signals and Shutdown](#signals-and-shutdown)
- [Authors](#authors)

## Features

- **Multi-client support:** Multiple users can connect and interact simultaneously.
- **Channel management:** Users can create, join, leave, and manage channels.
- **User authentication:** Password-protected server access.
- **Operator privileges:** Channel operators can manage users and channel settings.
- **IRC commands:** Implements standard IRC commands (`JOIN`, `PART`, `NAMES`, `KICK`, `TOPIC`, `PRIVMSG`, `QUIT`, `MODE`, `INVITE`).
- **Bot:** Includes a simple IRC bot for demonstration and testing.
- **Graceful shutdown:** Handles system signals for clean server termination.
- **Compatibility:** Can be used with standard IRC clients.

## Project Structure

```
.
├── Makefile                  # Build instructions for compiling the server and bot
├── README.md                 # Project documentation (this file)
├── includes/                 # Header files for class and function declarations
│   ├── Channel.hpp           # Channel class definition (channel management)
│   ├── Client.hpp            # Client class definition (user management)
│   ├── ClientConnection.hpp  # ClientConnection class (client socket abstraction)
│   ├── IRC.hpp               # Main includes, macros, and function prototypes
│   └── Server.hpp            # Server class definition (core server logic)
├── srcs/                     # Source files for implementation
│   ├── main.cpp              # Entry point of the IRC server
│   ├── Utils.cpp             # Utility functions (helpers, parsing, etc.)
│   ├── bot/                  # IRC bot source code
│   │   └── Bot.cpp           # Simple IRC bot implementation
│   ├── channel/              # Channel-related source code
│   │   └── Channel.cpp       # Channel class implementation
│   ├── client/               # Client-related source code
│   │   ├── Client.cpp        # Client class implementation
│   │   └── ClientConnection.cpp # ClientConnection class implementation
│   ├── commands/             # Implementation of IRC commands
│   │   ├── INVITE.cpp
│   │   ├── JOIN.cpp
│   │   ├── KICK.cpp
│   │   ├── MODE.cpp
│   │   ├── NAMES.cpp
│   │   ├── PART.cpp
│   │   ├── PRIVMSG.cpp
│   │   ├── QUIT.cpp
│   │   └── TOPIC.cpp
│   └── server/               # Server core logic and event loop
│       ├── Poll.cpp          # Polling and event loop logic
│       ├── ProcessMessages.cpp # Message parsing and dispatch
│       ├── Server.cpp        # Server class implementation
│       └── Signals.cpp       # Signal handling (SIGINT, SIGTERM)
└── .github/                  # GitHub configuration files
    └── ...
```

## Build Instructions

### Prerequisites

- C++ compiler supporting C++98 (e.g., `g++`)
- `make` utility

### Compilation

To build the server and the bot, run:

```sh
make
```

This will produce two executables:
- `ircserv` — the IRC server
- `bot` — a simple IRC bot

To clean object files:

```sh
make clean
```

To remove all binaries and object files:

```sh
make fclean
```

To rebuild everything:

```sh
make re
```

## Usage

### Starting the Server

```sh
./ircserv <port> <server_password>
```

- `<port>`: The port number to listen on (must be between 1024 and 65535).
- `<server_password>`: The password required for clients to connect.

Example:

```sh
./ircserv 6667 mysecretpassword
```

### Connecting with an IRC Client

You can use any IRC client (e.g., `irssi`, `weechat`, or a custom client) to connect:

- **Server:** `localhost`
- **Port:** The port you specified (e.g., 6667)
- **Password:** The server password

### Using the Bot

To run the bot:

```sh
./bot <server_ip> <port> <password>
```

Example:

```sh
./bot 127.0.0.1 6667 mysecretpassword
```

The bot will automatically join the `#test` channel and respond to "Hi bot" messages.

## Supported IRC Commands

- `PASS <password>` — Authenticate with the server.
- `NICK <nickname>` — Set your nickname.
- `USER <username> 0 * :<realname>` — Set your username and real name.
- `JOIN <#channel> [password]` — Join or create a channel.
- `PART <#channel>[,#channel2,...] [:reason]` — Leave one or more channels.
- `NAMES <#channel>` — List users in a channel.
- `KICK <#channel> <user> [reason]` — Remove a user from a channel.
- `TOPIC <#channel> [:topic]` — View or set the channel topic.
- `PRIVMSG <user|#channel> :<message>` — Send a private message.
- `QUIT [:message]` — Disconnect from the server.
- `MODE <#channel> <modes> [parameters]` — Set or view channel modes.
- `INVITE <nickname> <#channel>` — Invite a user to a channel.

## Bot

A simple IRC bot is included for demonstration and testing. The bot connects to the server, authenticates, joins a channel, and can respond to specific messages. You can modify the bot's behavior in [srcs/bot/Bot.cpp](srcs/bot/Bot.cpp).

## Signals and Shutdown

- The server handles `SIGINT` and `SIGTERM` for graceful shutdown.
- Use `Ctrl+C` in the terminal to stop the server safely.

## Authors

This project was developed with love at 42.

- [JARD Noan](https://github.com/noanjrd)
- [AANKOUR Naziha](https://github.com/naankour)
- [HASNAOUI Iliane](https://github.com/hasnawww)