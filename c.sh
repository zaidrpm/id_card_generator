#!/bin/bash
a1=$(date +%s%N | cut -b1-13)
echo '.'
echo '.'
echo '.'
g++ -ggdb "/home/zaid/Projects/c++/$1" -o /home/zaid/Projects/c++/open ` pkg-config --cflags --libs opencv`
a2=$(date +%s%N | cut -b1-13)
diff=$((a2-a1))
echo "Time required=$diff"
