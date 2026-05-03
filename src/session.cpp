#include "session.h"
#include "logger.h"

namespace calculator
{

namespace asio = boost::asio;
using tcp = asio::ip::tcp;

Session::Session(tcp::socket socket, Runner& runner)
    : m_socket(std::move(socket)), m_runner(runner)
{
}

void Session::start() { doRead(); }

void Session::doRead()
{
    auto self = shared_from_this();
    asio::async_read_until(m_socket, m_buffer, '\n',
                           [self](boost::system::error_code ec, std::size_t /*length*/) {
                               if (ec)
                               {
                                   Logger::instance().info("client disconnected");
                                   return;
                               }
                               std::istream stream(&self->m_buffer);
                               std::string line;
                               std::getline(stream, line);
                               self->m_response = self->m_runner.process(line);
                               self->doWrite();
                           });
}

void Session::doWrite()
{
    auto self = shared_from_this();
    asio::async_write(m_socket, asio::buffer(m_response),
                      [self](boost::system::error_code ec, std::size_t /*length*/) {
                          if (ec)
                          {
                              return;
                          }
                          self->doRead();
                      });
}

} // namespace calculator
