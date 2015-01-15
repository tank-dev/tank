#ifndef TANK_GEOMLOOKUP_HPP
#define TANK_GEOMLOOKUP_HPP

#include <algorithm>
#include <array>
#include <map>
#include <functional>
#include <utility>
#include <vector>
#include <exception>
#include <stdexcept>
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm_ext.hpp>
#include <boost/range/numeric.hpp>

namespace tank
{

template <typename T, typename GetCoordinates, typename Key = unsigned>
class GeometricLookup
{
    using coord_type = decltype(GetCoordinates{}(std::declval<T>()));
    // FIXME: this is invariably void
    using ordinate_type = decltype(std::get<1>(std::declval<coord_type>()));
    using map_type = std::multimap<Key, T>;
    static constexpr std::size_t depth = sizeof(Key) * 8 / 2;

    map_type contents_;
    std::function<coord_type(T const&) > get_coordinates = GetCoordinates{};
    const coord_type top_left;
    std::array<coord_type, depth> midpoints_;

public:
    using key_type = Key;
    using value_type = T;
    using size_type = typename map_type::size_type;
    using difference_type = typename map_type::difference_type;
    using reference = value_type&;
    using const_reference = value_type const&;
    using iterator = typename map_type::iterator;
    using const_iterator = typename map_type::const_iterator;
    using reverse_iterator = typename map_type::reverse_iterator;
    using const_reverse_iterator = typename map_type::const_reverse_iterator;
    /*
    using allocator_type = Allocator;
    using pointer = T*;
    using const_pointer = T const*;
    */

    GeometricLookup(coord_type const& bottom_right) : top_left(0, 0)
    {
        midpoints_ = gen_midpoints(this->top_left, bottom_right);
    }
    GeometricLookup(coord_type const& top_left, coord_type const& bottom_right)
        : top_left(top_left)
    {
        midpoints_ = gen_midpoints(this->top_left, bottom_right);
    }

    /* std container functions */
    bool empty() const
    {
        return contents_.empty();
        // could return contents empty AND all node contents empty
        // however, current impl prevents empty nodes
    }

    std::size_t size() const { return contents_.size(); }
    std::size_t max_size() const { return contents_.max_size(); }

    void clear() { contents_.clear(); }

    void insert(const_reference item)
    {
        key_type key = hash(get_coordinates(item));
        contents_.emplace(key, item);
    }

    void insert(value_type&& item)
    {
        key_type key = hash(get_coordinates(item));
        contents_.emplace(key, std::move(item));
    }

    template <typename... Args>
    void emplace(Args&&... args)
    {
        // FIXME: this isn't actually emplacing and that might be nasty?
        insert(std::move(value_type(std::forward<Args>(args)...)));
    }

    std::vector<std::reference_wrapper<value_type>>
    within_region(coord_type const& top_left, coord_type const& bottom_right)
    {
        return within_region<value_type>(top_left, bottom_right);
    }

    std::vector<std::reference_wrapper<const value_type>>
    within_region(coord_type const& top_left,
                  coord_type const& bottom_right) const
    {
        return within_region<const value_type>(top_left, bottom_right);
    }
    /*
    void insert(value_type&& item)
    {
        contents_.push_back(std::move(item));
    }
    */

    iterator begin() { return contents_.begin(); }
    iterator begin() const { return cbegin(); }
    iterator end() { return contents_.end(); }
    iterator end() const { return cend(); }
    const_iterator cbegin() const { return contents_.cbegin(); }
    const_iterator cend() const { return contents_.cend(); }
    reverse_iterator rbegin() { return contents_.rbegin(); }
    reverse_iterator rbegin() const { return crbegin(); }
    reverse_iterator rend() { return contents_.rend(); }
    reverse_iterator rend() const { return crend(); }
    const_reverse_iterator crbegin() const { return contents_.crbegin(); }
    const_reverse_iterator crend() const { return contents_.crend(); }

private:
    key_type hash(coord_type const& coords) const
    {
        static_assert(std::is_unsigned<key_type>::value,
                      "Lookup key_type must be unsigned");

        // translate coordinates so that top-left is at 0
        auto x = std::get<0>(coords) - std::get<0>(top_left);
        auto y = std::get<1>(coords) - std::get<1>(top_left);

        key_type hash = 0;

        // if x > midpoint then 1, else 0, shift left, repeat.
        // adjust x position so always considering range [0,2*midpoint]
        for (unsigned i = 0; i < depth; ++i) {
            const auto midX = std::get<0>(midpoints_[i]);
            const auto midY = std::get<1>(midpoints_[i]);

            const bool bitX = (x > midX);
            const bool bitY = (y > midY);

            hash <<= 1;
            hash += bitX;
            hash <<= 1;
            hash += bitY;

            x -= midX * bitX;
            y -= midY * bitY;
        }

        return hash;
    }

    std::array<coord_type, depth> gen_midpoints(coord_type const& p1,
                                                coord_type const& p2)
    {
        auto width = std::get<0>(p2) - std::get<0>(p1);
        auto height = std::get<1>(p2) - std::get<1>(p1);

        std::array<coord_type, depth> result;
        for (unsigned i = 0; i < depth; ++i) {
            width /= 2;
            height /= 2;
            result[i] = coord_type(width, height);
        }
        return result;
    }

    template <typename U>
    std::vector<std::reference_wrapper<U>>
    within_region(coord_type const& top_left, coord_type const& bottom_right)
    {
        auto outsideRegion = std::not1(Within{top_left, bottom_right});
        const auto begin = contents_.lower_bound(hash(top_left));
        const auto end = contents_.upper_bound(hash(bottom_right));
        std::vector<std::reference_wrapper<value_type>> result;

        std::transform(begin, end, std::back_inserter(result),
                       std::mem_fn(&map_type::value_type::second));
        boost::remove_erase_if(
            result, std::bind(outsideRegion, std::bind(get_coordinates,
                                                       std::placeholders::_1)));
        return result;
    }

    struct Within {
        using argument_type = coord_type const&;
        coord_type top_left, bottom_right;

        Within(argument_type top_left, argument_type bottom_right)
            : top_left(top_left), bottom_right(bottom_right)
        {
        }

        bool operator()(argument_type coord) const
        {
            const auto top = std::get<1>(top_left);
            const auto left = std::get<0>(top_left);
            const auto bottom = std::get<1>(bottom_right);
            const auto right = std::get<0>(bottom_right);
            const auto x = std::get<0>(coord);
            const auto y = std::get<1>(coord);
            return x >= left and x <= right and y >= top and y <= bottom;
        }
    };
};
} /* tank */
#endif /* TANK_GEOMLOOKUP_HPP */
