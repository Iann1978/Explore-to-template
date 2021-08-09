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

template <int a, int b>
struct Add_ {
	constexpr static int value = a + b;
};

template <int a, int b>
constexpr int Add = a + b;

constexpr int x1 = Add_<2, 3>::value;
constexpr int x2 = Add<2, 3>;

// Using template as the parameter of template
template <template <typename> class T1, typename T2>
struct Fun3_ {
	using type = typename T1<T2>::type;
};

template <template <typename> class T1, typename T2>
using Fun3 = typename Fun3_<T1, T2>::type;

template <bool AddOrRemoveRef> struct FunAddOrRemoveRef_;

template <>
struct FunAddOrRemoveRef_<true> {
	template <typename T>
	using type = std::add_lvalue_reference<T>;
};

template <>
struct FunAddOrRemoveRef_<false> {
	template <typename T>
	using type = std::remove_reference<T>;
};

template<typename T>
using MyAddReference = typename FunAddOrRemoveRef_<true>::type<T>;

template <int... Vals> struct IntContainer;
template <bool... Vals> struct BoolContainer;

template <typename... Types> struct TypeContainer;

template<template <typename> class... T> struct TemplateContainer;
template<template <typename...> class... T> struct TemplateContainer2;


template <typename T>
struct RemoveReferenceConst_ {
private:
	using inter_type = typename std::remove_reference<T>::type;
public:
	using type = typename std::remove_const<inter_type>::type;
};

template <typename T>
using RemoveReferenceConst = typename RemoveReferenceConst_<T>::type;





int main()
{
	std::cout << "Hello template meta!!!" << std::endl;

	Fun_<int>::type h = 3;
	std::cout << "Fun_<int>::type h = " << h << std::endl;
	
	Fun<int> hh = 4;
	std::cout << "Fun<int> hh = " << hh << std::endl;

	Fun1<double> a;
	std::cout << typeid(bool).name() << std::endl;

	std::remove_reference<int&>::type h1 = 5;
	std::cout << "std::remove_reference<int&>::type h1 = " << h1 << std::endl;

	std::remove_reference_t<int&> h2 = 6;
	std::cout << "std::remove_reference_t<int&> h2 = " << h2 << std::endl;

	std::cout << "Add_<2, 3>::value = " << x1 << std::endl;
	std::cout << "Add<2,3> = " << x2 << std::endl;

	const char* type_name1 = typeid(Fun3_<std::remove_reference, int&>::type).name();
	std::cout << "The type of Fun3_<std::remove_reference, int&>::type is " << type_name1 << std::endl;

	const char* type_nam32 = typeid(Fun3< std::remove_reference, int&>).name();
	std::cout << "The type of Fun3< std::remove_reference, int&> is " << type_name1 << std::endl;

	std::cout << "Code std::is_reference<int&> return " << std::is_reference<int&>::value << std::endl;
	std::cout << "Code std::is_reference<int> return " << std::is_reference<int>::value << std::endl;

	int aaa = 7;
	MyAddReference<int>::type bbb = aaa;
	//std::cout << "Code std::is_reference<int> return " << std::is_reference<int>::value << std::endl;


	//IntContainer<1, 2> intContainer;
	//std::cout << "The type of IntContainer<1,2> is " << typeid(IntContainer<1, 2>).name() 


	std::cout << "The type of RemoveReferenceConst<const int&> is " << typeid(RemoveReferenceConst<const int&>).name() << std::endl;


	std::cout << "The type of std::conditional_t<true, int, float> is " << typeid(std::conditional_t<true, int, float>).name() << std::endl;

	std::cout << "The type of std::conditional_t<false, int, float> is " << typeid(std::conditional_t<false, int, float>).name() << std::endl;



	return 0;
}
