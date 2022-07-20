@echo off
rem launch this from msvc-enabled console

set CFLAGS=/std:c11 /O2 /FC /W4 /WX /wd4996 /nologo /Fe.\build\bin\ /Fo.\build\bin\
set LIBS=

mkdir build
mkdir build\bin
mkdir build\examples

cl.exe %CFLAGS% .\src\hackc.c
cl.exe %CFLAGS% .\src\hack.c
cl.exe %CFLAGS% .\src\dehack.c
cl.exe %CFLAGS% .\src\hdb.c
cl.exe %CFLAGS% .\src\hack2nasm.c

if "%1" == "examples" setlocal EnableDelayedExpansion && for /F "tokens=*" %%e in ('dir /b .\examples\*.hack') do (
    set name=%%e
    ".\build\bin\hackc.exe" -d .\examples\%%e .\build\examples\!name:~0,-4!hvm
)
