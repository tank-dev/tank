#pragma once
#include <boost/any.hpp>
#include <unordered_map>
#include <string>

class Resources
{
    static std::unordered_map<std::string, boost::any> resources;
    
public:
    template<typename Res>
    static Res& get(const std::string& path) {
        if (resources.count(path) == 0) {
            resources.emplace(std::make_pair(path, Res()));
            Res& res = boost::any_cast<Res&>(resources[path]);
            res.loadFromFile(path);
            return res;
        }
        return boost::any_cast<Res&>(resources[path]);
    }
};