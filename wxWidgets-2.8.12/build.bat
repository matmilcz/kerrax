@echo off

REM wxWidgets 2.8.12 framework compilation script
REM Requires Visual Studio 2010

REM Add Visual Studio 2010 tools to PATH variable
SET PATH=%PATH%;C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\bin\

REM We need to be in this directory in order for build to work
PUSHD build\msw

REM Remove potential leftovers from previous build
DEL /S /Q vc_mswd
DEL /S /Q vc_mswud

REM Setup all Visual Studio tools variables
CALL vcvars32.bat

REM Compile in Unicode Debug configuration
REM It is required by KrxImpExp
nmake -f makefile.vc BUILD=debug UNICODE=1

REM Return to base directory
POPD

