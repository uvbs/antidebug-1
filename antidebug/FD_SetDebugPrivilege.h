void FD_SetDebugPrivilege() {
	PROCESSENTRY32 ProEntry = { 0 };
	DWORD pid = GetProcessIDByNameA("csrss.exe",&ProEntry);
	printf("FD_SetDebugPrivilege:\n");
	if (OpenProcess(PROCESS_QUERY_INFORMATION, 0, pid) != 0)
		printf("\t[+]SetDebugPrivilege Success\n");
	else
		printf("\t[-]SetDebugPrivilege Faild\n");
}
