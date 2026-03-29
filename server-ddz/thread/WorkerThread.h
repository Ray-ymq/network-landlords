//
// Created by Ray on 2026/3/29.
//

#ifndef SERVER_DDZ_WORKERTHREAD_H
#define SERVER_DDZ_WORKERTHREAD_H

#pragma once

#include <condition_variable>
#include <mutex>
#include <string>
#include <thread>

#include "EventLoop.h"

// 定义子线程对应的结构体
class WorkerThread
{
public:
    explicit WorkerThread(int index);
    ~WorkerThread();
    // 启动线程
    void run();
    inline EventLoop* getEventLoop()
    {
        return m_evLoop;
    }

private:
    void running();

private:
    std::thread* m_thread;   // 保存线程的实例
    std::thread::id m_threadID; // ID
    std::string m_name;
    std::mutex m_mutex;  // 互斥锁
    std::condition_variable m_cond;    // 条件变量
    EventLoop* m_evLoop;   // 反应堆模型
};

#endif // SERVER_DDZ_WORKERTHREAD_H
