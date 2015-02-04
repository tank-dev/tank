#ifndef TANK_RESOURCES_HPP
#define TANK_RESOURCES_HPP

#include <boost/any.hpp>
#include <unordered_map>
#include <string>

namespace tank
{

class Resources
{
    static std::unordered_map<std::string, boost::any> resources;

public:
    template <typename Res>
    static Res& get(const std::string& path)
    {
        if (resources.count(path) == 0) {
            resources.emplace(std::make_pair(path, Res()));
            Res& res = boost::any_cast<Res&>(resources[path]);
            res.load(path);
            return res;
        }
        return boost::any_cast<Res&>(resources[path]);
    }
};
}
#endif /* TANK_RESOURCES_HPP */
