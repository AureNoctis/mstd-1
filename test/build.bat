@echo off
setlocal enabledelayedexpansion
cd /D "%~dp0"
set "WORKSPACE_DIR=%~dp0"
if "%WORKSPACE_DIR:~-1%"=="\" set "WORKSPACE_DIR=%WORKSPACE_DIR:~0,-1%"

set "BUILD_DIR=%WORKSPACE_DIR%\..\build"

set "MODE=debug"

for %%a in (%*) do set "%%~a=1"

if "%debug%"=="1"   set "MODE=debug"
if "%release%"=="1" set "MODE=release"

set "CC=clang"
set "INCLUDES="
set "RELEASE_FLAGS=-O3 -DNDEBUG=1"
set "DEBUG_FLAGS=-g -O0 -DDEBUG=1"
set "COMMON_FLAGS=-Wall -Wextra -std=c11 -Wno-initializer-overrides -DMSTD_DEBUG"

if "%MODE%"=="debug" (
    set "OPTIONS=%COMMON_FLAGS% %DEBUG_FLAGS%"
) else (
    set "OPTIONS=%COMMON_FLAGS% %RELEASE_FLAGS%"
)

if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
pushd "%BUILD_DIR%"

    %CC% %OPTIONS% %INCLUDES% "%WORKSPACE_DIR%\test.c" -o test.exe

    if "%run%"=="1"     test.exe

popd

endlocal