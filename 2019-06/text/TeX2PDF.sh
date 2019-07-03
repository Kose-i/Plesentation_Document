#!/bin/sh

platex ${1}.tex

if [ $?==0 ];then
  dvipdfmx ${1}.dvi
  gio open ${1}.pdf
else
  echo "platex error"
fi

