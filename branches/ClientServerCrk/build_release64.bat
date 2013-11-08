call scons Server arch=x86_64 mode=release %*
call scons Client arch=x86_64 mode=release %*
call scons Proxy arch=x86_64 mode=release %*
pause
