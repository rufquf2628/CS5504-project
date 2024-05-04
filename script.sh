#!/bin/bash

wl=lts
cpu=o3
bp=tage
cache=sky

../gem5/build/X86/gem5.opt -d ./results/$wl/$wl-$cpu-$bp-$cache multi_args.py
