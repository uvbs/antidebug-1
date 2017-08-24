//FD_OD_Window
BOOL CALLBACK EnumWindowsProc(HWND hwnd,LPARAM lParam)
{
	char ch[100];
	int i=0;
	if (IsWindowVisible(hwnd))
	{
		GetWindowTextA(hwnd,ch,100);
		strupr(ch);
		printf("\t\tEnumWindow - %s\n",ch);
		while(gOllyDbg[i][0]!=0){
			strupr(gOllyDbg[i]);
			if(strstr(ch,gOllyDbg[i])){
				printf("\t[+]GetWindowTextA - %s:%s\n",gOllyDbg[i],ch);
			}else{
				//printf("\t\t\t[-]GetWindowTextA - %s:%s\n",gOllyDbg[i],ch);
			}
			i++;
		}
	}
	return TRUE;
}

void FD_OD_Window(){
	int i = 0;
	printf("FD_OD_Window:\n");
	while(gOllyDbg[i][0]!=0){
		strupr(gOllyDbg[i]);
		if(FindWindowA(gOllyDbg[i],0))
			printf("\t[+]FindWindowA - %s\n",gOllyDbg[i]);
		else
			printf("\t[-]FindWindowA - %s\n",gOllyDbg[i]);
		i++;
	}
	EnumWindows(EnumWindowsProc,0);
}