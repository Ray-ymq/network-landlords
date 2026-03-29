# Network Landlords

A complete Landlords card game system with client and server components, supporting online multiplayer mode.

## Project Overview

Network Landlords is a Landlords card game built with a Qt client and a C++ server, featuring three-player gameplay, landlord bidding, bomb animations, and more. The client is developed using the Qt framework, while the server implements a Reactor pattern for high-concurrency network communication.

## Technology Stack

### Client
- **Qt** - UI framework
- **Protobuf** - Data serialization
- **TCP** - Network communication
- **AES/RSA** - Encrypted communication

### Server
- **C++** - Server core
- **Epoll/Poll/Select** - I/O multiplexing
- **MySQL** - Data storage
- **ThreadPool** - Thread pool
- **Protobuf** - Data serialization

## Core Modules

### Client Modules (client-ddz)
| Module | Description |
|--------|-------------|
| card | Playing card class with rank and suit |
| player | Player and AI bot |
| strategy | Card-playing strategy algorithm |
| control | Game flow control |
| serialize | Protobuf encoding/decoding |
| crypto | AES/RSA/Base64 encryption |
| tcp | TCP network communication |
| windows | Qt UI interface |

### Server Modules (server-ddz)
| Module | Description |
|--------|-------------|
| reactor | Epoll/Poll/Select event dispatching |
| tcp | TCP connection management |
| game | Game room logic |
| http | HTTP file server |
| database | MySQL connection pool |
| thread | Thread pool |
| serialize | Protobuf encoding/decoding |
| crypto | Encryption utilities |

## Build Requirements

### Client
- Qt 5.x
- Protobuf
- GCC/MSVC

### Server
- GCC
- MySQL client library
- Protobuf

## Quick Start

### Build the Client

```bash
cd client-ddz
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j4
```

### Build the Server

```bash
cd server-ddz
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j4
```

### Start the Server

```bash
./server-ddz --port 8888
```

### Start the Client

Run the compiled executable and connect to the server IP to begin playing.

## Game Rules

- Three-player Landlords; two players are peasants
- Landlord bidding: 3–100 points
- Card combinations: Single, pair, triple, straight, consecutive pairs, aircraft, bomb, rocket (double jokers)
- The first player to empty their hand wins

## Directory Structure

```
network-landlords/
├── client-ddz/          # Qt Client
│   ├── card/            # Playing cards
│   ├── control/         # Game control
│   ├── player/          # Players
│   ├── strategy/        # Card-playing strategy
│   ├── windows/         # Qt UI
│   ├── serialize/       # Protobuf
│   ├── crypto/          # Encryption
│   ├── tcp/             # Network
│   └── thread/          # Threading
│
└── server-ddz/          # C++ Server
    ├── reactor/         # Event dispatching
    ├── tcp/             # Network
    ├── game/            # Game logic
    ├── http/            # HTTP
    ├── database/        # MySQL
    └── thread/          # Thread pool
```

## License

MIT License