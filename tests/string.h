#pragma once
// pasted
// https://gist.github.com/deepanshululla/f5ae9f77c96f8e09478ad728f0f19dd4
template <typename T = char>
class c_string {
private:
	T* str{};
	size_t length{};
	size_t allocs{};

	inline int string_compare(const T* other) {
		if constexpr (std::is_same<T, wchar_t>::value)
			return g_vcruntime.wstrcmp(str, other);
		else
			return g_vcruntime.strcmp(str, other);
	}

public:
	c_string() {}

	~c_string() {
		if (allocs) {
			allocation::free(str);
		}
	}

	c_string(const T* str) : str(const_cast<T*>(str)) {
		if (str == nullptr) {
			length = 0;
		}
		else {
			if constexpr (std::is_same<T, wchar_t>::value)
				length = g_vcruntime.wstrlen(str);
			else
				length = g_vcruntime.strlen(str);
		}
	}

	c_string(const c_string& other)
		: str(other.str), length(other.length) {}

	c_string(c_string&& other) noexcept {
		str = other.str;
		length = other.length;
		other.str = nullptr;
		other.length = 0;
	}

	T& operator[](int index) {
		return str[index];
	}

	c_string& operator=(const c_string& other) {
		str = other.str;
		length = other.length;
		return *this;
	}

	c_string& operator=(c_string&& other) noexcept {
		str = other.str;
		length = other.length;
		other.str = nullptr;
		other.length = 0;
		return *this;
	}

	c_string operator+(const c_string& other) {
		c_string s{};
		s.length = length + other.length;
		s.str = static_cast<T*>(allocation::malloc(sizeof(T) * (s.length + 1)));

		if constexpr (std::is_same<T, wchar_t>::value) {
			s.str = g_vcruntime.strcpy(s.str, str);
			s.str = g_vcruntime.strcatW(s.str, other.str);
		}
		else {
			s.str = g_vcruntime.strcpy(s.str, str);
			s.str = g_vcruntime.strcatA(s.str, other.str);
		}

		++s.allocs;
		return s;
	}

	// cringe but w/e
	bool operator==(c_string& other) {
		return string_compare(other.str) == 0;
	}

	bool operator==(const T* other) {
		return string_compare(other) == 0;
	}

	bool operator!=(c_string& other) {
		return string_compare(other.str) != 0;
	}

	bool operator!=(const T* other) {
		return string_compare(other) != 0;
	}

	size_t size() const {
		return length;
	}

	const T* data() const {
		return str;
	}
};