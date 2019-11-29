#!/bin/sh

[ -f "${1}.c" ] || exit

rm -f "${1}" "${1}.o"

gcc -Wall -o "${1}" "${1}.c"


if [ $(echo $?) = "0" ]
then
  program=$1
  shift
  ./$program $@
else
  echo "COMPILATION ERROR"
fi
