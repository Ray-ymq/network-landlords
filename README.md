

根据代码地图分析，这是一个完整的**斗地主 game** 项目，包含客户端（Qt开发）和服务器端。让我生成README文档：

# 网络斗地主 (Network Landlords)

一个完整的斗地主游戏系统，包含客户端和服务器端，支持网络对战模式。

## 项目简介

网络斗地主是一个基于Qt客户端和C++服务器端的斗地主卡牌游戏，支持三人对战、地主叫牌、炸弹动画等功能。客户端采用Qt框架开发，服务器端采用 Reactor 模式实现高并发网络通信。

## 技术栈

### 客户端
- **Qt** - UI框架
- **Protobuf** - 数据序列化
- **TCP** - 网络通信
- **AES/RSA** - 加密通信

### 服务器端
- **C++** - 服务器核心
- **Epoll/Poll/Select** - 多路复用
- **MySQL** - 数据存储
- **ThreadPool** - 线程池
- **Protobuf** - 数据序列化

## 核心模块

### 客户端模块 (client-ddz)
| 模块 | 说明 |
|------|------|
| card | 扑克牌类，牌面点数/花色 |
| player | 玩家、机器人AI |
| strategy | 出牌策略算法 |
| control | 游戏流程控制 |
| serialize | Protobuf 编解码 |
| crypto | AES/RSA/Base64 加密 |
| tcp | TCP 网络通信 |
| windows | Qt UI界面 |

### 服务器端模块 (server-ddz)
| 模块 | 说明 |
|------|------|
| reactor | Epoll/Poll/Select 事件分发 |
| tcp | TCP 连接管理 |
| game | 游戏房间逻辑 |
| http | HTTP 文件服务 |
| database | MySQL 连接池 |
| thread | 线程池 |
| serialize | Protobuf 编解码 |
| crypto | 加密工具 |

## 构建要求

### 客户端
- Qt 5.x
- Protobuf
- GCC/MSVC

### 服务器端
- GCC
- MySQL客户端库
- Protobuf

## 快速开始

### 构建客户端

```bash
cd client-ddz
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j4
```

### 构建服务器端

```bash
cd server-ddz
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j4
```

### 启动服务器

```bash
./server-ddz --port 8888
```

### 启动客户端

运行编译后的可执行文件，连接服务器IP进行游戏。

## 游戏规则

- 三人斗地主，对家为农民
- 叫地主机制：3-100分
- 牌型：单张、对子、三张、顺子、连对、飞机、炸弹、王炸
- 先出完手中牌者获胜

## 目录结构

```
network-landlords/
├── client-ddz/          # Qt客户端
│   ├── card/            # 扑克牌
│   ├── control/         # 游戏控制
│   ├── player/          # 玩家
│   ├── strategy/        # 出牌策略
│   ├── windows/         # Qt界面
│   ├── serialize/       # Protobuf
│   ├── crypto/          # 加密
│   ├── tcp/             # 网络
│   └── thread/           # 线程
│
└── server-ddz/          # C++服务器
    ├── reactor/         # 事件分发
    ├── tcp/              # 网络
    ├── game/             # 游戏逻辑
    ├── http/             # HTTP
    ├── database/         # MySQL
    └── thread/           # 线程池
```

## 许可证

MIT License