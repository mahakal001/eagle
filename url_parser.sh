#!/bin/bash
echo $1

grep -Eoi '<a [^>]+>' $1 | grep -Eo 'href="[^\"]+"' |\
   grep -v webcache |\
   sed '/url?q=/!d;s//&\n/;s/.*\n//;:a;/&amp/bb;$!{n;ba};:b;s//\n&/;P;D' |\
   tr '\n' ',' > $1
