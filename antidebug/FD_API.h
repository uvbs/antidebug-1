BOOL FD_API_CheckRemoteDebuggerPresent(){
	typedef BOOL (__stdcall* pF)(HANDLE,PDWORD);
	DWORD r = 0;
	HANDLE h = LoadLibraryA("kernel32");
	if (h == 0)
		return FALSE;
	pF f = (pF)GetProcAddress(h, "CheckRemoteDebuggerPresent");
	if (f == 0)
		return FALSE;
		f(GetCurrentProcess(),&r);
	return r;
}

void FD_API(){
	int r = 0;
	printf("FD_API:\n");
	r = FD_API_CheckRemoteDebuggerPresent();
	if(r)
		printf("\t[+]CheckRemoteDebuggerPresent() = %08X\n",r);
	else
		printf("\t[-]CheckRemoteDebuggerPresent() = %08X\n",r);
	r = IsDebuggerPresent();
	if (r)
		printf("\t[+]IsDebuggerPresent() \t\t= %08X\n", r);
	else
		printf("\t[-]IsDebuggerPresent() \t\t= %08X\n", r);
}