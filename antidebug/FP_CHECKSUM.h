DWORD FP_CHECKSUM_ROL(){
	__asm{
		sub ebx,ebx
		mov ebx,fs:[ebx+0x30]
		mov ebx,[ebx+0x08] 
		mov eax,[ebx+0x3c]
		add eax,ebx
		mov eax,[eax+0x28]
		add eax,ebx
		and eax,0xFFFFF000
		mov esi,eax
		sub eax,eax
		sub edx,edx
		mov ecx,0x1000
		l:
		lodsb
		rol eax,0x03
		add edx,eax
		loop l
		mov eax,edx
		mov edx,[ebx+0x38]
		cmp eax,edx
		je a
		jne r
		a:
		sub eax,eax
		jmp r
		r:	
	}
}
void FP_CHECKSUM(){
	DWORD sum = 0;
	printf("FP_CHECKSUM:\n");
	sum = FP_CHECKSUM_ROL();
	if(sum != 0)
		printf("\t[+]rol = %08X\n",sum);
	else
		printf("\t[-]rol = %08X\n",sum);
}