
#include "user_controller.hpp"

namespace nextflow {
namespace users {

UserController::UserController(const std::shared_ptr<DatabaseClient>& database) :
    database(database)
{
}

void UserController::createUser(const crow::request& req, crow::response& res)
{
    res.code = 201;
    res.end();
}

void UserController::getUsers(const crow::request& req, crow::response& res)
{
    res.code = 200;
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