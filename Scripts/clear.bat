rmdir /S /Q %~dp0..\NEncryptionKit\release
rmdir /S /Q %~dp0..\NEncryptionKit\debug
rmdir /S /Q %~dp0..\NEncryptionKit\build_
rmdir /S /Q %~dp0..\Example\build_
rmdir /S /Q %~dp0..\Example\release
rmdir /S /Q %~dp0..\Example\debug
rmdir /S /Q %~dp0..\bin
del /Q %~dp0..\Makefile*
del /Q %~dp0..\NEncryptionKit\Makefile*
del /Q %~dp0..\Example\Makefile*
