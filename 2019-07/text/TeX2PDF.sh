#!/bin/sh

if [ $#!=2 ];then
  echo "Error(argc != 2)"
  exit 1
fi
ls | grep ${1}.tex


if [ $?==0 ];then
  platex ${1}.tex
  if [$? ==0];then
    dvipdfmx ${1}.dvi
    gio open ${1}.pdf
  fi
else
  echo "platex error"
fi

