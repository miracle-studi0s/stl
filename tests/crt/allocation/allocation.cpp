#include "allocation.h"
#include "../../syscalls/parser/ae86.hpp"
#include "../../syscalls/syscalls.h"
#include <cassert>

void* allocation::malloc(std::size_t size) {
	PVOID chunk{nullptr};
	auto status = Syscall<NTSTATUS>(NtAllocateVirtualMemory, NtCurrentProcess(), 
		&chunk, 0, reinterpret_cast<PULONG>(&size), MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	assert(status == 0);

	return chunk;
}

void allocation::free(void* address) {
	MEMORY_BASIC_INFORMATION mbi{};
	SIZE_T mbi_size = static_cast<SIZE_T>(sizeof(mbi));
	PSIZE_T out{ NULL };

	auto status = Syscall<NTSTATUS>(NtQueryVirtualMemory, NtCurrentProcess(), 
		reinterpret_cast<PVOID>(address), MemoryBasicInformation, &mbi, mbi_size, out);

	assert(status == 0);

	status = Syscall<NTSTATUS>(NtFreeVirtualMemory, NtCurrentProcess(), 
		&address, reinterpret_cast<PULONG>(&mbi.RegionSize), MEM_RELEASE);

	assert(status == 0);
}