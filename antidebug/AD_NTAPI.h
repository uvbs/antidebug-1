void AD_NTAPI_ZwSetInformationThread(){
	typedef DWORD (__stdcall* pF)(HANDLE, DWORD, DWORD, DWORD);
	HANDLE h = LoadLibraryA("ntdll");
	if (h == 0)
		return;
	pF f = (pF)GetProcAddress(h, "ZwSetInformationThread");
	if (f == 0)
		return;
	f(GetCurrentThread(),17,0,0);//ThreadHideFromDebugger 17
}
void AD_NTAPI(){
	printf("AD_NTAPI:\n");
	AD_NTAPI_ZwSetInformationThread();
	printf("\t[*]ZwSetInformationThread - ThreadHideFromDebugger\n");
}