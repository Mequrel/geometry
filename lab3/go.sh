TEST="test_big"
ALGO="brute"

tail -n+2 $TEST.in > gp-test.in
./lab3 $ALGO < $TEST.in > $TEST$ALGO.out
tail -n+2 $TEST$ALGO.out > gp-test.out
gnuplot < display.gnuplot
mv gp-test.png $TEST$ALGO.png
