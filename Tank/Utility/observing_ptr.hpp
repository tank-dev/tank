// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_OBSERVING_PTR
#define TANK_OBSERVING_PTR
#include <memory>
#include <functional>

namespace tank
{

/*! \brief Dumb pointer class.
 *
 * This class exists to protect memory that is owned by the game engine from
 * being modified by users. Although a raw pointer could be used here, using a
 * dumb pointer class makes it clear that the user is not expected to manage the
 * memory.
 */
template <typename T>
class observing_ptr
{
    friend struct std::hash<observing_ptr>;
    template <typename U>
    friend class observing_ptr;
    T* p_ = nullptr;

public:
    /*! \brief Default constructor
     *
     * Sets the pointer to null.
     */
    observing_ptr() = default;

    /// TODO: Why does this exist?
    observing_ptr(T& x) : p_(&x) {}

    /*! \brief Construct from a unique_ptr.
     *
     * This allows construction from a unique pointer, setting the observing_ptr
     * to the same address. This does not perform a copy. The reason this does
     * not break unique_ptr's uniqueness contract is that observing_ptr is not
     * an owning smart pointer and cannot delete its internal pointer.
     */
    observing_ptr(const std::unique_ptr<T>& ptr)
        : p_{ptr.get()}
    {
    }

    observing_ptr(std::nullptr_t) : p_{nullptr} {}

    template <typename U>
    observing_ptr(const observing_ptr<U>& ptr)
        : p_{ptr.p_}
    {
    }

    template <typename U>
    observing_ptr(U* ptr)
        : p_{ptr}
    {
    }

    T const& operator*() const { return *p_; }

    T const* operator->() const { return p_; }

    T& operator*() { return *p_; }

    T* operator->() { return p_; }

    explicit operator bool() const { return p_ != nullptr; }

    bool operator==(const observing_ptr& other) const { return p_ == other.p_; }

    bool operator==(const std::unique_ptr<T>& other) const
    {
        return p_ == other.get();
    }

    bool operator==(const T* const other) const { return p_ == other; }

    bool operator!=(const observing_ptr& other) const { return p_ != other.p_; }

    bool operator!=(const std::unique_ptr<T>& other) const
    {
        return p_ != other.get();
    }

    bool operator!=(const T* const other) const { return p_ != other; }

    T* get() { return p_; }

    explicit operator T&() { return *p_; }

    explicit operator T&() const { return *p_; }
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
template <typename T>
struct hash<tank::observing_ptr<T>> {
    size_t operator()(const tank::observing_ptr<T>& ptr) const
    {
        return std::hash<T>(ptr.p_);
    }
};
}

#endif
