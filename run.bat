@echo off
setlocal

rem Set the path to your CMake executable and build directory
set CMAKE_PATH=cmake.EXE
set BUILD_DIR=build
set EXECUTABLE_PATH=%BUILD_DIR%\bin\main.exe

rem Configure the project
"%CMAKE_PATH%" -S . -B "%BUILD_DIR%"  

rem Build the specific target 'main'
"%CMAKE_PATH%" --build "%BUILD_DIR%"   --target main -j 10

rem Check if the executable exists and run it
if exist "%EXECUTABLE_PATH%" (
    echo Running the executable...
    start "" "%EXECUTABLE_PATH%"
) else (
    echo Executable not found!
)


endlocal
