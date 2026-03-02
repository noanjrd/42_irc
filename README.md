# ft_IRC — Internet Relay Chat Server

A custom IRC server written in **C++98**, following the IRC protocol (RFC 1459), built as part of the 42 school curriculum.  
Through this project, we learned how to work with **sockets** and network programming, while building a server that supports multiple simultaneous clients using **non-blocking I/O** with `poll()`, handles authentication, channel management, and IRC commands.

## Features

- Non-blocking I/O using `poll()`
- Multiple simultaneous clients
- Password-protected server authentication
- Full nickname/username registration
- Channel creation and management
- Operator privileges
- Channel modes: `i`, `t`, `k`, `l`, `o`
- Graceful shutdown on `SIGINT` / `SIGTERM`
- A basic IRC bot

## Requirements

- `c++` compiler (C++98 compatible)
- Linux
- Compatible IRC client (e.g., [HexChat](https://hexchat.github.io/))

## Installation

```bash
git clone <https://github.com/noanjrd/42_IRC>
cd 42_IRC
make
```

This will compile both the server (`ircserv`) and the bot (`bot`).

## Usage

### Start the server

```bash
./ircserv <port> <password>
```

| Argument   | Description                          |
|------------|--------------------------------------|
| `port`     | Port number (1024–65535)             |
| `password` | Password required to connect         |

**Example:**
```bash
./ircserv 6667 mypassword
```

### Connect with an IRC client

Using **nc** (for testing):
```bash
nc localhost 6667
```

### Stop the server

Press `Ctrl+C` — the server will shut down gracefully.

---

## Commands

> All commands follow the standard IRC protocol format.

### Connection

| Command | Syntax | Description |
|---------|--------|-------------|
| `PASS`  | `PASS <password>` | Authenticate with the server |
| `NICK`  | `NICK <nickname>` | Set your nickname |
| `USER`  | `USER <username> 0 * :<realname>` | Set your username |
| `QUIT`  | `QUIT [:<message>]` | Disconnect from the server |

### Channel

| Command   | Syntax | Description |
|-----------|--------|-------------|
| `JOIN`    | `JOIN <#channel> [password]` | Join or create a channel |
| `PART`    | `PART <#channel>[,#channel2] [:<reason>]` | Leave a channel |
| `NAMES`   | `NAMES <#channel>` | List users in a channel |
| `TOPIC`   | `TOPIC <#channel> [:<topic>]` | Get or set the channel topic |
| `KICK`    | `KICK <#channel> <user> [:<reason>]` | Remove a user from a channel |
| `INVITE`  | `INVITE <nickname> <#channel>` | Invite a user to a channel |
| `PRIVMSG` | `PRIVMSG <#channel\|nickname> :<message>` | Send a message to a channel or user |
| `MODE`    | `MODE <#channel> <+/-mode> [param]` | Set or unset channel modes |

### Channel Modes

| Mode | Description |
|------|-------------|
| `+i` / `-i` | Toggle invite-only mode |
| `+t` / `-t` | Toggle operator-only topic changes |
| `+k <password>` / `-k` | Set or remove a channel password |
| `+l <limit>` / `-l` | Set or remove a user limit |
| `+o <nick>` / `-o <nick>` | Grant or revoke operator status |

## Bot

A simple IRC bot is included and connects to the server automatically.

### Start the bot

```bash
./bot <server_ip> <port> <password>
```

**Example:**
```bash
./bot 127.0.0.1 6667 mypassword
```

### Bot behavior

- Connects and authenticates to the server
- Automatically joins `#test`
- Responds to `Hi bot` in `#test` with `Hi human`

## Architecture

```
Client connects
      │
      ▼
  poll() loop
      │
      ├── POLLIN  → recv() → splitMessage() → processMessage()
      │                                             │
      │                                    ┌────────┴────────┐
      │                                    │                 │
      │                              Authentication     Commands
      │                              (PASS/NICK/USER)  (JOIN/PART/...)
      │
      └── POLLOUT → send() pending messages from the output buffer to client
```

- **Non-blocking I/O**: All sockets are managed via `poll()`, no threads are used.
- **Message buffering**: Each client has an outgoing message buffer (`bufferToReceive`). Messages are sent when `POLLOUT` is ready.
- **Channel management**: Channels are dynamically created on first `JOIN` and destroyed when empty.
- **Operator management**: The first user to join a channel becomes its operator. If the operator leaves, the next user is promoted automatically.

## Project Structure

```
ft_irc/
├── includes/
│   ├── IRC.hpp              # Global includes, constants, function declarations
│   ├── Server.hpp           # Server class
│   ├── Client.hpp           # Client class
│   ├── ClientConnection.hpp # Client + pollfd wrapper
│   └── Channel.hpp          # Channel class
├── srcs/
│   ├── main.cpp             # Entry point, socket setup
│   ├── Utils.cpp            # Utility functions
│   ├── server/
│   │   ├── Server.cpp       # Server methods
│   │   ├── Poll.cpp         # poll() event loop
│   │   ├── ProcessMessages.cpp # Message parsing & routing
│   │   └── Signals.cpp      # Signal handling
│   ├── client/
│   │   ├── Client.cpp       # Client methods (auth, config, buffers)
│   │   └── ClientConnection.cpp
│   ├── channel/
│   │   └── Channel.cpp      # Channel logic
│   ├── commands/
│   │   ├── JOIN.cpp
│   │   ├── PART.cpp
│   │   ├── QUIT.cpp
│   │   ├── KICK.cpp
│   │   ├── INVITE.cpp
│   │   ├── TOPIC.cpp
│   │   ├── PRIVMSG.cpp
│   │   ├── MODE.cpp
│   │   └── NAMES.cpp
│   └── bot/
│       └── Bot.cpp          # IRC bot
└── Makefile
```

## Authors

- [**JARD Noan**](https://github.com/noanjrd)
- [**AANKOUR Naziha**](https://github.com/naankour)
- [**HASNAOUI Iliane**](https://github.com/hasnawww)