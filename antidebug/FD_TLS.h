void NTAPI _tls_callback1(PVOID DllHandle, DWORD dwReason, PVOID Reserved) {
	if (dwReason != 1)
		return;
//	BlockInput(TRUE);
	//MessageBoxA(0, "TLS Success!", "antidebug", 0);
}

#pragma comment(linker,"/INCLUDE:__tls_used")
#pragma data_seg(".CRT$XLB")
PIMAGE_TLS_CALLBACK _tls_callback[] = { _tls_callback1,0 };
#pragma data_seg()
