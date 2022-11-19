#pragma once

#include <string>
#include <exception>

class IOException : public std::exception
{
private:
    std::string msg;

public:
    IOException(const std::string &message = "") : msg(message)
    {
    }

    const char * what() const noexcept
    {
        return msg.c_str();
    }
};

class InterruptedException : public std::exception
{
private:
    std::string msg;

public:
    InterruptedException(const std::string &message = "") : msg(message)
    {
    }

    const char * what() const noexcept
    {
        return msg.c_str();
    }
};

class MalformedURLException : public std::exception
{
private:
    std::string msg;

public:
    MalformedURLException(const std::string &message = "") : msg(message)
    {
    }

    const char * what() const noexcept
    {
        return msg.c_str();
    }
};

class ProtocolException : public std::exception
{
private:
    std::string msg;

public:
    ProtocolException(const std::string &message = "") : msg(message)
    {
    }

    const char * what() const noexcept
    {
        return msg.c_str();
    }
};

class FileNotFoundException : public std::exception
{
private:
    std::string msg;

public:
    FileNotFoundException(const std::string &message = "") : msg(message)
    {
    }

    const char * what() const noexcept
    {
        return msg.c_str();
    }
};

class Error : public std::exception
{
private:
    std::string msg;

public:
    Error(const std::string &message = "") : msg(message)
    {
    }

    const char * what() const noexcept
    {
        return msg.c_str();
    }
};

class IllegalStateException : public std::exception
{
private:
    std::string msg;

public:
    IllegalStateException(const std::string &message = "") : msg(message)
    {
    }

    const char * what() const noexcept
    {
        return msg.c_str();
    }
};

class InternalError : public std::exception
{
private:
    std::string msg;

public:
    InternalError(const std::string &message = "") : msg(message)
    {
    }

    const char * what() const noexcept
    {
        return msg.c_str();
    }
};
