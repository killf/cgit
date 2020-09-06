#!/usr/bin/env bash
mkdir cgit/build && cd cgit/build && cmake ..
make -j8 && sudo make install