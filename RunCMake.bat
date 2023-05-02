@echo off

rem Copy the commit-msg git hook, but don't overwrite any existing file
echo n | copy /-y tools\git_hooks\commit-msg .git\hooks\commit-msg >NUL

set buildDir=%1

rem by default, put space in build directory name; this 
rem provides a bit of testing [ROSETTA-1167]
if "%buildDir%"=="" (set buildDir="build folder")

if not exist %buildDir%\ md %buildDir% || goto :EOF

pushd %buildDir%

echo ### Running CMake
call cmake -G "Visual Studio 15 2017 Win64" ..
popd
