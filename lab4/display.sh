TEST=$1

tail -n+2 $TEST.in > gp-test.in
head -2 $TEST.in | tail -1 >> gp-test.in
gnuplot < display.gnuplot
mv gp-test.png $TEST-display.png
rm gp-test.in
