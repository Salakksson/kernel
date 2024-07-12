#!/bin/bash
set -e

# make clean
make build
qemu-system-x86_64 -cdrom dist/kernel.iso

