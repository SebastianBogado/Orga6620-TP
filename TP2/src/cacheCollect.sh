#!/bin/bash

if [ $# -lt 2 ]; then
	echo "cacheCollect <repeticiones> [EJECUTABLE/S...]" 
	exit 1
fi


if [[ ! ("$1" =~ ^[0-9]+$) || "$1" -eq 0 ]]; then
        echo "Indique la cantidad de corridas a realizar"
        echo "cacheCollect <repeticiones> [EJECUTABLE/S...]" 
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

		valgrind --tool=cachegrind --D1=256,2,64 "./$file" WatorOut.txt 2>&1 | grep ".*D.*" | sed "s/==[0-9]*==/   /g" >> $temp

		echo -ne " Fin simulacion: $(tail -n 1 WatorOut.txt) \n" >> $temp

		i=$(( $i + 1 ))
	done
	max=0
	min=100000
	MR=0
	for rate in `sed <$temp -n 's/\s\+D1  miss rate:\s\+\([0-9]\+\.[0-9]\+\)%.\+/\1 /g p'`
	do
	        if [  $(echo "scale=5; $max < $rate" | bc) -eq 1 ]; then
                        max=$rate
                fi
                
                if [  $(echo "scale=5; $min > $rate" | bc) -eq 1 ]; then
                        min=$rate
                fi

		MR=$(echo "scale=3; $MR + $rate" | bc)
	done
	
	promedio=$( echo "scale=3; $MR / $corridas" | bc)

	echo -e " Promedio: $promedio\n\n" >> $temp
	cat $temp >> $outFull

	echo -ne "\n\n$file - Promedio MR: $promedio \n
		  Max: $max\n
		  Min: $min\n" >> $outSmall
done

rm cachegrind*
rm $temp

#clear

cat $outSmall

exit 0
