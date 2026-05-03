#pragma once
#include "runner.h"
#include <boost/asio.hpp>

namespace calculator
{

class Server
{
public:
    Server(boost::asio::io_context& io, unsigned short port, Runner& runner);
    ~Server() = default;

    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;
    Server(Server&&) = delete;
    Server& operator=(Server&&) = delete;

    void start();

private:
    void doAccept();

    boost::asio::ip::tcp::acceptor m_acceptor;
    Runner& m_runner;
};

} // namespace calculator
