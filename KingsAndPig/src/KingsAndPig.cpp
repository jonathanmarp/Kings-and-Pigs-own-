// Include header <Main>
#include "../include/Main.h"

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
	
	// Declare main
	Main main = Main();
	{
		(void)argc;
		(void)argc;
	}
	return 0;
}