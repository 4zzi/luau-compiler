@echo off
cls

call "I:\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"

msbuild "luaucompiler.sln" /p:Configuration=Release /p:Platform=x64

:: start "" "..\build\x64\Release\output\Xeno.exe"