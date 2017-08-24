//FD_PEB
BOOL FD_PEB_BeingDebuggedFlag(){
	__asm{
		xor ecx,ecx
		mov ecx,fs:[ecx+0x30]
		movzx eax,byte ptr[ecx+0x2]
	}
}

BOOL FD_PEB_NtGlobalFlags(){	
	__asm{
		xor ecx,ecx
		mov ecx,fs:[ecx+0x30]
		mov eax,[ecx+0x68]
		and eax,0x70
	}
}
void FD_PEB(){
	int r;
	printf("FD_PEB:\n");
	r = IsDebuggerPresent();
	if(r)
		printf("\t[+]IsDebuggerPresent() \t= %08X\n",r);
	else
		printf("\t[-]IsDebuggerPresent() \t= %08X\n",r);
	r = FD_PEB_BeingDebuggedFlag();
	if(r)
		printf("\t[+]BeingDebuggedFlag \t= %08X\n",r);
	else
		printf("\t[-]BeingDebuggedFlag \t= %08X\n",r);
	r = FD_PEB_NtGlobalFlags();
	if(r)
		printf("\t[+]NtGlobalFlags \t= %08X\n",r);
	else
		printf("\t[-]NtGlobalFlags \t= %08X\n",r);
}