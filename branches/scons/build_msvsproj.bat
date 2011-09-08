Rem to generate one solution for both x86 and x64 platforms
call scons -C ./Make mode=msvsproj %*
pause
