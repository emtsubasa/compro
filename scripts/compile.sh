echo filename:
read NAME
g++ -std=c++17 $NAME.cpp -O2 -I . -fsplit-stack
oj t -t 3 --diff