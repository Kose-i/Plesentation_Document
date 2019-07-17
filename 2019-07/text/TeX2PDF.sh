#!/bin/sh

if [ $# != 1 ];then
  echo "Error(argc != 2)"
  exit 1
fi

if [ ${1} = *.tex ];then
  TARGET=$(echo ${1} | sed -e "s/.\{4\}$//")
else
  TARGET=${1}
fi
echo $TARGET
ls | grep $TARGET.tex


if [ $? = 0 ];then
  platex $TARGET.tex
  if [ $? = 0 ];then
    dvipdfmx $TARGET.dvi
    gio open $TARGET.pdf
  else
    echo "Fail to `platex $TARGET`"
  fi
else
  echo "platex error"
fi
