
if [ $# -lt 1 ]
then
	echo "Uso: <nombre de archivo gprof>";
	exit 1;
fi



N='\( *[0-9][0-9]*\)' 		   # Campo numérico
F='\( *[0-9]\{1,2\}\.[0-9][0-9]\)' # Campo de punto flotante
S='\( *[A-Za-z%\/_][A-Za-z%\/_]*\)'  # String

head -n 5 $1
sed -n '6p'    $1 | sed "s/^$S$S$S$S$S/\1 \&\2 \&\3 \&   \&\4 \&\5 \&    \& \\\\\\\/g"
sed -n '7p'    $1 | sed "s/^$S$S$S$S$S$S$S/\1 \&\2 \&\3 \&\4 \&\5 \& \6 \& \7 \\\\\\\ \\\hline/g"
sed -n '8,20p' $1 | sed "s/^$F$F$F$N$F$F$S/\1 \&\2 \&\3 \&\4 \&\5 \& \6 \& \7 \\\\\\\ \\\hline/g"

