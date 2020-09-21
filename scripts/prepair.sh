echo dirname:
read NAME
mkdir $NAME
cp alld.sh ./$NAME/alld.sh
cd ./$NAME
echo filenames:
read FILES
echo $FILES | xargs mkdir 
echo $FILES | xargs -n 1 sh -c 'cp ../ghub/kpro/library/preparation.cpp ./$0/$0.cpp && cp ../compile.sh ./$0/compile.sh && code ./$0/$0.cpp'
