//
// Created by Ray on 2026/3/29.
//

#ifndef SERVER_DDZ_MYSQLCONN_H
#define SERVER_DDZ_MYSQLCONN_H

#include <chrono>
#include <mysql/mysql.h>
#include <string>

class MySqlConn
{
public:
    // 初始化数据库连接
    MySqlConn();
    // 释放数据库连接资源
    ~MySqlConn();
    // 连接数据库
    bool connect(std::string user, std::string dbname,
    std::string password, std::string ip, unsigned short port = 3306);
    // 更新操作 insert、delete、update
    bool update(std::string sql);
    // 查询操作 select
    bool query(std::string sql);
    // 向下遍历结果集中的一条记录
    bool next();
    // 得到指定索引对应的字段值
    std::string value(int index);

    // 刷新一下连接的起始的空闲时间点
    void refreshAliveTime();
    // 返回存活的时间
    long long getAliveTime()const;
    // 事务 transaction
    void transaction();
    // 提交事务
    void commit();
    // 事务回滚
    void rollback();

private:
    void freeResult();

private:
    MYSQL* m_conn = NULL;
    MYSQL_ROW m_row = NULL;
    MYSQL_RES* m_result = NULL;
    std::chrono::steady_clock::time_point m_alivetime;
};

#endif // SERVER_DDZ_MYSQLCONN_H
