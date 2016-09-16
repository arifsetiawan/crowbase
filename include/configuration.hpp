#pragma once

#include <string>
#include <cpptoml.h>

namespace nextflow {
namespace users {

/**
 * \brief Singleton class for configuration using TOML
 *
 * TODO:
 * - get<int> give error cpptoml.h:318:5: error: static_assert failed "invalid value type"
 */
class Configuration
{
public:
    static Configuration instance(void)
    {
        static Configuration singleton;
        return singleton;
    }

    template<class T> 
    auto get(const std::string& key) {
        if (config == nullptr)
            config =  cpptoml::parse_file("config.toml");

        auto val = config->get_qualified_as<T>(key);
        if (val)
            return *val;
        
        throw std::runtime_error("No config entry for " + key);
        return *val;
    }
private:
    Configuration() {}

    std::shared_ptr<cpptoml::table> config;
};

}}