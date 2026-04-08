#include "runner.h"
#include "calculator.h"
#include "checker.h"
#include "parser.h"
#include "printer.h"

void calculator::run(int argc, char *argv[])
{
    Context ctx = {};
    parse(argc, argv, &ctx);
    check(&ctx);
    if (ctx.error != mathlib::OK)
    {
        print(&ctx);
        return;
    }
    calculate(&ctx);
    print(&ctx);
}