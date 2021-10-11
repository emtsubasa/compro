echo filename:
read NAME
g++ -std=c++17 $NAME.cpp -O2 -I . -fsplit-stack
# g++ -std=c++17 $NAME.cpp -O2 -I . -fsplit-stack -fsanitize=address -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC
oj t -t 3 --diff