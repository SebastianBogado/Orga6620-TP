#!/bin/bash


if [ $# -lt 2 ]; then
        echo "fullCollect <repeticiones> [EJECUTABLE/S...]" 
        exit 1
fi

if [[ ! ("$1" =~ ^[0-9]+$) || "$1" -eq 0 ]]; then
        echo "Indique la cantidad de corridas a realizar"
        echo "fullCollect <repeticiones> [EJECUTABLE/S...]" 
        exit 1
fi

corridas=$1
shift

outFull="outFull.fullCollect"
outSmall="outSmall.fullCollect"

`> $outFull`
`> $outSmall`
 
echo "Procesando:"
for file in $@
do
	echo "  $file"
	./cacheCollect.sh $corridas $file >> /dev/null
	cat "cache/outSmall.cacheCollect" >> $outSmall
	./timeCollect.sh $corridas $file >> /dev/null
	cat "time/outSmall.timeCollect" >> $outSmall
	./gprofCollect.sh $file >> /dev/null
	cat "gprof/outSmall.gprofCollect" >> $outSmall
	

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

