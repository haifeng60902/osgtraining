rem call scons Server arch=x86_64 mode=release %*


cd src\find
start getQtMoc.bat
cd ..\..
call scons find arch=x86_64 mode=release %*

pause
