@echo off
rem launch this from msvc-enabled console


set CFLAGS=/std:c11 /O2 /FC /W4 /WX /wd4996 /nologo
set LIBS=

set EXAMPLES=./examples/fib.har ./examples/123i.har ./examples/123f.har ./examples/e.har

cl.exe %CFLAGS% ./src/hackc.c

cl.exe %CFLAGS% ./src/hack.c

cl.exe %CFLAGS% ./src/dehack.c

cl.exe %CFLAGS% ./src/hdb.c

rem TODO(#25): hdb is not built on Windows

if "%1" == "examples" setlocal EnableDelayedExpansion && for %%e in (%EXAMPLES%) do (
    set name=%%e
    "./hackc.exe" -d !name:~0,-3!hack %%e
)
