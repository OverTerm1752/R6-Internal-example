
#include <intrin.h>
#include <cstdint>
#include <libloaderapi.h>
#include "hexarys.h"
#include <windows.h>
#include <xmmintrin.h>

#include <unordered_map>
#include <mutex>
#include <iostream>
#include "vmmath.h"




namespace get
{

	const auto client = reinterpret_cast<std::uintptr_t>(GetModuleHandle("RainbowSix.exe"));
	auto retaddr = client;
	uint64_t GetPEBAddress() {
		return __readgsqword(0x60);
	}





}




