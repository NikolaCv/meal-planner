#!/bin/bash

cp "$1" backup_"$1"
sort -o "$1" -u "$1"
sed -i -E 's/\s[0-9]+[a-z]+//' "$1"
vim -nEs +'%s/č/c/g' +wq "$1"
vim -nEs +'%s/ć/c/g' +wq "$1"
vim -nEs +'%s/š/s/g' +wq "$1"
vim -nEs +'%s/ž/z/g' +wq "$1"
vim -nEs +'%s/đ/dj/g' +wq "$1"
