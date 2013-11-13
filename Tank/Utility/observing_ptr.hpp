/* This file is part of Tank.
 *
 * Tank is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Tank is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License and
 * the GNU Lesser General Public Licence along with Tank. If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * Copyright 2013 (©) Jamie Bayne, David Truby, David Watson.
 */

#ifndef TANK_OBSERVING_PTR
#define TANK_OBSERVING_PTR
#include <memory>
#include <functional>

namespace tank
{

template <typename T>
class observing_ptr
{
    friend struct std::hash<observing_ptr>;
    template <typename U> friend class observing_ptr;
	T* p_ = nullptr;
public:
    observing_ptr() = default;

    template <typename U>
    observing_ptr(const std::unique_ptr<U>& ptr) : p_{ptr.get()} {}

    observing_ptr(std::nullptr_t) : p_{nullptr} {}

    template <typename U>
    observing_ptr(const observing_ptr<U>& ptr) : p_{ptr.p_} {}

    template <typename U>
    observing_ptr(U* ptr) : p_{ptr} {}

    T const& operator* () const
	{
		return *p_;
	}

    T const* operator->() const
	{
		return p_;
	}

    T& operator* ()
	{
		return *p_;
	}

    T* operator->()
	{
		return p_;
	}

    explicit operator bool() const
    {
        return p_;
    }

    bool operator==(const observing_ptr& other) const
    {
        return p_ == other.p_;
    }

    bool operator==(const std::unique_ptr<T>& other) const
    {
        return p_ == other.get();
    }

    bool operator==(const T* const other) const
    {
        return p_ == other;
    }

    bool operator!=(const observing_ptr& other) const
    {
        return p_ != other.p_;
    }

    bool operator!=(const std::unique_ptr<T>& other) const
    {
        return p_ != other.get();
    }

    bool operator!= (const T* const other) const
    {
        return p_ != other;
    }

    T* get() {
        return p_;
    }
};


template <typename T, typename U>
bool operator==(const T& lhs, const observing_ptr<U>& rhs)
{
    return rhs == lhs;
}

template <typename T, typename U>
bool operator!=(const T& lhs, const observing_ptr<U>& rhs)
{
    return rhs != lhs;
}

}

namespace std
{
template<typename T>
struct hash<tank::observing_ptr<T>>
{
	size_t operator()(const tank::observing_ptr<T>& ptr) const
	{
		return std::hash<T>(ptr.p_);
	}
};
}

#endif
