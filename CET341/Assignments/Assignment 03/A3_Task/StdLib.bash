#!/bin/bash -f

rm -r -f ./Lib
mkdir ./Lib/
mkdir ./Lib/Common

ln -s ../../../StdLib/Common/Inc/.clang-format ./Src/.clang-format 
cd ./Lib/Common
ln -s ../../../../../StdLib/Common/Inc Inc 
ln -s ../../../../../StdLib/Common/Lib Lib
cd ../..


cd       ./Src/BSP/

rm -r -f MCU
ln -s ../../../../../StdLib/stm32F7/BSP/MCU MCU

rm -r -f Clock
ln -s ../../../../../StdLib/stm32F7/BSP/Clock Clock


rm -r -f Timer
cd ../..
cd       ./src/BSP/

