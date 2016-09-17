
#include <iostream>

#include <libcouchbase/couchbase++.h>
#include <libcouchbase/couchbase++/views.h>
#include <libcouchbase/couchbase++/query.h>
#include <libcouchbase/couchbase++/endure.h>
#include <libcouchbase/couchbase++/logging.h>

#include "database.hpp"
#include "configuration.hpp"

namespace nextflow {
namespace users {

DatabaseClient::DatabaseClient()
{
    auto databaseUrl = Configuration::instance().get<std::string>("Database.url");
    auto databasePassword = Configuration::instance().get<std::string>("Database.password");
    
    client = std::make_shared<Couchbase::Client>(databaseUrl, databasePassword);
    Couchbase::Status status = client->connect();
    if (!status.success()) {
        std::cout << "Couldn't connect to '"<< databaseUrl
             << "'. "<< "Reason: "<< status
             << std::endl;
        exit(EXIT_FAILURE); // todo: throw exception
    }
}

bool DatabaseClient::insert(const std::string& key, const json& body)
{
    auto result = client->upsert(key, body.dump());
    return result.status().success();
}

bool DatabaseClient::query(const std::string& command, json& array)
{
    Couchbase::QueryCommand qcmd(command);

    Couchbase::Status status;
    Couchbase::Query q(*client, qcmd, status);
    if (!status) {
        return false;
    }

    for (auto row : q) {
        array.push_back(json::parse(std::string(row.json())));
    }

    if (!q.status()) {
        return false;
    }

    return true;
}

}}