TEST=$1

./lab4 < $TEST.in > gp-test.out
gnuplot < display2.gnuplot
mv gp-test.png $TEST.png
rm gp-test.out
