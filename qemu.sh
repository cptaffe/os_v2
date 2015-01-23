#!/bin/sh
set -e
#. ./iso.sh

. ./build.sh

qemu-system-$(./target-triplet-to-arch.sh $HOST) -kernel sysroot/boot/myos.kernel -curses -k en-us

# qemu-system-$(./target-triplet-to-arch.sh $HOST) -cdrom myos.iso -curses
