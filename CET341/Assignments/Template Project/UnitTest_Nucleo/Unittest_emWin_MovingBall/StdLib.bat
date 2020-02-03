echo %~dp0
pushd %~dp0
set CurrentDir=%CD%
chdir /d %CurrentDir%

rmdir /Q /S .\Lib
mkdir .\Lib\
mkdir .\Lib\Common
mkdir .\Src\App

mklink /H .\Src\.clang-format ..\..\..\StdLib\Common\Inc\.clang-format

mklink /j .\Lib\Common\Inc ..\..\..\StdLib\Common\Inc

mklink /j .\Lib\Common\Lib ..\..\..\StdLib\Common\Lib

rmdir /Q /S .\Src\App\RTOS
mklink /j .\Src\App\RTOS ..\..\..\StdLib\FreeRTOS

rmdir /Q /S .\Src\App\GUI
mklink /j .\Src\App\GUI ..\..\..\StdLib\STemWin

rmdir /Q /S .\Src\BSP\MCU
mklink /j .\Src\BSP\MCU ..\..\..\StdLib\stm32F7\BSP\MCU

rmdir /Q /S .\Src\BSP\Clock
mklink /j .\Src\BSP\Clock ..\..\..\StdLib\stm32F7\BSP\Clock

rmdir /Q /S .\Src\BSP\Spim
mklink /j .\Src\BSP\Spim ..\..\..\StdLib\stm32F7\BSP\Spim

rmdir /Q /S .\Src\BSP\Dma
mklink /j .\Src\BSP\Dma ..\..\..\StdLib\stm32F7\BSP\Dma
pause