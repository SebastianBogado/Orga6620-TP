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

outFull="cache/outFull.cacheCollect"
outSmall="cache/outSmall.cacheCollect"
temp="temp.cacheCollect"
`> WatorOut.txt ` 
`> $outFull`
`>$outSmall`
`> $temp`

# echo -n "Procesando:"

for file in $@
do
#	echo -ne "\n $file "
	echo "$file" > $temp
	i=0

	while [ $i -lt $corridas ] 
	do
#		echo -n "."
		echo " Corrida $i" >> $temp

		valgrind --tool=cachegrind --D1=256,2,64 "./$file" WatorOut.txt 2>&1 | grep ".*D.*" | sed "s/==[0-9]*==/   /g" >> $temp

		echo -ne " Fin simulacion: $(tail -n 1 WatorOut.txt) \n" >> $temp

		i=$(( $i + 1 ))
	done
	max=0
	min=100000
	MR=0
	for rate in `sed <$temp -n 's/\s\+D1  miss rate:\s\+\([0-9]\+\.[0-9]\+\)%.\+/\1 /g p'`
	do
	        if [ $rate -gt $max ]; then
                        max=$rate
                fi
                
                if [ $rate -lt $min ]; then
                        min=$rate
                fi

		MR=$(echo "scale=2; $MR + $rate" | bc)
	done
	
	promedio=$( echo "scale=2; $MR / $corridas" | bc)

	echo -e " Promedio: $promedio\n\n" >> $temp
	cat $temp >> $outFull

	echo -ne "$file - Promedio MR: $promedio \n
		  Max: $max\n
		  Min: $min\n\n" >> $outSmall
done

rm cachegrind*
rm $temp

#clear

cat $outSmall

exit 0
