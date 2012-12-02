#!/bin/bash

if [ $# -lt 1 ]; then
	echo "dataCollect <repeticiones> [FUENTE/S...]" 
	exit 1
fi


outFull="gprof/outFull.gprofCollect"
outSmall="gprof/outSmall.gprofCollect"
temp="temp.gprofCollect"
`> WatorOut.txt ` 
`> $outFull`
`>$outSmall`
`> $temp`


#echo -n "Procesando:"

for file in $@
do
#	echo -ne "\n $file "

	exe="${file}_gprof"
	`gcc -pg "$file.c" -o "$exe"`

	echo "$file" > $temp
	echo "" >> $temp

	"./$exe" WatorOut.txt >/dev/null

	gprof "./$exe" >> $temp

	echo -ne "\n\nFin simulacion: $(tail -n 1 WatorOut.txt) \n" >> $temp
	
	cat $temp >> $outFull

	echo -ne "$file  \n" >> $outSmall
	tail -n +6 $temp | head -n 15  >> $outSmall	
	echo -e "\n"
	echo -ne "\n\nFin simulacion: $(tail -n 1 WatorOut.txt) \n" >>$outSmall 
done

rm $temp
rm *_gprof
#clear

cat $outSmall

exit 0


