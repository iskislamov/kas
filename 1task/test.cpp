#include <iostream>
#include <tuple>
#include <utility>
#include <cassert>


template<int...> struct index_tuple {};

template<int I, typename IndexTuple, typename... Types>
struct make_indexes_impl;

template<int I, int... Indexes, typename T, typename ... Types>
struct make_indexes_impl<I, index_tuple<Indexes...>, T, Types...>
{
	using type = typename make_indexes_impl<I + 1, index_tuple<Indexes..., I>, Types...>::type;
};

/*
template<int I, int... Indexes>
struct make_indexes_impl<I, index_tuple<Indexes...> >
{
	using type = index_tuple<Indexes...>;
};
*/

template<typename ... Types>
struct make_indexes : make_indexes_impl<0, index_tuple<>, Types...>
{};

template<class Base>
struct Proxy : Base {
	template<int... I, class... T>
	void call(index_tuple<I...>, std::tuple<T...>&& params)
	{
		Base(std::forward<T>(std::get<I>(params))...);
	}

	template<class ...T>
	Proxy(std::tuple<T...>&& params) {
		call(typename make_indexes<T...>::type(), std::forward<std::tuple<T...>>(params));
	}
};

struct Test {
	Test() = delete;
	Test(Test const&) = delete;
	Test(Test&&) = delete;

	Test(int a, int b, int c, std::string s) {
		assert(a == 7);
		assert(b == 42);
		assert(c == 12);
		assert(s == "asd");
		std::cout << "OK\n";
	}
};

/*
int main() {
	Proxy<Test>(std::forward_as_tuple(7, 42, 12, "asd"));
	system("pause");
	return 0;
}
*/