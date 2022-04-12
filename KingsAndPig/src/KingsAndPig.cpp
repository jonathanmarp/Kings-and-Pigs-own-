// Include header <Main>
#include "../include/Main.h"

// Include header <thirdparty>
#include "box2d/box2d.h"

// If release mode
#ifdef RELEASE_MODE
// Include header <Win32 API>
#include <Windows.h>
#endif

int main(int argc, const char* argv[]) {
	// If release mode	
	#ifdef RELEASE_MODE
		// Free console
		FreeConsole();
	#endif

	// Setup box 2d
	B2_NOT_USED(argc);
	B2_NOT_USED(argv);
	
	// Declare main
	Main main = Main();
	{
		(void)argc;
		(void)argc;
	}
	return 0;
}