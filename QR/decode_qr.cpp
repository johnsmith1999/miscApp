
#include <windows.h>
#include <stdio.h>

#if (_MSC_VER > 1310)
    #ifndef WIN___CALL
        #define WIN___CALL __stdcall
    #endif
#else
    #ifndef WIN___CALL
        #define WIN___CALL CALLBACK
    #endif
#endif

/*
parameters of function
const char * qrdllfile, //the qr dll file name and path.such as c:\qr\qrcoder_32.dll(32bit) or
                        //c:\qr\qrcoder_64.dll(64bit)
const char * qr_img_file, //the qr image file name and path to decode,
                                 //such as d:\temp\temp_qr_image.png
char * decode_data, //decode qr image to this string

return value:
if success,the return value is the length of decode string(decode_data).
others mean error.
note:
must have enough buffer for decode_data.
*/

int decode_qrimage_to_string(const char * qrdllfile,const char * qr_img_file,char * decode_data)
{
    int rtnv = 0;
    HINSTANCE hDll;
    typedef int (WIN___CALL *qrDecodeFunc)(char * p1,char * p2);
    qrDecodeFunc decqrfunc;

#if (_MSC_VER > 1300)
	hDll = LoadLibraryEx(qrdllfile , NULL , 0);
#else
	hDll = LoadLibrary(qrdllfile);
#endif
    if(!hDll) {
        MessageBox(NULL, TEXT("Cannot load QrCoder.dll"), NULL, MB_OK);
	rtnv = -1;
        return rtnv;
    }
    decqrfunc = (qrDecodeFunc) GetProcAddress(hDll, "QrDecode");
    if (decqrfunc)
    {
        rtnv = (*decqrfunc)(qr_img_file,decode_data);
    }else{
	rtnv = -2;
    }
    FreeLibrary(hDll);
    return rtnv;
}


