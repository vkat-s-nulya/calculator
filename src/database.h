#pragma once
#include "types.h"
#include <libpq-fe.h>
#include <memory>
#include <string>
#include <vector>

namespace calculator
{

struct CalculationRecord
{
    int64_t a;
    int64_t b;
    Operation operation;
    int64_t result;
    int status;
};

class PostgresDatabase
{
public:
    PostgresDatabase(const std::string& conninfo);
    ~PostgresDatabase() = default;

    PostgresDatabase(const PostgresDatabase&) = delete;
    PostgresDatabase& operator=(const PostgresDatabase&) = delete;

    void save(const CalculationRecord& record);
    std::vector<CalculationRecord> loadAll();

private:
    struct conn_deleter
    {
        void operator()(PGconn* conn) const { PQfinish(conn); }
    };

    struct result_deleter
    {
        void operator()(PGresult* result) const { PQclear(result); }
    };

    using result_ptr = std::unique_ptr<PGresult, result_deleter>;

    result_ptr execute(const std::string& query, const std::vector<std::string>& params);

    std::unique_ptr<PGconn, conn_deleter> m_conn;
};

}
