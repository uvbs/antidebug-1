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
			CHAR temp[MAX_PATH] = { 0 };
			int i = 0;
			//	printf("\t%04d:%s\n",pe32.th32ProcessID,pe32.szExeFile);
			if (stricmp(pe32.szExeFile,ProcessName)==0) {
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

DWORD GetProcessInfoByID(DWORD PID, PPROCESSENTRY32 PProEntry) {
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
			CHAR temp[MAX_PATH] = { 0 };
			int i = 0;
			//	printf("\t%04d:%s\n",pe32.th32ProcessID,pe32.szExeFile);
			if (pe32.th32ProcessID == PID) {
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
DWORD __declspec(naked) KiFastSystemCallByIndex(DWORD index,...) {
	__asm {
		mov eax,[esp+4]
		mov edx,esp
		//sysenter
		__emit 0x0f
		__emit 0x34
	}
}

DWORD __declspec(naked) KiIntSystemCallByIndex(DWORD index, ...) {
	__asm {
		mov eax, [esp + 4]
		lea edx, [esp+8]
		int 0x2e
		retn
	}
}

DWORD __declspec(naked) KiFastSystemCallByName(PCHAR name, ...) {
	__asm {
		push 0x6c
		push 0x6c64746e
		push esp
		call GetModuleHandle
		add esp, 0x8
		push[esp + 4]
		push eax
		call GetProcAddress
		mov eax, [eax + 1]
		lea edx, [esp + 8]
		int 0x2e
		retn
	}
}
DWORD __declspec(naked) KiIntSystemCallByName(PCHAR name, ...) {
	__asm {
		push 0x6c
		push 0x6c64746e
		push esp
		call GetModuleHandle
		add esp, 0x8
		push[esp + 4]
		push eax
		call GetProcAddress
		mov eax, [eax + 1]
		mov edx, esp
		//sysenter
		__emit 0x0f
		__emit 0x34
	}
}


DWORD gCallDllFunEsp = 0;
DWORD gCallDllFunRet = 0;
DWORD gCallDllFunDll = 0;
DWORD gCallDllFunFun = 0;
DWORD __declspec(naked) CallDllFun(PCHAR dll,PCHAR proc,...) {
	__asm {
		pop [gCallDllFunRet]
		pop [gCallDllFunDll]
		pop [gCallDllFunFun]
		mov[gCallDllFunEsp], esp

		sub esp,0x8
		call LoadLibraryA
		push eax
		call GetProcAddress

		call eax

		mov esp,[gCallDllFunEsp]
		push [gCallDllFunFun]
		push [gCallDllFunDll]
		push [gCallDllFunRet]
		retn
	}
}