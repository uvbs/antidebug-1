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
#include "FT_PUSHF.h"
#include "FD_OD_Process.h"
#include "FD_SetDebugPrivilege.h"
//main
/*
;_CRT_SECURE_NO_DEPRECATE;_CRT_NONSTDC_NO_DEPRECATE
*/
void main(){
	BlockInput(FALSE);
	FD_SetDebugPrivilege();
//	FD_Except();
	FD_OD_Process();
	FT_PUSHF();
	FP_CHECKSUM();
	FT_TIME_Start();
	FD_PEB();
	FD_API();
	FD_OD_Window();
	AD_API();
	FT_TIME_End();
	system("pause");
	ExitProcess(0);
}