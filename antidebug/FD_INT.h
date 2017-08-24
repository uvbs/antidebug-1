BOOL FD_INT_INT2D(){
	__try{
		__asm{
			int 0x2d
			nop
		}
	}__except(1){
		return FALSE;
	}
	return TRUE;
}
void FD_INT(){
	printf("FD_INT:\n");
	if(FD_INT_INT2D())
		printf("\t[+]int2d - except\n");
	else
		printf("\t[-]int2d - no except\n");
}
	