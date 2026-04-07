#include "runner.h"
#include "calculator.h"
#include "parser.h"
#include "printer.h"

void calculator::run(int argc, char *argv[])
{
    Context ctx = {};
    parse(argc, argv, &ctx);
    calculate(&ctx);
    print(&ctx);
}