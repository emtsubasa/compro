echo url:
read URL
echo file:
read FILES
echo $FILES | xargs -n 1 sh -c 'cd $1 && oj d $0$1 && cd ..' $URL