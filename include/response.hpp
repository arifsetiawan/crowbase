
#include <string>

namespace nextflow {
namespace users {

/**
 * \brief Make error JSON response following jsonapi.org spec
 */
std::string error(int status, std::string& title, std::string& description);  

}}