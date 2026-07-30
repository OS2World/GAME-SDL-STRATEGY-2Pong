@echo off
rem patch-sdl.cmd -- Fix SDL_config_os2.h uintptr_t conflict with kLIBC GCC 9.2
rem Uses sed (available on ArcaOS). Run ONCE before building 2Pong.

set LOG=patch-sdl.log
set SDL=C:\usr\include\SDL\SDL_config_os2.h
set SDL_BAK=C:\usr\include\SDL\SDL_config_os2.h.orig
set SDL_TMP=C:\usr\include\SDL\SDL_config_os2.tmp

echo patch-sdl.cmd log > %LOG%
echo ================== >> %LOG%
echo Target: %SDL% >> %LOG%
echo. >> %LOG%

if not exist %SDL% (
    echo ERROR: %SDL% not found >> %LOG%
    type %LOG%
    goto end
)
echo File exists: YES >> %LOG%

if exist %SDL_BAK% (
    echo Backup already exists: %SDL_BAK% >> %LOG%
    echo Delete it to re-run this script. >> %LOG%
    type %LOG%
    goto end
)

rem Backup
copy %SDL% %SDL_BAK% > NUL
echo Backup created: %SDL_BAK% >> %LOG%

rem Apply patch via sed (| delimiter avoids / conflicts in pattern)
sed "s|typedef unsigned long       uintptr_t;|/* typedef unsigned long       uintptr_t; */  /* kLIBC sys/types.h provides this */|" %SDL_BAK% > %SDL_TMP%
if errorlevel 1 (
    echo ERROR: sed failed >> %LOG%
    type %LOG%
    goto end
)
echo sed exit code: 0 >> %LOG%

rem Replace original with patched version
copy %SDL_TMP% %SDL% > NUL
del %SDL_TMP%
echo Patched file written >> %LOG%

rem Verify
echo. >> %LOG%
echo [Lines containing uintptr_t in patched file] >> %LOG%
grep uintptr_t %SDL% >> %LOG%

echo. >> %LOG%
echo Done. >> %LOG%

:end
type %LOG%
