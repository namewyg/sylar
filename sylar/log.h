#ifndef __SYLAR_LOG_H__
#define __SYLAR_LOG_H__

#include <string>
#include <stdint.h>
#include <stdio.h>
#include <memory>

namespace sylar {

/**
 * @brief 日志事件
 */
class LogEvent {
public:
    LogEvent();
private:
    const char* m_file = nullptr;
    uint32_t m_line = 0;
    uint32_t m_thread = 0;
    uint32_t m_fibraId = 0;
    uint64_t m_time;
    std::string m_content;

};

class Logger {
public:
    enum Level {
        DEBUG = 1,
        INFO = 2,
        WARN = 3,
        ERROR = 4,
        FATAL = 5
    };
    Logger();
    void log(Level level, const LogEvent& event);
private:
};

class LogAppender {
public:
    virtual ~LogAppender() {};
private:
};

class Formatter {

};

}

#endif