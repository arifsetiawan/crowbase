
#include <libcouchbase/couchbase++.h>
#include <libcouchbase/couchbase++/views.h>
#include <libcouchbase/couchbase++/query.h>
#include <libcouchbase/couchbase++/endure.h>
#include <libcouchbase/couchbase++/logging.h>
#include <json.hpp>

#include "database.hpp"
#include "configuration.hpp"

using json = nlohmann::json;
using namespace std;
using namespace Couchbase;

namespace nextflow {
namespace users {

DatabaseClient::DatabaseClient()
{
    auto databaseUrl = Configuration::instance().get<std::string>("Database.url");
    auto databaseSecret = Configuration::instance().get<std::string>("Database.secret");
    
    client = std::make_shared<Couchbase::Client>(databaseUrl, databaseSecret);
    Couchbase::Status status = client->connect();
    if (!status.success()) {
        cout << "Couldn't connect to '"<< databaseUrl
             << "'. "<< "Reason: "<< status
             << endl;
        exit(EXIT_FAILURE); // todo: throw exception
    }
}

}}