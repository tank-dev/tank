#ifndef TANK_OBSERVING_PTR
#define TANK_OBSERVING_PTR
#include <memory>
#include <functional>

namespace tank
{

template <typename T>
class observing_ptr
{
	friend class std::hash<T>;
	T* p_ = nullptr;
public:
	observing_ptr(std::unique_ptr<T> ptr) : p_(ptr.get()) {}

	observing_ptr& operator* ()
	{
		return *p_;
	}

	observing_ptr* operator->()
	{
		return p_;
	}
};

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
