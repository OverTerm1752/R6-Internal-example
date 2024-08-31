#pragma once
#include "get.h"
#include "Driver.h"

bool bypass_ext()
{

    uint64_t bypassbase = driver->get_module_base() + 0x8A1A4B0;
    return driver->write<uint8_t>(bypassbase + 9, 'G');
}