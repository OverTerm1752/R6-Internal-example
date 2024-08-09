
#pragma once
#include "get.h"



namespace offsets
{




	uint64_t GetGameManager()
	{
		uint64_t qword_8AB7C90 = *(uint64_t*)(get::client + 0x8B010A0);
		uint64_t qword_8AB7C91 = (qword_8AB7C90 + (get::retaddr & 0xFFFFFFFE00000000ui64) + 0x6339DDD026A7FA8Di64);




		return qword_8AB7C91;
	}



}
