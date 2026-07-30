@echo off
rem compile-2pong.cmd -- Build 2Pong for ArcaOS / kLIBC
rem Run from the 2Pong-Source\ directory (where conf.xml lives).
rem
rem Dependencies (install via ArcaOS rpm):
rem   SDL 1.2, SDL_mixer, SDL_net, libxml2
rem
rem If the lib names on your system differ, edit Makefile.os2:
rem   SDL_dll.a / SDL_mixer_dll.a / SDL_net_dll.a / xml2_dll.a

setlocal

set EMXOMFLD_TYPE=WLINK
set EMXOMFLD_LINKER=wl.exe
set EMXOMFLD_PRELINK=0

cd src
make -f Makefile.os2 %1 %2 2>&1 | tee ..\compile-2pong.log
cd ..

endlocal
