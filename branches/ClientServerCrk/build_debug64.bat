call scons Server arch=x86_64 mode=debug %*
call scons Client arch=x86_64 mode=debug %*
call scons Proxy arch=x86_64 mode=debug %*
pause
