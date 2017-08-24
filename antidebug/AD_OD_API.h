void AD_OD_API_SendMessage(){
	char ch[100];
	int i=0;
	HWND hwnd = GetForegroundWindow();

	GetWindowTextA(hwnd,ch,100);
	_strupr_s(ch,100);
	while(gOllyDbg[i][0]!=0){
		_strupr_s(gOllyDbg[i],32);
		if(strstr(ch,gOllyDbg[i])){
			printf("\t\t[+]GetWindowTextA - %s:%s\n",gOllyDbg[i],ch);
			printf("\t[*]SendMessage - %s\n",ch);
			SendMessageA(hwnd,WM_CLOSE,0,0);
		}else{
			printf("\t\t[-]GetWindowTextA - %s:%s\n",gOllyDbg[i],ch);
		}
		i++;
	}
}
void AD_OD_API(){
	printf("AD_OD_API:\n");
	OutputDebugStringA("%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s");
	printf("\t[*]OutputDebugStringA\n");
	printf("\t[*]GetForegroundWindow\n");
	AD_OD_API_SendMessage();
}