#pragma once
#include "runner.h"
#include <boost/asio.hpp>
#include <memory>

namespace calculator
{

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(boost::asio::ip::tcp::socket socket, Runner& runner);
    ~Session() = default;

    Session(const Session&) = delete;
    Session& operator=(const Session&) = delete;
    Session(Session&&) = delete;
    Session& operator=(Session&&) = delete;

    void start();

private:
    void doRead();
    void doWrite();

    boost::asio::ip::tcp::socket m_socket;
    Runner& m_runner;
    boost::asio::streambuf m_buffer;
    std::string m_response;
};

} // namespace calculator
