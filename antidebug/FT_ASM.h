BOOL FT_PUSHF_Asm(){
	__asm{
		push ss
		__emit 0x74
		__emit 0x03
		__emit 0x75
		__emit 0x01
		__emit 0xe8
		pop ss
		pushfd
        __emit 0x74
		__emit 0x03
		__emit 0x75
		__emit 0x01
		__emit 0xe8
		pop eax
		and eax,0x100
		jnz f
		xor eax,eax
		jmp r
		f:
		sub eax,eax
		inc eax
		r:
	}
}
BOOL TflagExcept() {
	__try {
		__asm {
			pushfd
				or dword ptr[esp], 0x100
				popfd
				nop
		}
		return TRUE;
	}
	__except (1) {
		return FALSE;
	}
}
void FT_PUSHF(){
	printf("FT_ASM:\n");
	if(FT_PUSHF_Asm())
		printf("\t[+]pushf trace\n");
	else
		printf("\t[-]pushf not trace\n");
	if (TflagExcept())
		printf("\t[+]Tflag \t- not except\n");
	else
		printf("\t[-]Tflag \t- except\n");
}