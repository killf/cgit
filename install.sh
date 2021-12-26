#!/usr/bin/env bash
n_threads=$(nproc)
echo "supporting threads number: " $n_threads
if [ -d "./cgit/build" ];
then 
    echo "do cmake clean work, delete cgit/build directory"
    rm -r -f ./cgit/build
else 
    ehco ""
fi
mkdir cgit/build && cd cgit/build && cmake ..
make -j$n_threads && sudo make install
