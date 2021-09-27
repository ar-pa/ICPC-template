for ((i = 1; i <= 10000; i++)); do
  echo $i -------
  cmake-build-debug/gen 5 $i >in
  cmake-build-debug/code <in >out
  #  cmake-build-debug/naive <in >out2
  #  diff out out2 >/dev/null
  if [ $? != 0 ]; then
    echo WA
    exit
  fi
done
