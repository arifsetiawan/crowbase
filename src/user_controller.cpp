
#include <json.hpp>
#include <string>

#include "user_controller.hpp"

using json = nlohmann::json;

namespace nextflow {
namespace users {

UserController::UserController(const std::shared_ptr<DatabaseClient>& database) :
    database(database)
{
}

void UserController::createUser(const crow::request& req, crow::response& res)
{
    auto body = json::parse(req.body);

    // TODO:: check if email valid 

    json user = json::object();
    user["_entity"] = "user";
    user["name"] = body["name"];
    user["email"] = body["email"];
    user["position_id"] = body["position_id"];
    user["position"] = body["position"];

    std::string email = user["email"];
    auto ok = database->insert("user:" + email, user);
    if (!ok) {
        res.code = 500;
        res.end();
        return;
    }

    json responseBody  = json::object();
    responseBody["data"] = user;
    res.set_header("Content-Type", "application/json");
    res.body = responseBody.dump();
    res.code = 201;
    res.end();
}

void UserController::getUsers(const crow::request& req, crow::response& res)
{
    std::string offset = "0";
    std::string limit = "10";

    if(req.url_params.get("page[offset]") != nullptr) {
        offset = std::string(req.url_params.get("page[offset]"));
    }
    if(req.url_params.get("page[limit]") != nullptr) {
        limit = std::string(req.url_params.get("page[limit]"));
    }

    // TODO :: Ensure we have index
    
    json users = json::array();
    std::string command = "SELECT u.email, u.name, u.position_id, u.position FROM gobase u WHERE _entity='user' LIMIT " + limit + " OFFSET " + offset;

    auto ok = database->query(command, users);
    if (!ok) {
        res.code = 500;
        res.end();
        return;
    }

    json responseBody  = json::object();
    responseBody["data"] = users;
    res.set_header("Content-Type", "application/json");
    res.body = responseBody.dump();
    res.code = 201;
    res.end();
}

void UserController::getUser(const crow::request& req, crow::response& res, const std::string& id)
{
    res.code = 200;
    res.end();
}

void UserController::updateUser(const crow::request& req, crow::response& res, const std::string& id)
{
    res.code = 200;
    res.end();
}

void UserController::deleteUser(const crow::request& req, crow::response& res, const std::string& id)
{
    res.code = 200;
    res.end();
}

}}