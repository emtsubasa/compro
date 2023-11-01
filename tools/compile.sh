echo filename:
read NAME
g++ -std=c++17 $NAME.cpp -O2 -I .
oj t -t 3 --diff