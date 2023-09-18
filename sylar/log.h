#ifndef __SYLAR_LOG_H__
#define __SYLAR_LOG_H__

#include <string>
#include <stdint.h>
#include <stdio.h>
#include <memory>
#include <list>
#include <stringstream>
#include <fsteam>

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

// 日志级别
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

// 日志格式器
class LogFormatter {
public:
    typedef std::shared_ptr<LogFormatter> ptr;
    LogFormatter(const std::string& pattern);
    std::string format(LogEvent::ptr event);
private:
    class FormatItem {
        public:
            typedef std::shared_ptr<LogFormatter> ptr;
            virtual ~FormatItem() {}
            virtual std::string format(LogEvent::ptr event) = 0;
    };

    void init();
private:
    std::string m_pattern;
    std::vector<FormatItem> m_items;

};

// 日志输出器   抽象基类
class LogAppender {
public:
    typedef std::shared_ptr<LogAppender> ptr;

    virtual ~LogAppender() {};

    virtual void log(LogLevel::Level level, LogEvent::ptr event) = 0; // 纯虚函数
    void setFormatter(LogFormatter::ptr val) { m_formatter = val;};
    LogFormatter::ptr getFormatter() const { return m_formatter; };
protected:
    LogLevel::Level m_level;
    LogFormatter::ptr m_formatter;
};


// 日志器
class Logger {
public:
    typedef std::shared_ptr<Logger> ptr;

    Logger(const std::string& name = "root");
    void log(LogLevel::Level level, LogEvent::ptr event);

    void debug(LogEvent::ptr event);
    void info(LogEvent::ptr event);
    void warn(LogEvent::ptr event);
    void error(LogEvent::ptr event);
    void fatal(LogEvent::ptr event);

    void addAppender(LogAppender::ptr appender);
    void delAppender(LogAppender::ptr appender);
    LogLevel::Level getLevel() const { return m_level; }
    void setLevel(LogLevel::Level val) { m_level = val; }

private:
    std::string m_name;
    LogLevel::Level m_level;
    std::list<LogAppender::ptr> m_appenders;

};

// ----------------------------------------------------------------
// Appender的具体声明
// ----------------------------------------------------------------

/**
 * @brief 1.输出到控制台的Appender
 */
class StdoutLogAppender : public LogAppender {
public:
    typedef std::shared_ptr<StdoutLogAppender> ptr;
    void log(LogLevel::Level level, LogEvent::ptr event) override;
private:

};
// 2.输出到文件
class FileLogAppender : public LogAppender {
public:
    typedef std::shared_ptr<FileLogAppender> ptr;
    FileLogAppender(const std::string& filename); // 写入文件需要文件名
    void log(LogLevel::Level level, LogEvent::ptr event) override;
    // 返回重新打开文件，文件打开成功返回true
    bool reopen();
private:
    std::string m_filename;
    std::ofstream m_filestream;
};

}

#endif