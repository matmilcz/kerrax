#!/bin/bash

# REQUIRES ROOT

mkdir buildgtk
cd buildgtk
../configure --enable-debug --with-gtk --enable-unicod
make
make install
ldconfig

