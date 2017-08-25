//FD_PEB
BOOL BeingDebugged(){
	__asm{
		xor ecx,ecx
		mov ecx,fs:[ecx+0x30]
		movzx eax,byte ptr[ecx+0x2]
	}
}

BOOL NtGlobalFlags(){	
	__asm{
		xor ecx,ecx
		mov ecx,fs:[ecx+0x30]
		mov eax,[ecx+0x68]
		and eax,0x70
	}
}
BOOL ProcessHeapForceFlags() {
	int r = 0;
	CHAR version = (CHAR)GetVersion();
	//for xp
	if (version == 5) {
		__asm {
				mov eax, fs:[0x30]
				mov eax, [eax + 0x18]
				mov eax, [eax + 0x10]
				mov r, eax
		}
	}
	else {
		__asm {
				mov eax, fs:[0x30]
				mov eax, [eax + 0x18]
				mov eax, [eax + 0x44]
				mov r, eax
		}
	}
	return r;
}
BOOL ProcessHeapFlags() {
	int r = 0;
	CHAR version = (CHAR)GetVersion();
	//for xp
	if (version == 5) {
		__asm {
			mov eax, fs:[0x30]
				mov eax, [eax + 0x18]
				mov eax, [eax + 0x0c]
				mov r, eax
		}
	}
	else {
		__asm {
			mov eax, fs:[0x30]
				mov eax, [eax + 0x18]
				mov eax, [eax + 0x40]
				mov r, eax
		}
	}
	return r;
}
void FD_PEB(){
	int r;
	printf("FD_PEB:\n");
	r = BeingDebugged();
	if(r)
		printf("\t[+]BeingDebugged \t= %08X\n",r);
	else
		printf("\t[-]BeingDebugged \t= %08X\n",r);
	r = NtGlobalFlags();
	if (r)
		printf("\t[+]NtGlobalFlags \t= %08X\n", r);
	else
		printf("\t[-]NtGlobalFlags \t= %08X\n", r);
	r = ProcessHeapFlags();
	if (r!=2)
		printf("\t[+]HeapFlags \t\t= %08X\n", r);
	else
		printf("\t[-]HeapFlags \t\t= %08X\n", r);
	r = ProcessHeapForceFlags();
	if (r!=0)
		printf("\t[+]HeapForceFlags \t= %08X\n", r);
	else
		printf("\t[-]HeapForceFlags \t= %08X\n", r);
}