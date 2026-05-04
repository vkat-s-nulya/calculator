#include "server.h"
#include "logger.h"
#include "session.h"
#include <memory>

namespace calculator
{

namespace asio = boost::asio;
using tcp = asio::ip::tcp;

Server::Server(asio::io_context& io, unsigned short port, Runner& runner)
    : m_acceptor(io, tcp::endpoint(tcp::v4(), port)), m_runner(runner)
{
    Logger::instance().info(
        ("server listening on port " + std::to_string(port)).c_str());
}

void Server::start() { doAccept(); }

void Server::doAccept()
{
    m_acceptor.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket)
        {
            if (!ec)
            {
                Logger::instance().info("client connected");
                std::make_shared<Session>(std::move(socket), m_runner)->start();
            }
            if (m_acceptor.is_open())
            {
                doAccept();
            }
        });
}

} // namespace calculator
