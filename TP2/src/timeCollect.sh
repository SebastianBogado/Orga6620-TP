#!/bin/bash

if [ $# -lt 2 ]; then
	echo "dataCollect <repeticiones> [EJECUTABLE/S...]" 
	exit 1
fi

if [ $1 -lt 1 ]; then
	echo "Boludo, el nro de  corridas "
	exit 1
fi

corridas=$1
shift

outFull="time/outFull.timeCollect"
outSmall="time/outSmall.timeCollect"
temp="temp.timeCollect"
`> WatorOut.txt ` 
`> $outFull`
`>$outSmall`
`> $temp`

echo -n "Procesando:"

for file in $@
do
	echo -ne "\n $file "
	echo "$file" > $temp
	i=0
	
	while [ $i -lt $corridas ] 
	do
		echo -n "."
		echo " Corrida $i" >> $temp

		(time "./$file" WatorOut.txt) 2>&1 | grep "real.*" >> $temp
		
		echo -ne " Fin simulacion: $(tail -n 1 WatorOut.txt) \n" >> $temp
		
		i=$(( $i + 1 ))
	done
	
	medTime=0
	
	for rate in `sed <$temp -n 's/[^0-9]\+0m\(.*\)s/\1/g p'`
	do
		medTime=$(echo "scale=4; $medTime + $rate" | bc)
	done
	
	promedio=$( echo "scale=4; $medTime / $corridas" | bc)
		
	echo -e " Promedio real time: $promedio \n\n" >> $temp
	cat $temp >> $outFull

	echo -ne "\n\n$file - Promedio real time: $promedio \n\n" >> $outSmall
done

rm $temp

#clear

cat $outSmall

exit 0


