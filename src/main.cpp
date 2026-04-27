#include "runner.h"
#include <cstdlib>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    try
    {
        const char* env = std::getenv("CALC_DB_CONNINFO");
        const std::string conninfo = (env != nullptr) ? env : "";

        calculator::Runner runner(conninfo);
        return runner.run(argc, argv);
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
