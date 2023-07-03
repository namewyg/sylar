#ifndef __SYLAR_LOG_H__
#define __SYLAR_LOG_H__

#include <string>
#include <stdint.h>
#include <stdio.h>
#include <memory>
#include <list>

namespace sylar {

/**
 * @brief 日志事件
 */
class LogEvent {
public:
    typedef std::shared_ptr<LogEvent> ptr;
    LogEvent();
private:
    const char* m_file = nullptr;
    uint32_t m_line = 0;
    uint32_t m_elapse = 0;
    uint32_t m_thread = 0;
    uint32_t m_fibraId = 0;
    uint64_t m_time;
    std::string m_content;

};

class LogLevel {
public:
    enum Level {
        DEBUG = 1,
        INFO = 2,
        WARN = 3,
        ERROR = 4,
        FATAL = 5
    };
};

class Logger {
public:
    Logger(const std::string& name = "root");
    void log(LogLevel::Level level, LogEvent::ptr event);

    void debug(LogEvent::ptr event);
    void info(LogEvent::ptr event);
    void warn(LogEvent::ptr event);
    void error(LogEvent::ptr event);
    void fatal(LogEvent::ptr event);

    void addAppender(LogAppender::ptr appender);
    void delAppender(LogAppender::ptr appender);

private:
    std::string m_name;
    LogLevel::Level m_level;
    std::list<LogAppender::ptr> m_appenders;

};
/**
 * @brief 输出到控制台的Appender
 */
class StdoutLogAppender : public LogAppender {
public:
    typedef std::shared_ptr<StdoutLogAppender> ptr;
    void log(Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override;
    std::string toYamlString() override;
};

class LogAppender {
public:
    typedef std::shared_ptr<LogAppender> ptr;

    virtual ~LogAppender() {};

    virtual void log(std::shared_ptr<Logger> Logger, LogLevel::Level level, LogEvent::ptr event) = 0;
private:
};

class Formatter {

};

}

#endif