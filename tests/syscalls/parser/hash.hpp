#pragma once

#include <memory>
#include "win.hpp"

using hash_t = uint32_t;

namespace hash {
	constexpr uint32_t val_32_const = 0x811c9dc5;
	constexpr uint32_t prime_32_const = 0x1000193;

	template<typename T>
	inline constexpr uint32_t hash_32_fnv1a_const(T const str, const uint32_t value = val_32_const) noexcept {
		return (str[0] == '\0') ? value : hash_32_fnv1a_const(&str[1], (value ^ uint32_t((uint8_t)str[0])) * prime_32_const);
	}

	template<typename T>
	constexpr hash_t compute_hash(T string) {
		return hash_32_fnv1a_const(string);
	}

	constexpr hash_t get_hash(const wchar_t* const string) {
		return compute_hash(string);
	}

	constexpr hash_t get_hash(const char* const string) {
		return compute_hash(string);
	}

	constexpr hash_t get_hash(const win::_UNICODE_STRING& string) {
		return compute_hash(string.Buffer);
	}

	constexpr unsigned int get_hash(unsigned int x) {
		x = ((x >> 16) ^ x) * 0x45d9f3b;
		x = ((x >> 16) ^ x) * 0x45d9f3b;
		x = (x >> 16) ^ x;
		return x;
	}
}

#define HASH_CT(data)                                            \
  [&]() {                                                           \
    constexpr auto hash = hash::get_hash(data); \
    return hash;                                                    \
  }()

#define HASH(data) hash::get_hash(data)