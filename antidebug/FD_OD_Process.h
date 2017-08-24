BOOL FD_OD_Module_OD(PCHAR ExeFile,DWORD ProcessID){
	BOOL ret = FALSE;
	HANDLE hModuleShot = 0;
	MODULEENTRY32 m32w = {0};
	m32w.dwSize = sizeof(m32w);
	
	hModuleShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,ProcessID);
	if(hModuleShot == INVALID_HANDLE_VALUE)
		return FALSE;
	if(Module32First(hModuleShot,&m32w)){
		do{
			int i = 0;
		//	printf("\t\t[*]%s\n",m32w.szModule);
			while(gOllyDbgDll[i][0]!=0){
				strupr(gOllyDbgDll[i]);
				strupr(m32w.szModule);
				if(strstr(m32w.szModule,gOllyDbgDll[i])){
					ret = TRUE;
					printf("\t[+]EnumModule - %s:%s\n",ExeFile,m32w.szModule);
				}else{
					//printf("\t\t\t[-]GetWindowTextA - %s:%s\n",gOllyDbg[i],ch);
				}
				i++;
			}
		}while(Module32Next(hModuleShot,&m32w));
	}
	return ret;
}
BOOL FD_OD_Process_OD(){
	BOOL ret = FALSE;
	HANDLE hProcessShot = 0;
	PROCESSENTRY32 pe32w = {0};
	pe32w.dwSize = sizeof(pe32w);//sizeof(PROCESSENTRY32) - GetLastError() - 24
	hProcessShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	if(hProcessShot == INVALID_HANDLE_VALUE){
		return FALSE;
	}
	if(Process32First(hProcessShot,&pe32w)){
		do{
			int i = 0;
		//	printf("\t%04d:%s\n",pe32w.th32ProcessID,pe32w.szExeFile);
			ret = FD_OD_Module_OD(pe32w.szExeFile,pe32w.th32ProcessID);
			while(gOllyDbg[i][0]!=0){
			strupr(gOllyDbgDll[i]);
			strupr(pe32w.szExeFile);
			if(strstr(pe32w.szExeFile,gOllyDbg[i])){
				ret = TRUE;
				printf("\t[+]EnumProcess - %s:%s\n",pe32w.szExeFile,gOllyDbg[i]);
			}else{
				//printf("\t\t\t[-]GetWindowTextA - %s:%s\n",gOllyDbg[i],ch);
			}
			i++;
		}
		}while(Process32Next(hProcessShot,&pe32w));
	}
	CloseHandle(hProcessShot);
	return ret;
}
void FD_OD_Process(){
	printf("FD_OD_Process:\n");
	FD_OD_Process_OD();
}