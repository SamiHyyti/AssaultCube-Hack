#pragma once
#include "pch.h"

bool Hook(void* toHook, void* ourFunct, int len);
bool Detour32(BYTE* src, BYTE* dst, const uintptr_t len);
BYTE* TrampHook32(BYTE* src, BYTE* dst, const uintptr_t len);