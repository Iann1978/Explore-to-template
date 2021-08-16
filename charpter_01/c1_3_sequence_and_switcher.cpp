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


// 1.3.4 explode
//template <size_t Input>
//constexpr size_t OnesCount = (Input % 2) + OnesCount<(Input / 2)>;
//template <> constexpr size_t OnesCount<0> = 0;
constexpr size_t OnesCountOf7 = OnesCount<7>;
constexpr size_t OnesCountOf15 = OnesCount<15>;

template <size_t A>
struct Sum_ {
	template <size_t ID, typename TDummy = void>
	struct imp {
		constexpr static size_t value = ID + imp<ID-1>::value;
	};
	template <typename TDummy>
	struct imp<0, TDummy> {
		constexpr static size_t value = 0;
	};
	template <size_t ID>
	constexpr static size_t value = imp<A + ID>::value;
};

// 1.3.5 Switch choice and shortcut logic
template <size_t N>
constexpr bool is_odd = ((N % 2) == 1);

//template <size_t... Numbers>
//struct IsAllOdd_ {
//	constexpr static bool value = false;
//};

//template <size_t FirstNumber>
//struct IsAllOdd_ {
//	constexpr staticbool value = is_odd<FirstNumber>;
//};

template <size_t FirstNumber, size_t... Numbers>
struct IsAllOdd_ {
	//constexpr static bool value = is_odd<FirstNumber> && IsAllOdd_<Numbers...>::value;
	constexpr static bool value = AndValue<is_odd<FirstNumber>, IsAllOdd_<Numbers...>>;
};

template<size_t FirstNumber>
struct IsAllOdd_<FirstNumber>{
	constexpr static bool value = is_odd<FirstNumber>;
};

template <bool cur, typename TNext>
constexpr static bool AndValue = false;

template <typename TNext>
constexpr static bool AndValue<true, TNext> = TNext::value;

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

	std::cout << "OnesCount<45> is " << OnesCount<45> << std::endl;

	std::cout << "Accumulate<2,3,4,5> is " << Accumulate<2, 3, 4, 5, 6> << std::endl;
	std::cout << "Accumulate2<2,3,4,5> is " << Accumulate2<1,2,3,4,5>() << std::endl;


	std::cout << "OnesCount<7> is " << OnesCount<7> << std::endl;
	std::cout << "OnesCount<15> is " << OnesCount<15> << std::endl;
	std::cout << "OnesCount<45> is " << OnesCount<45> << std::endl;

	std::cout << "Sum of 1...(5+6) is " <<Sum_<5>::value<6> << std::endl;

	std::cout << "IsAllOdd_<1>::value is " << (IsAllOdd_<1>::value ? "true" : "false") << std::endl;
	std::cout << "IsAllOdd_<0>::value is " << (IsAllOdd_<0>::value ? "true" : "false") << std::endl;
	std::cout << "IsAllOdd_<1,3,5,7>::value is " << (IsAllOdd_<1, 3, 5, 7>::value ? "true" : "false") << std::endl;
	std::cout << "IsAllOdd_<2,4,6,7>::value is " << (IsAllOdd_<2, 4, 6, 7>::value ? "true" : "false") << std::endl;
	printer("The number is ", sumNumbers);
	return 0;
}
