#if WIN32 && !NDEBUG
    #define WIN32_LEAN_AND_MEAN
    #include <stdio.h>
    #include <windows.h>

    extern "C" int WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
    {

        switch (fdwReason)
        {
        case DLL_PROCESS_ATTACH:
            AllocConsole();
            freopen("CONOUT$", "w", stdout);
            break;
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
        }
        return TRUE;
    }
#endif
