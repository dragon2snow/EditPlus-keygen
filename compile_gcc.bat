@echo off



cls
title Compiling batch file   by wxx9248



echo ******************************
echo     Compiling batch file
echo.
echo      using mingw-w64 gcc
echo.
echo          by wxx9248
echo ******************************



set CC=gcc
set WINDRES=windres

echo >%windir%\tmp.txt
if not exist %windir%\tmp.txt (goto PERMISSION_DENIED)
del /f /q /a %windir%\tmp.txt

%CC% >nul 2>nul
if %ERRORLEVEL% == 9009 (goto gcc_FAILED)

rem Reset errorlevel
dir >nul 2>nul

%CC% --version | findstr MinGW-W64 >nul 2>nul
if %ERRORLEVEL% == 1 (goto MinGW-W64_FAILED)

rem Reset errorlevel
dir >nul 2>nul

%WINDRES% --help >nul 2>nul
if %ERRORLEVEL% == 9009 (goto windres_FAILED)

rem Reset errorlevel
dir >nul 2>nul

set APIsPATH=.\APIs
set OBJ_OUTPATH_64=.\obj_out\x86_64
set OBJ_OUTPATH_32=.\obj_out\x86
set PE_OUTPATH_64=.\PE_out\x86_64
set PE_OUTPATH_32=.\PE_out\x86
set RESPATH=.\res

set EXEFLAGS=-std=c11
set OBJFLAGS=-c -std=c11
set DLLFLAGS=-shared -std=c11
set LINKFLAGS_64=-L%PE_OUTPATH_64% -lclr64 -lclip64 -lgen64
set LINKFLAGS_32=-L%PE_OUTPATH_32% -lclr -lclip -lgen

md %OBJ_OUTPATH_64% >nul 2>nul
md %OBJ_OUTPATH_32% >nul 2>nul
md %PE_OUTPATH_64% >nul 2>nul
md %PE_OUTPATH_32% >nul 2>nul

del /f /s /q /a %PE_OUTPATH_64%\*.* >nul 2>nul
del /f /s /q /a %PE_OUTPATH_32%\*.* >nul 2>nul


%CC% %DLLFLAGS% %APIsPATH%\clrscr.c -o %PE_OUTPATH_64%\libclr64.dll
if %ERRORLEVEL% == 1 (goto compilation_FAILED)
rem Reset errorlevel
dir >nul 2>nul
%CC% %DLLFLAGS% %APIsPATH%\copy_to_clipboard.c -o %PE_OUTPATH_64%\libclip64.dll
if %ERRORLEVEL% == 1 (goto compilation_FAILED)
rem Reset errorlevel
dir >nul 2>nul
%CC% %DLLFLAGS% %APIsPATH%\generate.c -o %PE_OUTPATH_64%\libgen64.dll
if %ERRORLEVEL% == 1 (goto compilation_FAILED)
rem Reset errorlevel
dir >nul 2>nul
%CC% %OBJFLAGS% main.c -o %OBJ_OUTPATH_64%\main64.o
if %ERRORLEVEL% == 1 (goto compilation_FAILED)
rem Reset errorlevel
dir >nul 2>nul
%WINDRES% -l 0409,04b0 -c=437  -i %RESPATH%\1033\resource.rc -o %OBJ_OUTPATH_64%\resource64_1033.o
if %ERRORLEVEL% == 1 (goto compilation_FAILED)
rem Reset errorlevel
dir >nul 2>nul
%WINDRES% -l 0804,04b0 -c=936 -i %RESPATH%\2052\resource.rc -o %OBJ_OUTPATH_64%\resource64_2052.o
if %ERRORLEVEL% == 1 (goto compilation_FAILED)
rem Reset errorlevel
dir >nul 2>nul
%CC% %EXEFLAGS% %LINKFLAGS_64% %OBJ_OUTPATH_64%\main64.o %OBJ_OUTPATH_64%\resource64_1033.o %OBJ_OUTPATH_64%\resource64_2052.o -o %PE_OUTPATH_64%\keygen64.exe
if %ERRORLEVEL% == 1 (goto compilation_FAILED)
rem Reset errorlevel
dir >nul 2>nul

%CC% -m32 %DLLFLAGS% %APIsPATH%\clrscr.c -o %PE_OUTPATH_32%\libclr.dll
if %ERRORLEVEL% == 1 (goto compilation_FAILED)
rem Reset errorlevel
dir >nul 2>nul
%CC% -m32 %DLLFLAGS% %APIsPATH%\copy_to_clipboard.c -o %PE_OUTPATH_32%\libclip.dll
if %ERRORLEVEL% == 1 (goto compilation_FAILED)
rem Reset errorlevel
dir >nul 2>nul
%CC% -m32 %DLLFLAGS% %APIsPATH%\generate.c -o %PE_OUTPATH_32%\libgen.dll
if %ERRORLEVEL% == 1 (goto compilation_FAILED)
rem Reset errorlevel
dir >nul 2>nul
%CC% -m32 %OBJFLAGS% main.c -o %OBJ_OUTPATH_32%\main.o
if %ERRORLEVEL% == 1 (goto compilation_FAILED)
rem Reset errorlevel
dir >nul 2>nul
%WINDRES% --output-format=coff --target=pe-i386 -l 0409,04b0 -c=437 -i %RESPATH%\1033\resource.rc -o %OBJ_OUTPATH_32%\resource_1033.o
if %ERRORLEVEL% == 1 (goto compilation_FAILED)
rem Reset errorlevel
%WINDRES% --output-format=coff --target=pe-i386 -l 0804,04b0 -c=936 -i %RESPATH%\2052\resource.rc -o %OBJ_OUTPATH_32%\resource_2052.o
if %ERRORLEVEL% == 1 (goto compilation_FAILED)
rem Reset errorlevel
dir >nul 2>nul
%CC% -m32 %EXEFLAGS% %LINKFLAGS_32% %OBJ_OUTPATH_32%\main.o %OBJ_OUTPATH_32%\resource_1033.o %OBJ_OUTPATH_32%\resource_2052.o -o %PE_OUTPATH_32%\keygen.exe
if %ERRORLEVEL% == 1 (goto compilation_FAILED)
rem Reset errorlevel
dir >nul 2>nul




echo.
choice /M "Debug?"
if %ERRORLEVEL% == 1 (goto debug)
if %ERRORLEVEL% == 2 (goto quit)




:debug
choice /M "Choose arch(6:x86_64, 3:x86)£º" /C "63"
set CHOICE=%ERRORLEVEL%
set /p PARAM="Enter parameters:"
if %CHOICE% == 1 (goto x86_64)
if %CHOICE% == 2 (goto x86)




:x86_64
%PE_OUTPATH_64%\keygen64 %PARAM%
pause
goto quit

:x86
%PE_OUTPATH_32%\keygen %PARAM%
pause

:gcc_FAILED
echo.
echo GCC not found! Please check your GCC installation and environment configuration!
pause
goto quit

:windres_FAILED
echo.
echo WINDRES not found! Please check your GCC installation!
pause
goto quit

:compilation_FAILED
echo.
echo Compilation failed!
pause
goto quit

:MinGW-W64_FAILED
echo.
echo This GCC version is not built by MinGW-W64 project, which is not suitable for this project. Please goto http://mingw-w64.org/doku.php to download a latest version!

ping -n 3 127.1 >nul 2>nul

echo [InternetShortcut] >%tmp%\mingw-w64.url
echo URL=http://mingw-w64.org/doku.php >>%tmp%\mingw-w64.url
%tmp%\mingw-w64.url
del /f /q /a %tmp%\mingw-w64.url >nul 2>nul

pause
goto quit

:PERMISSION_DENIED
echo.
echo You don't have an administration privilege, please run this script as an administrator!
pause
goto quit

:quit
exit
