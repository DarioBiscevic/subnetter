#!/bin/sh

CFLAGS="-Wall"
LIBS="-lm"

EXEC="subnetter"
TARGETDIR="target"
INCLUDEDIR="include"
SRCDIR="src"

mkdir -p $TARGETDIR

gcc -I $INCLUDEDIR $SRCDIR/* $CFLAGS $LIBS -o $TARGETDIR/$EXEC