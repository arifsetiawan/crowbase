#include "crow.h"

#include <cassert>
#include <iostream>
#include <string>
#include <functional>
#include <sstream>

#include "user_controller.hpp"
#include "configuration.hpp"

using namespace std;
using namespace nextflow::users;

int main()
{
    crow::SimpleApp app;

    auto database = std::make_shared<DatabaseClient>();
    auto userController = std::make_shared<UserController>(database);

    CROW_ROUTE(app, "/hello")
        .methods("GET"_method)
    ([](const crow::request& req, crow::response& res) {
        res.body = "world";
        res.code = 200;
        res.end();
    });

    CROW_ROUTE(app, "/users")
        .methods("POST"_method,
                 "GET"_method)
    ([&userController](const crow::request& req, crow::response& res) {
        if (req.method == "POST"_method) 
            userController->createUser(req, res);
        else if (req.method == "GET"_method) 
            userController->getUsers(req, res);
        else {
            res.code = 404;
            res.end();
        }
    });

    CROW_ROUTE(app, "/users/<string>")
        .methods("POST"_method,
                 "GET"_method,
                 "DELETE"_method)
    ([&userController](const crow::request& req, crow::response& res, const std::string& id) {
        if (req.method == "POST"_method) 
            userController->updateUser(req, res, id);
        else if (req.method == "GET"_method) 
            userController->getUser(req, res, id);
        else if (req.method == "DELETE"_method) 
            userController->deleteUser(req, res, id);
        else {
            res.code = 404;
            res.end();
        }
    });

    auto port = Configuration::instance().get<std::string>("Server.port");
    app.port(std::stoul(port,nullptr,0)).multithreaded().run();
    
}
