call scons Server arch=x86 mode=release %*
call scons Client arch=x86 mode=release %*
call scons Proxy arch=x86 mode=release %*
pause
