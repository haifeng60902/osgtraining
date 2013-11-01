call scons arch=x86 mode=debug %1
call scons arch=x86 mode=release %1
call scons arch=x86_64 mode=debug %1
call scons arch=x86_64 mode=release %1

pause