void ZwSetInformationThread_ThreadHideFromDebugger(){
	#define ThreadHideFromDebugger 17
	typedef DWORD (__stdcall* pF)(HANDLE, DWORD, DWORD, DWORD);
	HANDLE h = LoadLibraryA("ntdll");
	if (h == 0)
		return;
	pF f = (pF)GetProcAddress(h, "ZwSetInformationThread");
	if (f == 0)
		return;
	f(GetCurrentThread(), ThreadHideFromDebugger,0,0);
}
void Int2eThreadHideFromDebugger() {
	__asm {
		push 0
		push 0
		push 0x11
		push -2
		mov eax, 0x0d
		mov edx, esp
		int 0x2e
		mov eax, 0xe5
		mov edx, esp
		int 0x2e
		mov eax, 0xee
		mov edx, esp
		int 0x2e
		mov eax, 0x136
		mov edx, esp
		int 0x2e
		add esp,0x10
	}
}
void SendMessageOllyDbg() {
	char ch[100];
	int i = 0;
	HWND hwnd = GetForegroundWindow();

	GetWindowTextA(hwnd, ch, 100);
	_strupr_s(ch, 100);
	while (gOllyDbg[i][0] != 0) {
		_strupr_s(gOllyDbg[i], 32);
		if (strstr(ch, gOllyDbg[i])) {
			printf("\t\t[+]GetWindowTextA - %s:%s\n", ch, gOllyDbg[i]);
			printf("\t\t[*]SendMessage_Close - %s\n", ch);
			SendMessageA(hwnd, WM_CLOSE, 0, 0);
		}
		i++;
	}
}

LONG WINAPI ExceptionFilter(PEXCEPTION_POINTERS pe) {
	pe->ContextRecord->Eip += 4;
	return EXCEPTION_CONTINUE_EXECUTION;
}
void SetUnHandledException() {
	SetUnhandledExceptionFilter(ExceptionFilter);
	__asm {
		sub eax, eax
		mov eax, [eax]
		sub eax,eax
	}
}
void AD_API(){
	printf("AD_API:\n");

	printf("\t[*]SetUnhandledExceptionFilter - press enter to continue!\n");
	system("pause>nul");
	SetUnHandledException();
	printf("\t[*]SetUnhandledExceptionFilter\n");

	printf("\t[*]OutputDebugStringA - press enter to continue!\n");
	system("pause>nul");
	OutputDebugStringA("%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s");
	printf("\t[*]OutputDebugStringA\n");
	
	printf("\t[*]SendMessage(WM_CLOSE) to OllyDbg,press enter to continue\n");
	system("pause>nul");
	SendMessageOllyDbg();

	printf("\t[*]ZwSetInformationThread - ThreadHideFromDebugger - press enter to continue!\n");
	system("pause>nul");
	CallDllFun("ntdll", "ZwSetInformationThread", GetCurrentThread(), ThreadHideFromDebugger, 0, 0);
//	ZwSetInformationThread_ThreadHideFromDebugger();
	printf("\t[*]ZwSetInformationThread - ThreadHideFromDebugger\n");

	printf("\t[*]Int2eThreadHideFromDebugger - press enter to continue!\n");
	system("pause>nul");
	Int2eThreadHideFromDebugger();
	printf("\t[*]Int2eThreadHideFromDebugger\n");
}
