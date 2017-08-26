BOOL int1(){
	__try{
		__asm{
			__emit 0xF1
		}
		return TRUE;
	}__except(1){
		return FALSE;
	}
}
BOOL int3() {
	__try {
		__asm {
			__emit 0xCC
		}
		return TRUE;
	}
	__except (1) {
		return FALSE;
	}
}
BOOL int_2d() {
	__try {
		__asm {
			int 0x2d
				nop
		}
	}
	__except (1) {
		return FALSE;
	}
	return TRUE;
}
BOOL CloseHandleExcept() {
	__try {
		CloseHandle((HANDLE)0x66666666);
		return FALSE;
	}
	__except (1) {
		return TRUE;
	}
}
BOOL RaiseExcept() {
	__try {
		RaiseException(DBG_RIPEXCEPTION,0,0,0);
		return TRUE;
	}
	__except (1) {
		return FALSE;
	}
}

void FD_Except() {
	printf("FD_EXCEPT:\n");
	if (int_2d())
		printf("\t[+]int_2d \t- except \n");
	else
		printf("\t[-]int_2d \t- no except\n");
	if (int1())
		printf("\t[+]int1 \t not- except\n");
	else
		printf("\t[-]int1 \t- except\n");
	if (int3())
		printf("\t[+]int3 \t not- except\n");
	else
		printf("\t[-]int3 \t- except\n");
	if (CloseHandleExcept())
		printf("\t[+]CloseHandle \t- except\n");
	else
		printf("\t[-]CloseHandle \t- not except\n");
	if (RaiseExcept())
		printf("\t[+]RaiseExcept \t- except\n");
	else
		printf("\t[-]RaiseExcept \t- not except\n");
}