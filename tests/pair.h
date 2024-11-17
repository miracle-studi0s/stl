#pragma once

template<typename A, typename B> 
struct pair_t {
	A first{};
	B second{};

	pair_t(A a, B b) : first(a), second(b) {}
	pair_t(A&& a, B&& b) : first(a), second(b) {}

	void make(A a, B b) {
		first = (a);
		second = (b);
	}

	void make(A&& a, B&& b) {
		first = std::forward<A>(a);
		second = std::forward<B>(b);
	}
};