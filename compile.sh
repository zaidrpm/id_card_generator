#!/bin/bash
a1=$(date +%s%N | cut -b1-13)
a2=$(date +%s)
#//clear
#cd /usr/include
echo '.'
echo '.'
echo '.'
g++ -ggdb /home/zaid/Projects/c++/open.cpp -o /home/zaid/Projects/c++/open ` pkg-config --cflags --libs opencv`
cp /home/zaid/Projects/c++/open.cpp "/home/zaid/Projects/c++/backup/$a2.cpp"
a2=$(date +%s%N | cut -b1-13)
diff=$((a2-a1))
echo "Time required=$diff"
