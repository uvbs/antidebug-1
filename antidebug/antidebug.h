#include "windows.h"
#include "tlhelp32.h"
#include "stdio.h"
#include "string.h"

// OllyDbg Alias
char gOllyDbg[][32] = {
	"OllyDbg",
	"OllyICE",
	"FlyODBG",
	"VBoxTray",
	"VBoxService",
	"VmWareTray",
	"VmWareService",
	"VmWareUser",
	""
};
char gOllyDbgDll[][32] = {
	"DBGHELP",
	"LOADDLL",
	""
};

DWORD GetProcessIDByNameA(PCHAR ProcessName, PPROCESSENTRY32 PProEntry) {
	DWORD pid = 0;
	HANDLE hProcessShot = 0;
	PROCESSENTRY32 pe32 = { 0 };
	pe32.dwSize = sizeof(pe32);
	hProcessShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessShot == INVALID_HANDLE_VALUE) {
		return FALSE;
	}
	if (Process32First(hProcessShot, &pe32)) {
		do {
			int i = 0;
			//	printf("\t%04d:%s\n",pe32.th32ProcessID,pe32.szExeFile);
			if (strcmp(pe32.szExeFile, ProcessName)==0) {
				pid = pe32.th32ProcessID;
				if (PProEntry != 0)
					memcpy(PProEntry, &pe32, sizeof(pe32));
				break;
			}
		} while (Process32Next(hProcessShot, &pe32));
	}
	CloseHandle(hProcessShot);
	return pid;
}