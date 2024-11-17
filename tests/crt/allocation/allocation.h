#pragma once
#include <Windows.h>
#include <cstddef>
#include <cstdint>

// indexes that i can't find dynamically due to allocation used before parser...
enum syscall_index_t {
	NtAllocateVirtualMemory = 0x18,
	NtQueryVirtualMemory = 0x23,
	NtFreeVirtualMemory = 0x1E,
};

namespace allocation {
	void* malloc(std::size_t);
	void free(void*);
}