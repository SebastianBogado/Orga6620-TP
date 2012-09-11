OUT=tests/time.out

cd src
make

echo "Quicksort" > $OUT
echo "1kb" >> $OUT
echo "ordenado" >> $OUT
/usr/bin/time -p -a -o $OUT ./tp0 -q tests/1kb_rand.test > a.out
echo "orden invertido" >> $OUT
/usr/bin/time -p -a -o $OUT ./tp0 -q tests/1kb_inv.test > a.out
echo "aleatorio" >> $OUT
/usr/bin/time -p -a -o $OUT ./tp0 -q tests/1kb_sorted.test > a.out

echo "8kb" >> $OUT
echo "ordenado" >> $OUT
/usr/bin/time -p -a -o $OUT ./tp0 -q tests/8kb_rand.test > a.out
echo "orden invertido" >> $OUT
/usr/bin/time -p -a -o $OUT ./tp0 -q tests/8kb_inv.test > a.out
echo "aleatorio" >> $OUT
/usr/bin/time -p -a -o $OUT ./tp0 -q tests/8kb_sorted.test > a.out

echo "16kb" >> $OUT
echo "ordenado" >> $OUT
/usr/bin/time -p -a -o $OUT ./tp0 -q tests/16kb_rand.test > a.out
echo "orden invertido" >> $OUT
/usr/bin/time -p -a -o $OUT ./tp0 -q tests/16kb_inv.test > a.out
echo "aleatorio" >> $OUT
/usr/bin/time -p -a -o $OUT ./tp0 -q tests/16kb_sorted.test > a.out

echo "Stoogesort" >> $OUT
echo "1kb" >> $OUT
echo "ordenado" >> $OUT
/usr/bin/time -p -a -o $OUT ./tp0 -s tests/1kb_rand.test > a.out
echo "orden invertido" >> $OUT
/usr/bin/time -p -a -o $OUT ./tp0 -s tests/1kb_inv.test > a.out
echo "aleatorio" >> $OUT
/usr/bin/time -p -a -o $OUT ./tp0 -s tests/1kb_sorted.test > a.out

echo "8kb" >> $OUT
echo "ordenado" >> $OUT
/usr/bin/time -p -a -o $OUT ./tp0 -s tests/8kb_rand.test > a.outt
echo "orden invertido" >> $OUT
/usr/bin/time -p -a -o $OUT ./tp0 -s tests/8kb_inv.test > a.out
echo "aleatorio" >> $OUT
/usr/bin/time -p -a -o $OUT ./tp0 -s tests/8kb_sorted.test > a.out

echo "16kb" >> $OUT
echo "ordenado" >> $OUT
/usr/bin/time -p -a -o $OUT ./tp0 -s tests/16kb_rand.test > a.out
echo "orden invertido" >> $OUT
/usr/bin/time -p -a -o $OUT ./tp0 -s tests/16kb_inv.test > a.out
echo "aleatorio" >> $OUT
/usr/bin/time -p -a -o $OUT ./tp0 -s tests/16kb_sorted.test > a.out


rm a.out
