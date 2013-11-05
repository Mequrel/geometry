TEST=$1

tail -n+2 $TEST.in > gp-test.in
head -2 $TEST.in | tail -1 >> gp-test.in

./classify < $TEST.in > gp-test.out

gnuplot < classify.gnuplot

mv gp-test.png $TEST\.classication.png
rm gp-test.in
rm gp-test.out
