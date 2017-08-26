BOOL IsExplorerProcessChild(PCHAR ParentProcess) {
	PROCESSENTRY32 pe = { 0 };
	CHAR	ExeFileName[MAX_PATH] = { 0 };
	PCHAR	ExeNamePart = 0;
	int		i = 0;
	GetModuleFileNameA(GetModuleHandle(0), ExeFileName, MAX_PATH);
	for (i = 0; ExeFileName[i] != 0;i++) {
		if (ExeFileName[i] == '\\') {
			ExeNamePart = &ExeFileName[i + 1];
		}
	}
	GetProcessIDByNameA(ExeNamePart, &pe);
	GetProcessInfoByID(pe.th32ParentProcessID, &pe);
	strcpy(ParentProcess, pe.szExeFile);
	if (stricmp(pe.szExeFile, "explorer.exe") == 0 || stricmp(pe.szExeFile, "cmd.exe") == 0)
		return FALSE;
	else
		return TRUE;
}
BOOL HardBreak() {
	CONTEXT context = { 0 };
	context.ContextFlags = CONTEXT_DEBUG_REGISTERS;
	GetThreadContext(GetCurrentThread(), &context);
	if (context.Dr0 != 0 || context.Dr1 != 0 || context.Dr2 != 0 || context.Dr3 != 0 || context.Dr6 != 0 || context.Dr7 != 0)
		return TRUE;
	else
		return FALSE;
}
void FD_API(){
	typedef DWORD(WINAPI* pF)(HANDLE,DWORD,PDWORD,DWORD,DWORD);
	BOOL	r = 0;
	DWORD	Debug = 0;
	pF		NtQueryInformationProcess	=	0;

	CHAR	parentProcess[MAX_PATH] = { 0 };
	printf("FD_API:\n");

	r = IsDebuggerPresent();
	if (r)
		printf("\t[+]IsDebuggerPresent() \t\t= %08X\n", r);
	else
		printf("\t[-]IsDebuggerPresent() \t\t= %08X\n", r);
	
	r = CheckRemoteDebuggerPresent(GetCurrentProcess(),&Debug);
	if(Debug)
		printf("\t[+]CheckRemoteDebuggerPresent() = %08X\n", Debug);
	else
		printf("\t[-]CheckRemoteDebuggerPresent() = %08X\n", Debug);

	NtQueryInformationProcess = (pF)GetProcAddress(LoadLibrary("ntdll"), "NtQueryInformationProcess");

	r = NtQueryInformationProcess(GetCurrentProcess(), 0x07, &Debug, sizeof(Debug), 0);
	if (Debug)
		printf("\t[+]NtQueryInformationProcess() - ProcessDebugPort \t\t= %08X\n", Debug);
	else
		printf("\t[-]NtQueryInformationProcess() - ProcessDebugPort \t\t= %08X\n", Debug);
	
	
	r = NtQueryInformationProcess(GetCurrentProcess(), 0x1e, &Debug, sizeof(Debug), 0);
	if (Debug)
		printf("\t[+]NtQueryInformationProcess() - ProcessDebugObjectHandle \t= %08X\n", Debug);
	else
		printf("\t[-]NtQueryInformationProcess() - ProcessDebugObjectHandle \t= %08X\n", Debug);
	
	
	r = NtQueryInformationProcess(GetCurrentProcess(), 0x1f, &Debug, sizeof(Debug), 0);
	if (Debug==0)
		printf("\t[+]NtQueryInformationProcess() - ProcessDebugFlags \t\t= %08X\n", Debug);
	else
		printf("\t[-]NtQueryInformationProcess() - ProcessDebugFlags \t\t= %08X\n", Debug);

	if (IsExplorerProcessChild(parentProcess))
		printf("\t[+]ParentProcessName = %s\n", parentProcess);
	else
		printf("\t[-]ParentProcessName = %s\n", parentProcess);

	STARTUPINFOA sinfo = { 0 };
	GetStartupInfoA(&sinfo);
	if (sinfo.dwX != 0 || sinfo.dwY != 0 || sinfo.dwXSize != 0 || sinfo.dwYSize != 0 || sinfo.dwXCountChars != 0 || sinfo.dwYCountChars != 0 || sinfo.dwFillAttribute != 0)
		printf("\t[+]GetStartupInfo\n");
	else
		printf("\t[-]GetStartupInfo\n");

	if(HardBreak())
		printf("\t[+]HardBreak\n");
	else
		printf("\t[-]HardBreak\n");
}