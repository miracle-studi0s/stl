#ifndef AE86_H_
#define AE86_H_

/*
	Made with LOVE by Soufiw & infirms
	07-06-23

	Modified by Miracle (made compatible with x64)
	21-10-2023
 */

#include <Windows.h>

#include "win.hpp"
#include "hash.hpp"

#include "../../hash_table.h"

#define PTR_64_(p) ((DWORD64)(ULONG_PTR)(p))
#define HADNLE_64_(p) ((DWORD64)(LONG_PTR)(p))
#define NtCurrentProcess() ((HANDLE)(LONG_PTR)-1)

namespace ae86 {
    win::_TEB64* nt_current_teb() noexcept;
    win::_PEB64* nt_current_peb() noexcept;

    const IMAGE_DOS_HEADER* get_image_dos_header(std::uintptr_t image);
    const IMAGE_NT_HEADERS* get_image_nt_headers(std::uintptr_t image);
    const IMAGE_DATA_DIRECTORY* get_image_data_directory(std::uintptr_t image,
        std::uint16_t directory);

    std::uintptr_t get_image(hash_t name_hash);

	class c_syscall_parser {
	public:
		c_syscall_parser();
		~c_syscall_parser();

		void parse();
		int get_index(hash_t hash) { return syscalls_[hash]; }
	private:
		int count_;
		c_hash_table<hash_t, int> syscalls_;
	};
}

inline ae86::c_syscall_parser g_syscall_parser{};

#endif  // AE86_H_