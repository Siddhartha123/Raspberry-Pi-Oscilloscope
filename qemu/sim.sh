#!/bin/bash
make clean
make
qemu-system-aarch64 -machine raspi3 -kernel ./kernel8.img -vga std

