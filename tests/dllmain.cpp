#include "common.h"
#include "syscalls/parser/ae86.hpp"
#include "syscalls/syscalls.h"

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
	if (reason != 1)
		return true;

	g_syscall_parser.parse();

	c_vector<int> vec{};
	vec.emplace_back(10);
	vec.emplace_back(20);
	vec.emplace_back(30);
	vec.emplace_back(40);
	vec.emplace_back(50);

	for (auto& i : vec) {
		int num = i + 10;
		int b = 0;
	}
	return false;
}