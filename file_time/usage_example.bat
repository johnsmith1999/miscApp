
rem set single file
rem filetimeset.exe r:\ses\aaa.zip 1 2019_11_12_3_22_15_15_512 1 2019_11_12_3_22_15_15_515 1 2019_11_12_3_22_15_15_517 0 *.*
rem set all files in a directory
rem filetimeset.exe r:\ses 1 2019_11_12_3_22_15_15_512 1 2019_11_12_3_22_15_15_515 1 2019_11_12_3_22_15_15_517 0 *.*
rem set files with specified extention in a directory
rem filetimeset.exe r:\ses\aaa.zip 1 2019_11_12_3_22_15_15_512 1 2019_11_12_3_22_15_15_515 1 2019_11_12_3_22_15_15_517 0 *.zip
rem set files with specified extention in a directory,include sub dir.
rem filetimeset.exe r:\ses\aaa.zip 1 2019_11_12_3_22_15_15_512 1 2019_11_12_3_22_15_15_515 1 2019_11_12_3_22_15_15_517 1 *.abc


@echo off
SETLOCAL enableDelayedExpansion

set timecreate=2000_11_12_3_22_15_15_512
set timemodify=2000_11_12_3_22_15_15_515
set timeaccess=2000_11_12_3_22_15_15_517
set fileext=*.*
set tmcreate=1
set tmmodify=1
set tmaccess=1
set subdir=1
set rootpath=r:\sec


if "%PROCESSOR_ARCHITECTURE%"=="x86"   (set timesetter=FileTimeSet_32.exe)
if "%PROCESSOR_ARCHITECTURE%"=="AMD64" (set timesetter=FileTimeSet_64.exe)

call :UpdataFileTime %timesetter% %rootpath% %tmcreate% %timecreate% %tmmodify% %timemodify% %tmaccess% %timeaccess% %subdir% %fileext%

    :funcfinish

    goto :ENDEND

    :UpdataFileTime
        echo off
        set texe=%~1
        set tpath=%~2
        set ftc=%~3
        set ftcv=%~4
        set ftm=%~5
        set ftmv=%~6
        set fta=%~7
        set ftav=%~8
        set fsub=%~9
        set fext=%~10
        @%texe% %tpath% %ftc% %ftcv% %ftm% %ftmv% %fta% %ftav% %fsub% %fileext% >>buildver.log

    goto :eof

::==========================================================================finish
:ENDEND
@endlocal



