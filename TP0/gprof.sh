cd src
make gprof
./tp0 -q tests/1mb.txt
gprof tp0 > qsort_gprof.out

