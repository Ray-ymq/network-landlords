//
// Created by Ray on 2026/3/29.
//

#ifndef SERVER_DDZ_DISPATCHER_H
#define SERVER_DDZ_DISPATCHER_H

#pragma once
#include "Channel.h"
#include "EventLoop.h"
#include <string>

class EventLoop;
class Dispatcher
{
public:
    Dispatcher(EventLoop* evloop);
    virtual ~Dispatcher();
    // 添加
    virtual int add();
    // 删除
    virtual int remove();
    // 修改
    virtual int modify();
    // 事件监测
    virtual int dispatch(int timeout = 2); // 单位: s
    inline void setChannel(Channel* channel)
    {
        m_channel = channel;
    }
protected:
    std::string m_name = std::string();
    Channel* m_channel;
    EventLoop* m_evLoop;
};

#endif //SERVER_DDZ_DISPATCHER_H