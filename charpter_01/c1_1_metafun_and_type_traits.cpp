#include <iostream>

constexpr int fun(int a) { return a + 1; }

template <typename T>
struct Fun_ { using type = T; };

template <>
struct Fun_<int> { using type = unsigned int; };

template<>
struct Fun_<long> { using type = unsigned long; };

template <typename T>
	using Fun = typename Fun_<T>::type;

template <typename T>
	struct Fun1 {};

int main()
{
	std::cout << "Hello template meta!!!" << std::endl;

	Fun_<int>::type h = 3;
	std::cout << "Fun_<int>::type h = " << h << std::endl;
	
	Fun<int> hh = 4;
	std::cout << "Fun<int> hh = " << hh << std::endl;

	Fun1<double> a;
	std::cout << typeid(bool).name() << std::endl;
	return 0;
}
