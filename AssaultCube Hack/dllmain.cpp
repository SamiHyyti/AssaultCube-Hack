// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "offsets.h"
#include "hooks.h"

typedef BOOL(__stdcall* twglSwapBuffers)(HDC hDc);

uintptr_t moduleBase = (uintptr_t)GetModuleHandle(L"ac_client.exe");
twglSwapBuffers owglSwapBuffers;
bool bHealth = false, bAmmo = false, bRecoil = false, bRapidFire = false;;
DWORD jmpBackAddress;

void __declspec(naked) noRecoil() {
    __asm {
        ret 8
        and esp, -8
        jmp[jmpBackAddress]
    }
}
//run cheats in glSwapbufferHook in stead of while loop
BOOL __stdcall hkwglSwapbuffers(HDC hDc)
{

    if (GetAsyncKeyState(VK_END) & 1)
    {
        //break;
    }
    if (GetAsyncKeyState(VK_NUMPAD1) & 1)
    {
        bHealth = !bHealth;
    }
    if (GetAsyncKeyState(VK_NUMPAD2) & 1)
    {
        bAmmo = !bAmmo;
    }
    if (GetAsyncKeyState(VK_NUMPAD3) & 1)
    {
        bRecoil = !bRecoil;
    }
    if (GetAsyncKeyState(VK_NUMPAD5) & 1)
    {
        bRapidFire = !bRapidFire;
    }
    LocalPlayer* localPlayer = *(LocalPlayer**)(moduleBase + 0x10F4F4);

    if (localPlayer)
    {
        if (bHealth)
        {
            localPlayer->health = 666;
        }
        if (bAmmo)
        {
            localPlayer->curWeapon->wpnstatPtr->ammo = 69;
            localPlayer->curWeapon->wpnstatPtr->magazine = 69;
            localPlayer->grenadeAmmo = 69;
        }
        if (bRecoil)
        {
            int hookLen = 6;
            DWORD hookAdd = 0x462020;
            jmpBackAddress = hookAdd + hookLen;

            Hook((void*)hookAdd, noRecoil, hookLen);
        }
        if (bRapidFire)
        {
            localPlayer->curWeapon->wpnstatPtr->cooldown = 0;
        }
    }

    return owglSwapBuffers(hDc);
}



DWORD WINAPI HackThread(HMODULE hModule) {
    //get module base
    

    owglSwapBuffers = (twglSwapBuffers)GetProcAddress(GetModuleHandle(L"opengl32.dll"), "wglSwapBuffers");
    owglSwapBuffers = (twglSwapBuffers)TrampHook32((BYTE*)owglSwapBuffers, (BYTE*)hkwglSwapbuffers, 5);


    //hack loop
    /*
    while (true)
    {
        if (GetAsyncKeyState(VK_END) & 1)
        {
            break;
        }
        if (GetAsyncKeyState(VK_NUMPAD1) & 1)
        {
            bHealth = !bHealth;
        }
        if (GetAsyncKeyState(VK_NUMPAD2) & 1)
        {
            bAmmo = !bAmmo;
        }
        if (GetAsyncKeyState(VK_NUMPAD3) & 1)
        {
            bRecoil = !bRecoil;
        }
        LocalPlayer* localPlayer = *(LocalPlayer**)(moduleBase + 0x10F4F4);

        if (localPlayer)
        {
            if (bHealth)
            {
                localPlayer->health = 666;
            }
            if (bAmmo)
            {
                localPlayer->curWeapon->wpnstatPtr->ammo = 69;
                localPlayer->curWeapon->wpnstatPtr->magazine = 69;
                localPlayer->grenadeAmmo = 69;
            }
            if (bRecoil)
            {
                int hookLen = 6;
                DWORD hookAdd = 0x462020;
                jmpBackAddress = hookAdd + hookLen;

                Hook((void*)hookAdd, noRecoil, hookLen);
                //localPlayer->health = 666;
            }
            Sleep(5);
        }
    }
    */
    
    
    //cleanup
    //FreeLibraryAndExitThread(hModule, 0);
    return 0;
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

