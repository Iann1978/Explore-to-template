#include <iostream>

struct A; struct B;
template <typename T>
struct Switcher_ {
	constexpr static size_t value = 0;
};

template <>
struct Switcher_<A> {
	constexpr static size_t value = 1;
};

template <>
struct Switcher_<B> {
	constexpr static size_t value = 2;
};


template <typename T>
constexpr size_t AnotherSwitcher = 0;

template <>
constexpr size_t AnotherSwitcher<A> = 1;

template <>
constexpr size_t AnotherSwitcher<B> = 2;

template <typename TW>
struct Wrapper {
	template <typename T>
	struct Fun_ {
		constexpr static size_t value = 0;
	};

	template<>
	struct Fun_<A> {
		constexpr static size_t value = 1;
	};
};


template <bool IsFeedbackOut, typename T,
	std::enable_if_t<IsFeedbackOut>* = nullptr>
	auto FeedbackOut_(T&& param) 
{
	std::cout << "IsFeedbackOut is true. and param = " << param << std::endl;
};

template <bool IsFeedbackOut, typename T,
	std::enable_if_t<!IsFeedbackOut>* = nullptr>
	auto FeedbackOut_(T&& param)
{
	std::cout << "IsFeedbackOut is false. and param = " << param << std::endl;
};

template <bool Check, std::enable_if_t<Check>* = nullptr>
auto CheckFun() {
	return (int)0;
}

template <bool Check, std::enable_if_t<!Check>* = nullptr>
auto CheckFun() {
	return (float)1;
}

template <bool Check>
auto wrap2() {
	return CheckFun<Check>();
}

template <typename T, std::enable_if_t<std::is_same<T,float>::value>* = nullptr>
auto TypedFun() {
	return (float)5;
}
template <typename T, std::enable_if_t<std::is_same<T, double>::value>* = nullptr>
auto TypedFun() {
	return (double)6;
}
template <typename T, std::enable_if_t<std::is_same<T, int>::value>* = nullptr>
auto TypedFun() {
	return (int)7;
}

// Circulation
template <size_t Input>
constexpr size_t OnesCount = (Input % 2) + OnesCount<Input / 2>;

template <> constexpr size_t OnesCount<0> = 0;

template <size_t... Inputs>
constexpr size_t Accumulate = 0;

template <size_t CurInput, size_t... Inputs>
constexpr size_t Accumulate<CurInput, Inputs...> = CurInput + Accumulate<Inputs...>;

template<typename ...Args>
void printer(Args&&... args) {
	(std::cout << ... << args) << '\n';
}

template <size_t... values>
constexpr size_t Accumulate2()
{
	return (0 + ... + values);
}

constexpr size_t sumNumbers = Accumulate2<1, 2, 3, 4, 5>();
int main()
{
	std::cout << "Hello Sequence and Switcher!!!" << std::endl;

	std::cout << "Switcher_<A>::value = " << Switcher_<A>::value << std::endl;
	std::cout << "Switcher_<B>::value = " << Switcher_<B>::value << std::endl;

	std::cout << "AnotherSwitcher<A> = " << AnotherSwitcher<A> << std::endl;
	std::cout << "AnotherSwitcher<B> = " << AnotherSwitcher<B> << std::endl;

	std::cout << "Wrapper<A>::Fun_<A>::value = " << Wrapper<A>::Fun_<A>::value << std::endl;



	FeedbackOut_<false>(5);
	FeedbackOut_<true>(6);

	std::cout << "wrap2<true>() = " << wrap2<true>() << std::endl;
	std::cout << "wrap2<false>() = " << wrap2<false>() << std::endl;

	std::cout << "TypedFun<float>() = " << TypedFun<float>() << std::endl;
	std::cout << "TypedFun<double>() = " << TypedFun<double>() << std::endl;
	std::cout << "TypedFun<int>() = " << TypedFun<int>() << std::endl;

	std::cout << "OnesCout<45> is " << OnesCount<45> << std::endl;

	std::cout << "Accumulate<2,3,4,5> is " << Accumulate<2, 3, 4, 5, 6> << std::endl;
	std::cout << "Accumulate2<2,3,4,5> is " << Accumulate2<1,2,3,4,5>() << std::endl;

	

	printer("The number is ", sumNumbers);
	return 0;
}
