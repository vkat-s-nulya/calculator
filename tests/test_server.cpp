#include "runner.h"
#include "server.h"
#include <boost/asio.hpp>
#include <chrono>
#include <cstdlib>
#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <thread>

namespace asio = boost::asio;
using tcp = asio::ip::tcp;

namespace
{
constexpr unsigned short kTestPort = 19000;
constexpr auto kTimeout = std::chrono::seconds(5);
} // namespace

class ServerTest : public ::testing::Test
{
protected:
    static void SetUpTestSuite()
    {
        const char* env = std::getenv("CALC_DB_CONNINFO");
        const std::string conninfo = (env != nullptr) ? env : "";

        s_runner = std::make_unique<calculator::Runner>(conninfo);

        s_io = std::make_unique<asio::io_context>();
        s_server =
            std::make_unique<calculator::Server>(*s_io, kTestPort, *s_runner);
        s_server->start();

        s_thread = std::thread([]() { s_io->run(); });

        const auto deadline = std::chrono::steady_clock::now() + kTimeout;
        while (std::chrono::steady_clock::now() < deadline)
        {
            asio::io_context probe;
            tcp::socket sock(probe);
            boost::system::error_code ec;
            sock.connect(tcp::endpoint(asio::ip::make_address("127.0.0.1"), kTestPort), ec);
            if (!ec)
            {
                return;
            }
        }
        FAIL() << "server failed to start within timeout";
    }

    static void TearDownTestSuite()
    {
        if (s_io)
        {
            s_io->stop();
        }
        if (s_thread.joinable())
        {
            s_thread.join();
        }
        s_server.reset();
        s_runner.reset();
        s_io.reset();
    }

    static std::string sendRequest(const std::string& request)
    {
        asio::io_context io;
        tcp::socket sock(io);
        sock.connect(
            tcp::endpoint(asio::ip::make_address("127.0.0.1"), kTestPort));
        asio::write(sock, asio::buffer(request + "\n"));

        asio::streambuf buf;
        asio::read_until(sock, buf, '\n');
        std::istream stream(&buf);
        std::string response;
        std::getline(stream, response);
        return response;
    }

    static std::unique_ptr<asio::io_context> s_io;
    static std::unique_ptr<calculator::Runner> s_runner;
    static std::unique_ptr<calculator::Server> s_server;
    static std::thread s_thread;
};

std::unique_ptr<asio::io_context> ServerTest::s_io;
std::unique_ptr<calculator::Runner> ServerTest::s_runner;
std::unique_ptr<calculator::Server> ServerTest::s_server;
std::thread ServerTest::s_thread;

TEST_F(ServerTest, Addition)
{
    const auto resp = sendRequest(R"({"a": 12345, "b": 67, "op": "add"})");
    EXPECT_NE(resp.find("\"result\":12412"), std::string::npos) << resp;
    EXPECT_NE(resp.find("\"status\":0"), std::string::npos) << resp;
}

TEST_F(ServerTest, Subtraction)
{
    const auto resp = sendRequest(R"({"a": 100, "b": 7, "op": "sub"})");
    EXPECT_NE(resp.find("\"result\":93"), std::string::npos) << resp;
}

TEST_F(ServerTest, Multiplication)
{
    const auto resp = sendRequest(R"({"a": 11, "b": 13, "op": "mul"})");
    EXPECT_NE(resp.find("\"result\":143"), std::string::npos) << resp;
}

TEST_F(ServerTest, Division)
{
    const auto resp = sendRequest(R"({"a": 100, "b": 4, "op": "div"})");
    EXPECT_NE(resp.find("\"result\":25"), std::string::npos) << resp;
}

TEST_F(ServerTest, Power)
{
    const auto resp = sendRequest(R"({"a": 3, "b": 7, "op": "pow"})");
    EXPECT_NE(resp.find("\"result\":2187"), std::string::npos) << resp;
}

TEST_F(ServerTest, Factorial)
{
    const auto resp = sendRequest(R"({"a": 6, "op": "fac"})");
    EXPECT_NE(resp.find("\"result\":720"), std::string::npos) << resp;
}

TEST_F(ServerTest, DivisionByZeroReturnsError)
{
    const auto resp = sendRequest(R"({"a": 1, "b": 0, "op": "div"})");
    EXPECT_NE(resp.find("\"status\":1"), std::string::npos) << resp;
    EXPECT_NE(resp.find("\"error\""), std::string::npos) << resp;
}

TEST_F(ServerTest, InvalidJsonReturnsError)
{
    const auto resp = sendRequest("not a json");
    EXPECT_NE(resp.find("\"status\":1"), std::string::npos) << resp;
    EXPECT_NE(resp.find("invalid JSON"), std::string::npos) << resp;
}

TEST_F(ServerTest, UnknownOperationReturnsError)
{
    const auto resp = sendRequest(R"({"a": 1, "b": 2, "op": "xor"})");
    EXPECT_NE(resp.find("\"status\":1"), std::string::npos) << resp;
}

TEST_F(ServerTest, MultipleRequestsInSameSession)
{
    asio::io_context io;
    tcp::socket sock(io);
    sock.connect(tcp::endpoint(asio::ip::make_address("127.0.0.1"), kTestPort));

    asio::streambuf buf;

    asio::write(
        sock,
        asio::buffer(std::string(R"({"a": 1, "b": 2, "op": "add"})") + "\n"));
    asio::read_until(sock, buf, '\n');
    {
        std::istream stream(&buf);
        std::string response;
        std::getline(stream, response);
        EXPECT_NE(response.find("\"result\":3"), std::string::npos) << response;
    }

    asio::write(
        sock,
        asio::buffer(std::string(R"({"a": 8, "b": 4, "op": "sub"})") + "\n"));
    asio::read_until(sock, buf, '\n');
    {
        std::istream stream(&buf);
        std::string response;
        std::getline(stream, response);
        EXPECT_NE(response.find("\"result\":4"), std::string::npos) << response;
    }
}
