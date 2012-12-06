#!/bin/bash

if [ $# -lt 1 ]; then
	echo "gprofCollect [EJECUTABLE/S..]" 
	exit 1
fi


outFull="gprof/outFull.gprofCollect"
outSmall="gprof/outSmall.gprofCollect"
outLatex="gprof/latexOut.gprofCollect"
temp="temp.gprofCollect"
`> WatorOut.txt ` 
`> $outFull`
`> $outSmall`
`> $outLatex`
`> $temp`


echo -n "Procesando:"

for file in $@
do
	echo -ne "\n $file "

	exe="${file}_gprof"
	`gcc -p "$file.c" -o "$exe"`

	echo "$file" > $temp
	echo "" >> $temp

	"./$exe" WatorOut.txt >/dev/null

	gprof "./$exe" >> $temp

	echo -ne "\n\nFin simulacion: $(tail -n 1 WatorOut.txt) \n" >> $temp
	
	cat $temp >> $outFull

	echo -ne "\n\n$file - gprof Flat Profile \n" >> $outSmall
	tail -n +6 $temp | head -n 15  >> $outSmall	
	echo -ne "\n\nFin simulacion: $(tail -n 1 WatorOut.txt) \n" >>$outSmall

	./gprof/gprofToTex.sh $temp >> $outLatex
done

rm $temp
rm *_gprof
#clear

cat $outSmall

exit 0


