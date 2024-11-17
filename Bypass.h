#pragma once
#include "get.h"
//lol
void bypass()
{


 uint64_t bypassbase = get::client + 0x8471660;
float* bypass = reinterpret_cast<float*>(bypassbase + 9);
*bypass = 9;


}
