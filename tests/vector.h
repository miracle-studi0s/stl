#pragma once
#include "crt/allocation/allocation.h"
#include <memory>

template<typename T>
class c_vector {
private:
	using iterator = T*;

	size_t size{};
	size_t capacity{};

	T* data{nullptr};

	void realloc(size_t new_capacity) {
		if (data == nullptr) {
			data = reinterpret_cast< T* >( allocation::malloc(sizeof(T) * new_capacity) );
			capacity = new_capacity;
			return;
		}

		T* new_data = reinterpret_cast< T* >( allocation::malloc(sizeof(T) * new_capacity) );
		if (new_capacity < size)
			size = new_capacity;

		for (size_t i = 0; i < size; ++i)
			std::construct_at(&new_data[i], std::forward<T>(data[i]));

		for (size_t i = 0; i < size; ++i)
			data[i].~T();

		allocation::free(data);
		data = new_data;
		capacity = new_capacity;
	}
public:
	c_vector() {
		realloc(2);
	}

	~c_vector() {
		clear();
		allocation::free(data);
	}

	c_vector(const c_vector& other) {
		size = other.size;
		realloc(size);
		for (size_t i = 0; i < size; ++i)
			std::construct_at(&data[i], other.data[i]);
	}

	c_vector(c_vector&& other) noexcept {
		capacity = other.capacity;
		size = other.size;
		data = other.data;

		other.capacity = 0;
		other.size = 0;
		other.data = nullptr;
	}

	c_vector& operator=(c_vector&& other) noexcept {
		capacity = other.capacity;
		size = other.size;
		data = other.data;

		other.capacity = 0;
		other.size = 0;
		other.data = nullptr;

		return *this;
	}

	c_vector& operator=(const c_vector& other) {
		size = other.size;
		realloc(size);
		for (size_t i = 0; i < size; ++i)
			std::construct_at(&data[i], other.data[i]);

		return *this;
	}

	void clear() {
		for (size_t i = 0; i < size; ++i)
			data[i].~T();

		size = 0;
	}

	void reserve(size_t capacity) {
		realloc(capacity);
	}

	void clear_memory() {
		clear();
		realloc(2);
	}

	void push_back(const T& value) {
		if (size >= capacity)
			realloc(capacity + capacity / 2);

		data[size] = value;
		++size;
	}

	template<typename ...Args>
	void emplace_back(Args&& ...args) {
		if (size >= capacity)
			realloc(capacity + capacity / 2);

		std::construct_at(&data[size], std::forward<Args>(args)...);
		++size;
	}

	void pop_back() {
		if (size) {
			--size;
			data[size].~T();
		}
	}

	iterator begin() {
		return data;
	}

	iterator end() {
		return data + size;
	}

	bool empty() {
		return size == 0;
	}

	size_t vec_size() {
		return size;
	}

	size_t vec_capacity() {
		return capacity;
	}

	T& operator[](size_t index) {
		return data[index];
	}

	const T& operator[](size_t index) const {
		return data[index];
	}
};