
#pragma once
#include "crow.h"
#include <string>
#include <memory>
#include "database.h"

namespace nextflow {
namespace users {

/**
 * \brief Crow User controller
 */
class UserController {
 public:
    UserController(const std::shared_ptr<DatabaseClient>& database);
    void createUser(const crow::request& req, crow::response& res);
    void getUsers(const crow::request& req, crow::response& res);
    void getUser(const crow::request& req, crow::response& res, const std::string& id);
    void updateUser(const crow::request& req, crow::response& res, const std::string& id);
    void deleteUser(const crow::request& req, crow::response& res, const std::string& id);

private:
    std::shared_ptr<DatabaseClient> database; 
};

}}