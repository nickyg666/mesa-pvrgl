#!/bin/sh
# Cross llvm-config for mesa aarch64 builds.
# /usr/lib/llvm-21/lib now holds aarch64 libclang*.a + libLLVM.so.21.1
# (arm64 packages replaced the x86_64 files; headers arch-neutral).
exec /usr/lib/llvm-21/bin/llvm-config "$@"
