#include "antidebug.h"
//module
#include "FD_TLS.h"
#include "FD_PEB.h"
#include "FD_OD_Window.h"
#include "FD_API.h"
#include "FD_Except.h"
#include "FT_TIME.h"
#include "AD_API.h"
#include "FP_CHECKSUM.h"
#include "FT_ASM.h"
#include "FD_OD_Process.h"
#include "FD_SetDebugPrivilege.h"
//main
/*
;_CRT_SECURE_NO_DEPRECATE;_CRT_NONSTDC_NO_DEPRECATE
*/
void main() {
	DWORD a = 0 ;
	if ((CHAR)GetVersion() == 5) {
		KiFastSystemCallByIndex(0x9a, -1, 0x1f, &a, 4, 0);
		KiFastSystemCallByName("ZwQueryInformationProcess", -1, 0x1f, &a, 4, 0);
		KiIntSystemCallByIndex(0x9a, -1, 0x1f, &a, 4, 0);
		KiIntSystemCallByName("ZwQueryInformationProcess", -1, 0x1f, &a, 4, 0);
	}
	CallDllFun("ntdll", "ZwQueryInformationProcess", -1, 0x1f, &a, 4, 0);
	//CallDllFun("user32", "MessageBoxA", 0, "ok", "pk", 0);
	BlockInput(FALSE);
	FT_TIME_Start();
	FD_SetDebugPrivilege();
	FD_Except();
	FD_OD_Process();
	FT_PUSHF();
	FP_CHECKSUM();
	FD_PEB();
	FD_API();
	FD_OD_Window();
	AD_API();
	FT_TIME_End();
	system("pause");
	ExitProcess(0);
}