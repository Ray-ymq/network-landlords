//
// Created by Ray on 2026/3/29.
//

#ifndef SERVER_DDZ_POLLDISPATCHER_H
#define SERVER_DDZ_POLLDISPATCHER_H

#pragma once
#include "Channel.h"
#include "EventLoop.h"
#include "Dispatcher.h"
#include <string>
#include <poll.h>

class PollDispatcher : public Dispatcher
{
public:
    PollDispatcher(EventLoop* evloop);
    ~PollDispatcher();
    // 添加
    int add() override;
    // 删除
    int remove() override;
    // 修改
    int modify() override;
    // 事件监测
    int dispatch(int timeout = 2) override; // 单位: s

private:
    int m_maxfd;
    struct pollfd* m_fds;
    const int m_maxNode = 1024;
};

#endif //SERVER_DDZ_POLLDISPATCHER_H
