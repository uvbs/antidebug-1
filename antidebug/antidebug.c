#include "windows.h"
#include "tlhelp32.h"
#include "stdio.h"
#include "string.h"

#define true	1
#define false	0
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
//module
#include "FD_PEB.h"
#include "FD_OD_Window.h"
#include "FD_API.h"
#include "FD_INT.h"
#include "FT_TIME.h"
#include "FT_ICE.h"
#include "AD_OD_API.h"
#include "AD_NTAPI.h"
#include "FP_CHECKSUM.h"
#include "FT_PUSHF.h"
#include "FD_OD_Process.h"
//main
/*
;_CRT_SECURE_NO_DEPRECATE;_CRT_NONSTDC_NO_DEPRECATE
*/
void main(){
	FD_OD_Process();
	FT_PUSHF();
	FP_CHECKSUM();
	//find trace
	FT_ICE();
	//time start
	FT_TIME_Start();
	//find debugger
	FD_PEB();
	FD_API();
	FD_INT();
	FD_OD_Window();
	//find trace
	//attack debugger
	__asm{
		jmp n
		__emit 0x41
		__emit 0x44
		__emit 0x00
		n:
		nop
	}
	AD_NTAPI();
	AD_OD_API();
	__asm{
		nop
	}
	//time end
	FT_TIME_End();
	system("pause");
	ExitProcess(0);
}
