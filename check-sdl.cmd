@echo off
rem check-sdl.cmd -- Verify SDL 1.x, SDL_mixer, SDL_net, libxml2 on ArcaOS
rem Run from anywhere on ArcaOS. Results written to check-sdl.log here.

set LOG=check-sdl.log
echo 2Pong SDL dependency check > %LOG%
echo ============================= >> %LOG%
echo. >> %LOG%

rem --- All SDL-related headers ---
echo [SDL headers in %UNIXROOT%\usr\include\SDL\] >> %LOG%
dir %UNIXROOT%\usr\include\SDL\*.h /b >> %LOG% 2>NUL
if errorlevel 1 echo   (directory not found or empty) >> %LOG%
echo. >> %LOG%

rem --- libxml2 headers ---
echo [libxml2 headers] >> %LOG%
if exist %UNIXROOT%\usr\include\libxml2\libxml\tree.h (
    echo   FOUND: %UNIXROOT%\usr\include\libxml2\libxml\tree.h >> %LOG%
) else (
    echo   MISSING >> %LOG%
)
echo. >> %LOG%

rem --- All lib files matching SDL or xml ---
echo [Lib files in %UNIXROOT%\usr\lib\ matching SDL or xml] >> %LOG%
dir %UNIXROOT%\usr\lib\SDL*.* /b >> %LOG% 2>NUL
dir %UNIXROOT%\usr\lib\sdl*.* /b >> %LOG% 2>NUL
dir %UNIXROOT%\usr\lib\*xml*.* /b >> %LOG% 2>NUL
echo. >> %LOG%

rem --- DLLs ---
echo [DLLs in %UNIXROOT%\usr\bin\ matching SDL or xml] >> %LOG%
dir %UNIXROOT%\usr\bin\SDL*.dll /b >> %LOG% 2>NUL
dir %UNIXROOT%\usr\bin\sdl*.dll /b >> %LOG% 2>NUL
dir %UNIXROOT%\usr\bin\*xml*.dll /b >> %LOG% 2>NUL
echo. >> %LOG%

rem --- Also check BEGINLIBPATH locations ---
echo [DLLs in %UNIXROOT%\usr\lib\ matching SDL or xml] >> %LOG%
dir %UNIXROOT%\usr\lib\SDL*.dll /b >> %LOG% 2>NUL
dir %UNIXROOT%\usr\lib\sdl*.dll /b >> %LOG% 2>NUL
dir %UNIXROOT%\usr\lib\*xml*.dll /b >> %LOG% 2>NUL
echo. >> %LOG%

type %LOG%
echo.
echo Results also saved to: %LOG%
