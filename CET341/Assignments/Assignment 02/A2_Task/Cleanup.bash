#!/bin/bash -f

rm -r -f ./Lib/Common/Inc
rm -r -f ./Lib/Common/Lib
rm -r -f ./Lib
rm -r -f ./build/Output
rm       ./build/*.emSession
rm       ./build/*.jlink

rm       ./Src/.clang-format
rm       ./Src/BSP/MCU
rm       ./Src/BSP/Clock
