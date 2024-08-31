#pragma once
#include <Windows.h>
#include <string>


#include <vector>

class c_driver
{
private:
    HANDLE process_handle;

public:
    auto initialize(const int process_id) -> bool
    {
        process_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, process_id);
        return process_handle != nullptr;
    }

    auto get_module_base(const std::wstring& module_name) -> const std::uintptr_t
    {
        HMODULE hModule = GetModuleHandle(module_name.c_str());
        if (hModule == nullptr)
            return 0;
        return reinterpret_cast<std::uintptr_t>(hModule);
    }

    auto read(const std::uintptr_t address, void* buffer, const std::size_t size) -> bool
    {
        return ReadProcessMemory(process_handle, reinterpret_cast<LPCVOID>(address), buffer, size, nullptr);
    }

    template <typename t>
    auto read(const std::uintptr_t address) -> t
    {
        t response{};
        this->read(address, &response, sizeof(t));
        return response;
    }

    auto write(const std::uintptr_t address, void* buffer, const std::size_t size) -> bool
    {
        return WriteProcessMemory(process_handle, reinterpret_cast<LPVOID>(address), buffer, size, nullptr);
    }

    template <typename t>
    auto write(const std::uintptr_t address, t value) -> bool
    {
        return this->write(address, &value, sizeof(t));
    }

    auto unload() -> bool
    {
        return CloseHandle(process_handle);
    }
};

static c_driver* driver = new c_driver();
