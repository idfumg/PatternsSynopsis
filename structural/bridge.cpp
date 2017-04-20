/*
  Паттерн Bridge разделяет абстракцию и реализацию на две
  отдельных иерархии классов так, что их можно изменять
  независимо друг от друга.
 */

#include <iostream>

using namespace std;

#define MT

class LoggerImpl {
public:
    virtual ~LoggerImpl() {}
    virtual void console_log(const string& str) = 0;
    virtual void file_log(const string& file, const string& str) = 0;
    virtual void socket_log(const string& host, int port, const string& str) = 0;
};

class ST_LoggerImpl : public LoggerImpl {
public:
    virtual void console_log(const string& str) {
        cout << "Single-threaded console logger" << endl;
    }
    virtual void file_log(const string& file, const string& str) {
        cout << "Single-threaded file logger" << endl;
    }
    virtual void socket_log(const string& host, int port, const string& str) {
        cout << "Single-threaded socket logger" << endl;
    }
};

class MT_LoggerImpl : public LoggerImpl{
public:
    virtual void console_log(const string& str) {
        cout << "Multi-threaded console logger" << endl;
    }
    virtual void file_log(const string& file, const string& str) {
        cout << "Multi-threaded file logger" << endl;
    }
    virtual void socket_log(const string& host, int port, const string& str) {
        cout << "Multi-threaded socket logger" << endl;
    }
};

class Logger {
public:
    Logger(LoggerImpl* pimpl) : pimpl(pimpl) {}

    virtual ~Logger() {
        delete this->pimpl;
    }

    virtual void log(const string& str) = 0;

protected:
    LoggerImpl* pimpl;
};

class ConsoleLogger : public Logger {
public:
    ConsoleLogger() : Logger(
#ifdef MT
        new MT_LoggerImpl()
#else
        new ST_LoggerImpl()
#endif
        ) {
    }

    void log(const string& str) {
        this->pimpl->console_log(str);
    }
};

class FileLogger : public Logger {
public:
    FileLogger(const string& file) : Logger(
#ifdef MT
        new MT_LoggerImpl()
#else
        new ST_LoggerImpl()
#endif
        ), file(file) {
    }

    void log(const string& str) {
        this->pimpl->file_log(this->file, str);
    }

private:
    string file;
};

class SocketLogger : public Logger {
public:
    SocketLogger(const string& host, int port) : Logger(
#ifdef MT
        new MT_LoggerImpl()
#else
        new ST_LoggerImpl()
#endif
        ), host(host), port(port) {
    }

    void log(const string& str) {
        this->pimpl->socket_log(this->host, this->port, str);
    }

private:
    string host;
    int port;
};

int main() {
    Logger* p = new FileLogger("log.txt");
    p->log("hello world!");
    delete p;

    return 0;
}
