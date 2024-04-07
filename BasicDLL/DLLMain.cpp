#include <Windows.h>
#include <stdio.h>

#define LOG(fmt, ...) do { \
    const int MAX_BUFFER_SIZE = 1024; \
    char buf[MAX_BUFFER_SIZE]; \
    int written = snprintf(buf, sizeof(buf), "[Debug DLL] " fmt, ##__VA_ARGS__); \
    if (written > 0 && written < MAX_BUFFER_SIZE) { \
        OutputDebugStringA(buf); \
    } \
} while (0)

BOOL WINAPI DllMain( HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved ) {

	auto ModuleBase = ( UINT_PTR ) GetModuleHandle( NULL );
	CHAR ModulePath[ MAX_PATH ];
	DWORD length = GetModuleFileNameA( NULL, ModulePath, MAX_PATH );
	if ( length == 0 || length == MAX_PATH ) {
		strcpy_s( ModulePath, MAX_PATH, "Unknown" );
	}

	switch ( fdwReason ) {
	case DLL_PROCESS_ATTACH:
		LOG( "Entrypoint called in %s", ModulePath );
		LOG( "Module base: 0x%p", ( VOID* ) ModuleBase );
		LOG( "DLL base: 0x%p", ( VOID* ) hinstDLL );
		break;

	case DLL_THREAD_ATTACH:

		break;

	case DLL_THREAD_DETACH:

		break;

	case DLL_PROCESS_DETACH:

		if ( lpvReserved != nullptr ) {
			break;
		}

		break;
	}
	return TRUE;
}