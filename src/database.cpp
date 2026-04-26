#include "database.h"
#include "exceptions.h"
#include "logger.h"

namespace calculator
{

PostgresDatabase::PostgresDatabase(const std::string& conninfo)
    : m_conn(PQconnectdb(conninfo.c_str()))
{
    if (PQstatus(m_conn.get()) != CONNECTION_OK)
    {
        throw DatabaseError(std::string("failed to connect: ") + PQerrorMessage(m_conn.get()));
    }
    Logger::instance().info("connected to database");
}

PostgresDatabase::result_ptr PostgresDatabase::execute(const std::string& query, const std::vector<std::string>& params)
{
    std::vector<const char*> values;
    values.reserve(params.size());
    for (const auto& p : params)
    {
        values.push_back(p.c_str());
    }

    result_ptr result(PQexecParams(
        m_conn.get(),
        query.c_str(),
        static_cast<int>(params.size()),
        nullptr,
        values.data(),
        nullptr,
        nullptr,
        0));

    if (!result)
    {
        throw DatabaseError(std::string("query failed: ") + PQerrorMessage(m_conn.get()));
    }

    ExecStatusType status = PQresultStatus(result.get());
    if (status != PGRES_COMMAND_OK && status != PGRES_TUPLES_OK)
    {
        throw DatabaseError(std::string("query error: ") + PQresultErrorMessage(result.get()));
    }

    return result;
}

void PostgresDatabase::save(const CalculationRecord& record)
{
    const std::string query =
        "INSERT INTO calculations (a, b, operation, result, status) "
        "VALUES ($1, $2, $3, $4, $5)";

    std::vector<std::string> params = {
        std::to_string(record.a),
        std::to_string(record.b),
        std::to_string(static_cast<int>(record.operation)),
        std::to_string(record.result),
        std::to_string(record.status),
    };

    execute(query, params);
    Logger::instance().debug("saved record to database");
}

std::vector<CalculationRecord> PostgresDatabase::loadAll()
{
    const std::string query = "SELECT a, b, operation, result, status FROM calculations";
    result_ptr result = execute(query, {});

    int rows = PQntuples(result.get());
    std::vector<CalculationRecord> records;
    records.reserve(rows);

    for (int i = 0; i < rows; ++i)
    {
        CalculationRecord record;
        record.a = std::stoll(PQgetvalue(result.get(), i, 0));
        record.b = std::stoll(PQgetvalue(result.get(), i, 1));
        record.operation = static_cast<Operation>(std::stoi(PQgetvalue(result.get(), i, 2)));
        record.result = std::stoll(PQgetvalue(result.get(), i, 3));
        record.status = std::stoi(PQgetvalue(result.get(), i, 4));
        records.push_back(record);
    }

    Logger::instance().debug(("loaded " + std::to_string(rows) + " records from database").c_str());
    return records;
}

}
