
#include <json.hpp>

#include "response.hpp"

using json = nlohmann::json;

namespace nextflow {
namespace users {

std::string error(int status, std::string& title, std::string& description)
{
    json e;
    e["status""] = status;
    e["title"] = title;
    e["detail"] = detail;
}

}}