#include "logger.h"
#include "runner.h"
#include "server.h"
#include <boost/asio.hpp>
#include <csignal>
#include <cstdlib>
#include <iostream>
#include <string>
#include <thread>

int main()
{
    try
    {
        sigset_t sigset;
        sigemptyset(&sigset);
        sigaddset(&sigset, SIGINT);
        sigaddset(&sigset, SIGTERM);
        pthread_sigmask(SIG_BLOCK, &sigset, nullptr);

        const char* connEnv = std::getenv("CALC_DB_CONNINFO");
        const std::string conninfo = (connEnv != nullptr) ? connEnv : "";

        const char* portEnv = std::getenv("CALC_PORT");
        const unsigned short port =
            (portEnv != nullptr) ? static_cast<unsigned short>(std::stoi(portEnv)) : 9000;

        calculator::Runner runner(conninfo);

        boost::asio::io_context io;
        calculator::Server server(io, port, runner);
        server.start();

        std::thread worker([&io]() { io.run(); });

        int signum = 0;
        sigwait(&sigset, &signum);
        calculator::Logger::instance().info(
            ("received signal " + std::to_string(signum) + ", shutting down").c_str());

        io.stop();
        worker.join();

        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Fatal: " << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "Fatal: unknown error" << std::endl;
        return 1;
    }
}
