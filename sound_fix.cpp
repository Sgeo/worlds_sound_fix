#define CINTERFACE
#include <windows.h>
#include <detours.h>

//#pragma comment(linker, "/export:MyDetourFinishHelperProcess,@1,NONAME")

// static int (WINAPI * TrueEntryPoint)(VOID) = NULL;


BOOL (STDMETHODCALLTYPE *RealPlaySoundA)(
   LPCSTR pszSound,
   HMODULE hmod,
   DWORD   fdwSound
) = PlaySoundA;

BOOL MinePlaySoundA(LPCSTR pszSound, HMODULE hmod, DWORD fdwSound) {
    if(fdwSound & SND_PURGE) {
        fdwSound &= ~SND_PURGE;
        fdwSound |= SND_ASYNC;
        return RealPlaySoundA(NULL, NULL, fdwSound);
    } else {
        return RealPlaySoundA(pszSound, hmod, fdwSound);
    }
}

// int WINAPI MyEntryPoint(VOID) {
//     LONG error;
//     DetourTransactionBegin();
//     DetourUpdateThread(GetCurrentThread());
//     RealPlaySound = PlaySound;
//     DetourAttach(&(PVOID&)RealPlaySound, MinePlaySound);
//     error = DetourTransactionCommit();
//     return TrueEntryPoint();
// }

BOOL WINAPI DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID reserved)
{
    LONG error;
    (void)hinst;
    (void)reserved;

    if (DetourIsHelperProcess()) {
        return TRUE;
    }

    if (dwReason == DLL_PROCESS_ATTACH) {
        DetourRestoreAfterWith();

        // NB: DllMain can't call LoadLibrary, so we hook the app entry point.
        // TrueEntryPoint = (int (WINAPI *)(VOID))DetourGetEntryPoint(NULL);

        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach(&(PVOID&)RealPlaySoundA, MinePlaySoundA);
        error = DetourTransactionCommit();
    }
    else if (dwReason == DLL_PROCESS_DETACH) {
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        if (RealPlaySoundA != NULL) {
            DetourDetach(&(PVOID&)RealPlaySoundA, (PVOID)MinePlaySoundA);
        }
        // DetourDetach(&(PVOID&)TrueEntryPoint, MyEntryPoint);
        error = DetourTransactionCommit();
    }
    return TRUE;
}