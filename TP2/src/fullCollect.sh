#!/bin/bash

if [ $# -lt 2 ]; then
	echo "fullCollect [repeticiones] <Ejecutable/s>"
	exit 1
fi

if [ $1 -lt 0 ]; then
	echo "mal repeticiones"
	exit 1
fi

corridas=$1
shift

outFull="outFull.fullCollect"
outSmall="outSmall.fullCollect"

`> $outFull`
`>$outSmall`
 
echo "Procesando:"
for file in $@
do
	echo "  $file"
	./cacheCollect.sh $corridas $file >> $outSmall
	./timeCollect.sh $corridas $file >> $outSmall
	./gprofCollect.sh $file >> $outSmall
	
	cat "cache/outFull.cacheCollect" >> $outFull
	echo -ne "====================\n" >> $outFull
	cat "time/outFull.timeCollect" >> $outFull
	echo -ne "====================\n" >> $outFull
	cat "gprof/outFull.gprofCollect" >> $outFull
	echo -ne "====================\n" >> $outFull

done


clear

cat $outSmall
exit 0

