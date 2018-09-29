#include "kernel.h"
#include <circle/startup.h>

int main(void)
{
	CKernel Kernel;
	if (!Kernel.Initialize ())
	{
		halt ();
		return EXIT_HALT;
	}
	
	CStdlibApp::TShutdownMode ShutdownMode = Kernel.Run ();

	Kernel.Cleanup ();

	switch (ShutdownMode)
	{
	case CStdlibApp::ShutdownReboot:
		reboot ();
		return EXIT_REBOOT;

	case CStdlibApp::ShutdownHalt:
	default:
		halt ();
		return EXIT_HALT;
	}
}
