DWORD gTime = 0;
DWORD FT_TIME_RDTSC(){
	__asm{
		rdtsc
		mov eax,edx
	}
}
void FT_TIME_Start(){
	printf("FT_TIME_START:\n");
	gTime = FT_TIME_RDTSC();
	printf("\t[*]rdtsc = %08X\n",gTime);
}
void FT_TIME_End(){
	DWORD t = 0;
	printf("FT_TIME_END:\n");
	t = FT_TIME_RDTSC();
	printf("\t[*]rdtsc = %08X\n",t);
	t = t - gTime;
	if(t > 5 || t < 0)
		printf("\t[+]rdtsc delay = %08X\n",t);
	else
		printf("\t[-]rdtsc delay = %08X\n",t);
}