#!/bin/bash
g++ -std=c++17 gen.cpp -o gen
g++ -std=c++17 doing.cpp -o my
g++ -std=c++17 naive.cpp -o sol

echo 'All codes compiled!'

./gen > in && ./my < in > out1 && ./sol < in > out2
declare -i i=0
DIFF=$(diff out1 out2)

while [ $? -eq 0 ] 
do
	echo 'Test #'$i passed!
	i=$((i+1))
    ./gen > in && ./my < in > out1 && ./sol < in > out2
	DIFF=$(diff out1 out2)
done

echo $DIFF
echo "Found a counter test! :)"
