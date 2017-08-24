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

BOOL FD_API_CloseHandle(){
	__try{
		CloseHandle((HANDLE)0x66666666);
		return FALSE;
	}__except(1){
		return TRUE;
	}
}

BOOL FD_API_DeleteFiber(){
	__try {	
		DeleteFiber((LPVOID)0x66666666);
		
	}__except (1) {

	}
	return GetLastError() != 0x57;
}
void FD_API(){
	int r = 0;
	printf("FD_API:\n");
	r = FD_API_CheckRemoteDebuggerPresent();
	if(r)
		printf("\t[+]CheckRemoteDebuggerPresent() = %08X\n",r);
	else
		printf("\t[-]CheckRemoteDebuggerPresent() = %08X\n",r);
	if(FD_API_CloseHandle())
		printf("\t[+]CloseHandle - except\n");
	else
		printf("\t[-]CloseHandle - not except\n");
	//if(FD_API_DeleteFiber())
	//	printf("\t[+]DeleteFiber - GetLastError != 0x57\n");
	//else
	//	printf("\t[-]DeleteFiber - GetLastError == 0x57\n");	
}