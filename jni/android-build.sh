#!/bin/sh
cp ../.dynacoe/MODE ./
cp ../.dynacoe/PATH ./
cp ../.dynacoe/PROJECT ./
ndk-build NDK_PROJECT_PATH=../ V=1 $@
rm MODE PATH PROJECT
