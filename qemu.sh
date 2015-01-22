#!/bin/sh
set -e
#. ./iso.sh

. ./build.sh

qemu-system-$(./target-triplet-to-arch.sh $HOST) -kernel sysroot/boot/myos.kernel -curses

# qemu-system-$(./target-triplet-to-arch.sh $HOST) -cdrom myos.iso -curses
