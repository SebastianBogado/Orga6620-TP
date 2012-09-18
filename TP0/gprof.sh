cd src
make gprof
./tp0 -q tests/16kb_rand.test
gprof ./tp0 -q tests/16kb_rand.test > qsort_.out

