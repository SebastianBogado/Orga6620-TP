#!/bin/bash

# $1 = sed script
# $2 = nombre de aquello que se busca promedio
promedio () {
	acum=0
	for val in `sed <$temp -n "$1"`
	do
		acum=$(echo "scale=2; $acum + $val" | bc)
	done
	
	promedio=$( echo "scale=2; $acum / $corridas" | bc)
	
	echo "  $2: $promedio" >> $temp
	echo -ne "$2: $promedio; " >> $outSmall
}

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

outFull="outFull.dataCollect"
outSmall="outSmall.dataCollect"
temp="temp.dataCollect"
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
		echo -e " Corrida $i\n" >> $temp

		/usr/bin/time -pao $temp valgrind --tool=cachegrind --D1=256,2,64 "./$file" WatorOut.txt 2>&1 | grep ".*D.*" | sed "s/==[0-9]*==/   /g" >> $temp  
		
		echo -ne " Fin simulacion: $(tail -n 1 WatorOut.txt) \n" >> $temp
		
		i=$(( $i + 1 ))
	done

	echo -e "\n Promedios:" >> $temp	
	echo -ne "$file - Promedios:\n\t" >> $outSmall
	
	promedio 's/\s\+D1  miss rate:\s\+\([0-9]\+\.[0-9]\+\)%.\+/\1 /g p' 'MR'
	echo " time -> " >> $temp
	echo -ne "\n\ttime -> " >> $outSmall
	promedio 's/^real \([0-9]\+\.[0-9]\+\)$/\1 /g p' 'r'
	promedio 's/^user \([0-9]\+\.[0-9]\+\)$/\1 /g p' 'u'
	promedio 's/^sys \([0-9]\+\.[0-9]\+\)$/\1 /g p' 's'

	echo -e "\n" >> $temp
	echo -e "\n" >> $outSmall

	cat $temp >> $outFull
done

rm cachegrind*
rm $temp

clear

cat $outSmall

exit 0


