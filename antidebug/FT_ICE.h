BOOL FT_ICE_Asm(){
	__try{
		__asm{
			__emit 0xF1
		}
		return true;
	}__except(1){
		return false;
	}
}
void FT_ICE(){
	printf("FT_ICE:\n");
	if(FT_ICE_Asm())
		printf("\t[+]__emit 0xF1 not excep\n");
	else
		printf("\t[-]__emit 0xF1 excep\n");
}