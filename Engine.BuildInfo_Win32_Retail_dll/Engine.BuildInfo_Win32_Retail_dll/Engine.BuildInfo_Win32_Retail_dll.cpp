#include <windows.h>
#include <stdio.h>
HINSTANCE mHinst = 0, mHinstDLL = 0;
UINT_PTR mProcs[1] = {0};


LPCSTR mImportNames[] = {"getBuildInfo"};
BOOL WINAPI DllMain( HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved ) {
	mHinst = hinstDLL;
	if ( fdwReason == DLL_PROCESS_ATTACH ) {
		mHinstDLL = LoadLibrary( "ori_.\Engine.BuildInfo_Win32_Retail_dll.dll" );
		if ( !mHinstDLL )
			return ( FALSE );
		for ( int i = 0; i < 1; i++ )
			mProcs[ i ] = (UINT_PTR)GetProcAddress( mHinstDLL, mImportNames[ i ] );
	} else if ( fdwReason == DLL_PROCESS_DETACH ) {
		FreeLibrary( mHinstDLL );
	}
	return ( TRUE );
}

extern "C" __declspec(naked) void __stdcall getBuildInfo_wrapper(){__asm{jmp mProcs[0*4]}}
