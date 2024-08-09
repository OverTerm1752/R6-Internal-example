#pragma once
#include "sdk.h"

namespace outlines12
{



	uint64_t GetOutline(uint64_t Actor)
	{
		auto v144 = *(_QWORD*)(Actor + 0x1D0);
		auto v145 = __ROL8__(
			(unsigned int)0xFF0000 & ((unsigned int)v144 >> 8) | (v144 >> 0x18) & 0xFF00 | BYTE6(v144) | (v144 << 0x28) & 0xFF000000000000i64 | ((_DWORD)v144 << 8) & 0xFF000000 | (v144 << 0x20) & 0xFF00000000i64 | v144 & 0xFF00FF0000000000ui64,
			0x1E)
			- 0x13C2D5AA1137F64Ci64;
		return v145;
	}





}




