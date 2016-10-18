#include <iostream>
#include <string>

template<typename T>
class EmptyOnWrite
{
public:
	inline static void OnWrite(T& var)
	{
	}
};

template<typename T>
class EmptyOnRead
{
public:
	inline static void OnRead(T& var)
	{
	}
};

template<typename T>
class EmptyMangle
{
public:
	inline static T Mangle(T& other)
	{
		return other;
	}
};

template<typename T>
class EmptyDeMangle
{
public:
	inline static T DeMangle(T& other)
	{
		return other;
	}
};

// TODO:
// thread safety
// increfs and decrefs: move constructors

template<typename T,
	typename Mangle = EmptyMangle<T>, typename DeMangle = EmptyDeMangle<T>,
	typename OnWrite = EmptyOnWrite<T>, typename OnRead = EmptyOnRead<T> >
class VarWrap
{
public:
	T _inner;

public:
	inline T inner()
	{
		OnRead::OnRead(_inner);
		return DeMangle::DeMangle(_inner);
	}

	inline void set(T& val)
	{
		_inner = Mangle::Mangle(val);
		OnWrite::OnWrite(_inner);
	}

	inline VarWrap()
	{
		memset(&_inner, 0, sizeof(T));
	}

	inline VarWrap(T var)
	{
		set(var);
	}

	// Arithmetic Operators
	inline T operator+(T var)
	{
		return inner() + var;
	}

	template<typename U>
	inline T operator+(U other)
	{
		return inner() + other.inner();
	}

	inline T operator-(T var)
	{
		return inner() - var;
	}

	template<typename U>
	inline T operator-(U other)
	{
		return inner() - other.inner();
	}

	inline T operator*(T var)
	{
		return inner() * var;
	}

	template<typename U>
	inline T operator*(U other)
	{
		return inner() * other.inner();
	}

	inline T operator/(T var)
	{
		return inner() / var;
	}

	template<typename U>
	inline T operator/(U other)
	{
		return inner() / other.inner();
	}

	inline T operator%(T var)
	{
		return inner() % var;
	}

	template<typename U>
	inline T operator%(U other)
	{
		return inner() % other.inner();
	}

	inline T operator++(int)
	{
		T val = inner() + 1;
		_inner = Mangle::Mangle(val);
		return inner();
	}

	inline T operator--(int)
	{
		T val = inner() - 1;
		_inner = Mangle::Mangle(val);
		return inner();
	}

	// Relational Operators
	inline bool operator==(T var)
	{
		return (inner() == var);
	}

	template<typename U>
	inline bool operator==(U other)
	{
		return (inner() == other.inner());
	}

	inline bool operator>(T var)
	{
		return (inner() > var);
	}

	template<typename U>
	inline bool operator>(U other)
	{
		return (inner() > other.inner());
	}

	inline bool operator<(T var)
	{
		return (inner() < var);
	}

	template<typename U>
	inline bool operator<(U other)
	{
		return (inner() < other.inner());
	}

	inline bool operator>=(T var)
	{
		return (inner() >= var);
	}

	template<typename U>
	inline bool operator>=(U other)
	{
		return (inner() >= other.inner());
	}

	inline bool operator<=(T var)
	{
		return (inner() <= var);
	}

	template<typename U>
	inline bool operator<=(U other)
	{
		return (inner() <= other.inner());
	}

	// Assignment Operators
	inline void operator=(T var)
	{
		set(var);
	}

	template<typename U>
	inline void operator=(U other)
	{
		set(other.inner());
	}

	inline void operator+=(T var)
	{
		T t = inner();
		t += var;
		set(t);
	}

	template<typename U>
	inline void operator+=(U other)
	{
		T t = inner();
		t += other.inner();
		set(t);
	}

	inline void operator-=(T var)
	{
		T t = inner();
		t -= var;
		set(t);
	}

	template<typename U>
	inline void operator-=(U other)
	{
		T t = inner();
		t -= other.inner();
		set(t);
	}

	inline void operator*=(T var)
	{
		T t = inner();
		t *= var;
		set(t);
	}

	template<typename U>
	inline void operator*=(U other)
	{
		T t = inner();
		t *= other.inner();
		set(t);
	}

	inline void operator/=(T var)
	{
		T t = inner();
		t /= var;
		set(t);
	}

	template<typename U>
	inline void operator/=(U other)
	{
		T t = inner();
		t /= other.inner();
		set(t);
	}

	inline void operator%=(T var)
	{
		T t = inner();
		t %= var;
		set(t);
	}

	template<typename U>
	inline void operator%=(U other)
	{
		T t = inner();
		t %= var;
		set(t);
	}

	inline void operator<<=(size_t var)
	{
		T t = inner();
		t <<= var;
		set(t);
	}

	inline void operator>>=(size_t var)
	{
		T t = inner();
		t >>= var;
		set(t);
	}

	inline void operator&=(size_t var)
	{
		T t = inner();
		t &= var;
		set(t);
	}

	inline void operator^=(size_t var)
	{
		T t = inner();
		t ^= var;
		set(t);
	}

	inline void operator|=(size_t var)
	{
		T t = inner();
		t |= var;
		set(t);
	}
};

template<typename T>
class OnReadWriteCout
{
public:
	inline static void OnWrite(T& var)
	{
		std::cout << var;
	}

	inline static void OnRead(T& var)
	{
		std::cout << var;
	}
};

template<typename T>
class Mangler
{
public:
	inline static T DeMangle(T& var) { return var; }
	inline static T Mangle(T& var) { return var; }
};

template<typename T>
T test(T val)
{
	val++;
	val *= 2.0f;
	val--;
	val /= 2.0f;
	val++;
	return val;
}

#define VWFloat VarWrap<float, Mangler<float>, Mangler<float>, EmptyOnWrite<float>, EmptyOnRead<float>>

int main(int argc, char** argv)
{
	const float val = 3.0f;

	VarWrap<float, Mangler<float>, Mangler<float>, EmptyOnWrite<float>, EmptyOnRead<float>> vwf1 = val;
	VarWrap<float, Mangler<float>, Mangler<float>, EmptyOnWrite<float>, EmptyOnRead<float>> vwf2 = val;

	float nvwf = val;

	VWFloat vwf = val;

	float vals[4];
	vals[0] = test(val);
	vals[1] = test(vwf1).inner();
	vals[2] = test(vwf2).inner();
	vals[3] = test(vwf).inner();

	std::cin.get();
}
