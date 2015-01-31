// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_OBSERVING_PTR
#define TANK_OBSERVING_PTR
#include <memory>
#include <functional>
#include <type_traits>

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

    template <typename U> using not_bool_convertible =
        std::enable_if_t<!std::is_convertible<U, bool>::value, T>;

    T* p_ = nullptr;

public:
    /*! \brief Default constructor
     *
     * Sets the pointer to null.
     */
    observing_ptr() = default;

    /*! \brief Copy constructor.
     *
     * This allows copy construction from another observing_ptr. It takes an
     * observing_ptr of type U instead of T to allow conversion from a pointer
     * to a derived type to a pointer to a base type.
     */
    template <typename U>
    observing_ptr(const observing_ptr<U>& ptr)
        : p_{ptr.p_}
    {
    }

    /*! \brief Construct from a nullptr.
     *
     * This ensures that when constructing with the new nullptr value in C++11
     * the inner pointer is constructed properly.
     */
    observing_ptr(std::nullptr_t) : p_{nullptr} {}

    /*! \brief Construct from a unique_ptr.
     *
     * This allows construction from a unique pointer, setting the observing_ptr
     * to the same address. This does not perform a copy. The reason this does
     * not break unique_ptr's uniqueness contract is that observing_ptr is not
     * an owning smart pointer and cannot delete its internal pointer.
     *
     * This takes a unique_ptr of type U to allow conversion from a unique_ptr
     * to a derived type to an observing_ptr of base type.
     */
    //template <typename U>
    observing_ptr(const std::unique_ptr<T>& ptr)
        : p_{ptr.get()}
    {
    }

    /*! \brief Constructor from a raw pointer.
     *
     * This allows construction from a raw pointer, setting the observing_ptr
     * to the same address. This allows raw pointers to be wrapped in
     * observing_ptrs for safety.
     *
     * This takes a raw pointer of type U to allow conversion from a raw pointer
     * to a derived type to an observing_ptr of base type.
     */
    template <typename U>
    observing_ptr(U* ptr)
        : p_{ptr}
    {
    }

    /*! \brief Constructor from a reference.
     *
     * This constructor exists to aid the use of certain STL algorithms.
     *
     * \deprecated This is hacky and doesn't fit well with other constructors
     *             for this class. It will probably be removed once uses of it
     *             in the engine itself are removed.
     *
     */
    observing_ptr(T& ref) : p_{&ref} {}

    /*! \brief Dereference operator.
     *
     * This operator behaves exactly as if the pointer was a raw pointer.
     * __This means that calling these functions on a null pointer
     * exhibits undefined behavior.__
     *
     * \returns The pointer to value.
     */
    T& operator*() const { return *p_; }

    /*! \brief Member access operator.
     *
     * \copydetails operator*()
     */
    T* operator->() const { return p_; }

    /*! \brief Explicit bool conversion operator.
     *
     * \return Whether the pointer is null.
     *
     */
    explicit operator bool() const { return p_ != nullptr; }

    /*! \brief Equality comparison with observing_ptr.
     *
     * \note This performs a pointer comparison, not an object comparison.
     *
     * \return Whether the pointers are equal.
     */
    bool operator==(const observing_ptr<T>& other) const
    {
        return p_ == other.p_;
    }

    /*! \brief Inequality comparison with observing_ptr.
     *
     * \note This performs a pointer comparison, not an object comparison.
     *
     * \return Whether the pointers are not equal.
     */
    bool operator!=(const observing_ptr<T>& other) const
    {
        return !(*this == other);
    }

    /*! \brief Equality comparison with unique_ptr.
     *
     * \note This performs a pointer comparison, not an object comparison.
     *
     * \return Whether the pointers are equal.
     *
     */
    bool operator==(const std::unique_ptr<T>& other) const
    {
        return p_ == other.get();
    }

    /*! \brief Inequality comparison with unique_ptr.
     *
     * \note This performs a pointer comparison, not an object comparison.
     *
     * \return Whether the pointers are not equal.
     *
     */
    bool operator!=(const std::unique_ptr<T>& other) const
    {
        return !(*this == other);
    }

    /*! \brief Equality comparison with raw pointer.
     *
     * \note This performs a pointer comparison, not an object comparison.
     *
     * \return Whether the pointers are equal.
     *
     */
    bool operator==(const T* const other) const { return p_ == other; }

    /*! \brief Inequality comparison with raw pointer.
     *
     * \note This performs a pointer comparison, not an object comparison.
     *
     * \return Whether the pointers are not equal.
     *
     */
    bool operator!=(const T* const other) const { return !(*this == other); }

    /*! \brief Equality comparison with reference.
     *
     * \deprecated This is quite an odd function to have, and doesn't really
     *             match the behaviour of the others. It may be removed once
     *             uses of it are removed from the rest of the engine.
     *
     */
    bool operator==(const T& other) const { return *p_ == other; }

    /*! \brief Inequality comparison with reference.
     *
     * \deprecated This is quite an odd function to have, and doesn't really
     *             match the behaviour of the others. It may be removed once
     *             uses of it are removed from the rest of the engine.
     *
     */
    bool operator!=(const T& other) const { return *p_ != other; }

    /*! \brief Return the contained pointer.
     *
     * This doesn't check for null, so it will return a null pointer if the
     * observing_ptr is null.
     */
    T* get() { return p_; }

    /*! \brief Implicit conversion to reference.
     *
     * This allows users to use references as opposed to observing_ptrs if they
     * don't require the reference to be rebindable, for example for an entity
     * in a world that will always exist.
     *
     * \note For normal usage the return type of this function can be considered
     *       to be T&.
     *       This function is only available when the class is not convertible
     *       to bool. This is due to issues with overload resolution, and is the
     *       reason that the type is more complex than a normal conversion
     *       operator.

     * \return A reference to the contained object.
     */
    template <typename U = T>
    operator not_bool_convertible<U>& () { return *p_; }

    /*! \brief Implicit conversion to const reference.
     *
     * This allows users to use references as opposed to observing_ptrs if they
     * don't require the reference to be rebindable, for example for an entity
     * in a world that will always exist.
     *
     * \note For normal usage the return type of this function can be considered
     *       to be const T&.
     *       This function is only available when the class is not convertible
     *       to bool. This is due to issues with overload resolution, and is the
     *       reason that the type is more complex than a normal conversion
     *       operator.
     *
     * \return A reference to the contained object.
     */
    template <typename U = T>
    operator const not_bool_convertible<U>&() const { return *p_; }
};

/*! \copydoc observing_ptr::operator==(const T&) const
 *
 * \relates observing_ptr
 */
template <typename T, typename U>
bool operator==(const T& lhs, const observing_ptr<U>& rhs)
{
    return rhs == lhs;
}

/*! \copydoc observing_ptr::operator!=(const T&) const
 *
 * \relates observing_ptr
 */
template <typename T, typename U>
bool operator!=(const T& lhs, const observing_ptr<U>& rhs)
{
    return rhs != lhs;
}


/*! \copydoc observing_ptr::operator==(const std::unique_ptr<T>&) const
 *
 * \relates observing_ptr
 */
template <typename T, typename U>
bool operator==(const std::unique_ptr<T>& lhs, const observing_ptr<U>& rhs)
{
    return rhs == lhs;
}

/*! \copydoc observing_ptr::operator!=(const std::unique_ptr<T>&) const
 *
 * \relates observing_ptr
 */
template <typename T, typename U>
bool operator!=(const std::unique_ptr<T>& lhs, const observing_ptr<U>& rhs)
{
    return rhs != lhs;
}

/*! \copydoc observing_ptr::operator==(const T* const) const
 *
 * \relates observing_ptr
 */
template <typename T, typename U>
bool operator==(const T* const lhs, const observing_ptr<U>& rhs)
{
    return rhs == lhs;
}

/*! \copydoc observing_ptr::operator!=(const T* const) const
 *
 * \relates observing_ptr
 */
template <typename T, typename U>
bool operator!=(const T* const lhs, const observing_ptr<U>& rhs)
{
    return rhs != lhs;
}
}

namespace std
{
/*! \brief Hash function on observing_ptr.
 *
 * This allows the observing_ptr to be stored in std::unordered_set and
 * std::unordered_map. It simply returns the hash of the internal pointer.
 */
template <typename T>
struct hash<tank::observing_ptr<T>> {
    size_t operator()(const tank::observing_ptr<T>& ptr) const
    {
        return std::hash<T*>{}(ptr.p_);
    }
};
}

#endif
