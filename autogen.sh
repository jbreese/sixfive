#!/bin/sh

# Because we haven't written these files yet, and we'll get yelled at
touch NEWS AUTHORS ChangeLog

# Create Makefile.in and friends
autoreconf --force --install
