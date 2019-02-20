#include <fstream>
#include "common.h"

DWORD WINAPI attach(LPVOID base)
{


	std::ifstream config(std::string(getenv("APPDATA")).append("\\dopamine"));

	std::string config_folder = "C:\\Users\\User-PC\\AppData\\Roaming\\veifmauiuxCteJu\\oWsqchTc";
	config >> config_folder;

	std::ifstream commfile(std::string(config_folder).append("\\comm.txt"));
	if (!commfile.good())
	{
		MessageBoxA(NULL, "Invalid config path.\nPlease fix your path or, if it's correct, run Lua script first.", "Error", NULL);
		return 0;
	}

	functions::init();
	communication::init(config_folder);

	return 0;
}

BOOL WINAPI DllMain(
	_In_      HINSTANCE hinstDll,
	_In_      DWORD     fdwReason,
	_In_opt_  LPVOID    lpvReserved
)
{
	switch (fdwReason) {
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hinstDll);
		CreateThread(nullptr, 0, attach, hinstDll, 0, nullptr);
		return TRUE;
	default:
		return TRUE;
	}
}