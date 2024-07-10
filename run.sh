#!/bin/bash
make build-x86
qemu-system-x86_64 -cdrom dist/kernel.iso
