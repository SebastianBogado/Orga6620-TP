cd src
make gprof
./tp0 -s tests/1mb.txt
gprof tp0 > ssort_gprof.out

