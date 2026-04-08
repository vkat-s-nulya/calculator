#include "parser.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace calculator
{
static struct option long_options[] = {
    {"a", required_argument, NULL, 'a'},
    {"b", required_argument, NULL, 'b'},
    {"operation", required_argument, NULL, 'o'},
    {"help", no_argument, NULL, 'h'},
    {NULL, 0, NULL, 0},
};

static void parse_arg(char *optarg, int64_t *destination)
{
    *destination = strtoll(optarg, NULL, 10);
}

static void parse_operation(char *optarg, Operation *destination)
{
    if (strcmp(optarg, "add") == 0)
    {
        *destination = Operation::ADD;
        return;
    }
    if (strcmp(optarg, "sub") == 0)
    {
        *destination = Operation::SUB;
        return;
    }
    if (strcmp(optarg, "mul") == 0)
    {
        *destination = Operation::MUL;
        return;
    }
    if (strcmp(optarg, "div") == 0)
    {
        *destination = Operation::DIV;
        return;
    }
    if (strcmp(optarg, "pow") == 0)
    {
        *destination = Operation::POW;
        return;
    }
    if (strcmp(optarg, "fac") == 0)
    {
        *destination = Operation::FAC;
        return;
    }

    *destination = Operation::UNKNOWN;
}

void parse(int argc, char *argv[], Context *ctx)
{
    int opt;
    while ((opt = getopt_long(argc, argv, "a:b:o:h", long_options, NULL)) != -1)
    {
        switch (opt)
        {
        case 'a':
            parse_arg(optarg, &ctx->a);
            ctx->has_a = 1;
            break;
        case 'b':
            parse_arg(optarg, &ctx->b);
            ctx->has_b = 1;
            break;
        case 'o':
            parse_operation(optarg, &ctx->operation);
            ctx->has_op = 1;
            break;
        case 'h':
            printf("Usage: calculator -a NUM -b NUM -o OPERATION\n");
            printf("Operations: add, sub, mul, div, pow, fac\n");
            exit(0);
        case '?':
            printf("Error: invalid option\n");
            exit(1);
        default:
            break;
        }
    }
}
} // namespace calculator