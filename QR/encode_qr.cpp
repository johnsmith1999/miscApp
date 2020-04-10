
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
const char * target_qr_img_file, //the qr image file name and path to create,
                                 //such as d:\temp\temp_qr_image.png
const char * input_string, //the string to create qr image
const int string_length    //the length of the input_string
if success,the return value is 0.and an image will be created.
*/

int encode_string_to_qrimage(const char * qrdllfile,
                char * target_qr_img_file,
                char * input_string,
                int string_length)
{
    int rtnv = 0;
    HINSTANCE hDll;
    typedef int (WIN___CALL *qrLoadFunc)(char * p1,char * p2,int p3);
    qrLoadFunc loadqrfunc;

#if (_MSC_VER > 1300)
	hDll = LoadLibraryEx(qrdllfile , NULL , 0);
#else
	hDll = LoadLibrary(qrdllfile);
#endif
    if(!hDll) {
        MessageBox(NULL, TEXT("Cannot load QrCoder.dll"), "Tip", MB_OK);
	rtnv = 1;
        return rtnv;
    }
    loadqrfunc = (qrLoadFunc) GetProcAddress(hDll, "QrEncode");
    if (loadqrfunc)
    {
	rtnv = (*loadqrfunc)(target_qr_img_file,input_string,string_length);
    }else{
	rtnv = 2;
    }
    FreeLibrary(hDll);
    return rtnv;
}


