#pragma once
#include "get.h"
#include "Driver.h"

void bypass()
{

	// Ubisoft's anti-cheat bypass (credits to OVERHEAD)

uint64_t bypassbase = get::client + 0x8A1A4B0;
float* bypass = reinterpret_cast<float*>(bypassbase + 9);
*bypass = 9;


}

