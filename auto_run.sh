#!/bin/sh

echo "-------make distclean------>"
make distclean
echo "-------make clean------>"
make clean
echo "-------make itop4412_defconfig------>"
make itop4412_defconfig ARCH=arm
echo "-------make------>"
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
