#pragma once

#include <vector>
#include <string>

#include <json.hpp>
using json = nlohmann::json;

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

    bool insert(const std::string& key, const json& body);
    bool query(const std::string& command, json& array);

private:
    std::shared_ptr<Couchbase::Client> client;
};

}}
