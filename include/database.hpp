#pragma once
#include <vector>
#include <string>

namespace Couchbase
{
    class Client;
}

namespace nextflow {
namespace users {

/**
 * \brief Couchbase client
 */
class DatabaseClient
{
public:
    DatabaseClient();

private:
    std::shared_ptr<Couchbase::Client> client;
};

}}
