echo %~dp0
pushd %~dp0
set CurrentDir=%CD%
chdir /d %CurrentDir%

rmdir /Q /S .\Lib\Common\Inc
rmdir /Q /S .\Lib\Common\Lib
rmdir /Q /S .\Lib
rmdir /Q /S Build\Output
del Build\*.emSession
del Build\*.jlink
del .\Src\.clang-format

rmdir /Q /S .\Src\BSP\MCU
rmdir /Q /S .\Src\BSP\Clock

rmdir /Q /S .\Src\App\RTOS
