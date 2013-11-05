TEST=$1

tail -n+2 $TEST.in > gp-test.in
head -2 $TEST.in | tail -1 >> gp-test.in

./lab4 < $TEST.in > gp-test-full.out
rm -rf $TEST\_history
mkdir $TEST\_history
lines=`cat gp-test-full.out | wc -l`
triangles=$(($lines/3))

for i in `seq 1 $triangles`; do 
  head -n $(($i * 3)) gp-test-full.out > gp-test.out
  gnuplot < display2.gnuplot
  filename=`printf %03d $i`
  mv gp-test.png $TEST\_history/$filename.png
done

convert -delay 100 -loop 0 $TEST\_history/*.png $TEST\_history/history.gif

rm gp-test.out
rm gp-test-full.out
rm gp-test.in