// QRbtest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#if (_MSC_VER > 1310)
    #ifndef WIN___CALL
        #define WIN___CALL __stdcall
    #endif
#else
    #ifndef WIN___CALL
        #define WIN___CALL CALLBACK
    #endif
#endif
void load_qr();
void decodeqr(char * fn,char * data);

int main(int argc, char* argv[])
{
	char * data;
	int i = 0;
	if(argc > 1)
	{
	printf("argc = %d\r\nargv = %s %s\r\n",argc,argv[0],argv[2]);
	}
	printf("Hello World!\n");
	if(argc > 1)
	{
		data = (char * )malloc(sizeof(char) * 1024);
		decodeqr(argv[2],data);
		printf("data = %s\r\n",data);
		free(data);
	}else{
		load_qr();
	}
	data = NULL;
	return 0;
}
void decodeqr(char * fn,char * data)
{
	int rtnv = 0;
    HMODULE hDll;
	typedef int (WIN___CALL *StartDialogFunc)(char * p1,char * p2);
    StartDialogFunc StartDialog;

#if (_MSC_VER > 1300)
	hDll = LoadLibraryEx("QrCoder.dll" , NULL , 0);
#else
	hDll = LoadLibrary("QrCoder.dll");
#endif
    if(!hDll) {
        MessageBox(NULL, TEXT("Cannot load QrCoder.dll"), NULL, MB_OK);
        return;
    }
    StartDialog = (StartDialogFunc) GetProcAddress(hDll, "QrDecode");

    rtnv = (*StartDialog)(fn,data);

	FreeLibrary(hDll);
}
void load_qr()
{
	char * fn,* strs;
	int pl = 0;
	int rtnv;
    HMODULE hDll;
	typedef int (WIN___CALL *StartDialogFunc)(char * p1,char * p2,int p3);
    StartDialogFunc StartDialog;

#if (_MSC_VER > 1300)
	hDll = LoadLibraryEx("QrCoder.dll" , NULL , 0);
#else
	hDll = LoadLibrary("QrCoder.dll");
#endif
    if(!hDll) {
        MessageBox(NULL, TEXT("Cannot load QrCoder.dll"), NULL, MB_OK);
        return;
    }
    StartDialog = (StartDialogFunc) GetProcAddress(hDll, "QrEncode");

	fn = "r:\\dsdf.png";
	strs = "we are the champion of the world.";
	pl = (int)strlen(strs);
    rtnv = (*StartDialog)(fn,strs,pl);

	FreeLibrary(hDll);
}
