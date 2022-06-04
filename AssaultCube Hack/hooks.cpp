#include "pch.h"
#include "hooks.h"

bool Hook(void* toHook, void* ourFunct, int len)
{
    if (len < 5) return false;

    DWORD curProtection;
    VirtualProtect(toHook, len, PAGE_EXECUTE_READWRITE, &curProtection);

    memset(toHook, 0x90, len); //nop all 5 bytes at toHook

    DWORD relativeAddress = ((DWORD)ourFunct - (DWORD)toHook) - 5;

    *(BYTE*)toHook = 0XE9; //place jmp
    *(DWORD*)((DWORD)toHook + 1) = relativeAddress;

    DWORD temp;
    VirtualProtect(toHook, len, curProtection, &temp);

    return true;
}

bool Detour32(BYTE* src, BYTE* dst, const uintptr_t len)
{
    if (len < 5) return false;

    DWORD curProtection;
    VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &curProtection);

    uintptr_t relativeAddress = dst - src - 5;

    *src = 0xE9; //place jmp

    *(uintptr_t*)(src + 1) = relativeAddress;

    VirtualProtect(src, len, curProtection, &curProtection);
    return true;
}

BYTE* TrampHook32(BYTE* src, BYTE* dst, const uintptr_t len)
{
    if (len < 5) return 0;

    //create gateway
    BYTE* gateway = (BYTE*)VirtualAlloc(0, len, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

    //write stolen bytes to gateway
    memcpy_s(gateway, len, src, len);

    //get gateway to destination address
    uintptr_t gatewayRelativeAdd = src - gateway - 5;

    //add jmp to end of gateway
    *(gateway + len) = 0xE9;

    //write address of gateway to jmp
    *(uintptr_t*)((uintptr_t)gateway + len + 1) = gatewayRelativeAdd;

    //perform detour
    Detour32(src, dst, len);

    return gateway;
}