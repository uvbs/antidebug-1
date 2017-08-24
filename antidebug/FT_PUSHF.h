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
void FT_PUSHF(){
	printf("FT_PUSHF:\n");
	if(FT_PUSHF_Asm())
		printf("\t[+]pushf trace\n");
	else
		printf("\t[-]pushf not trace\n");
}