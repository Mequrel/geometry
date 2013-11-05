set terminal png
set output 'gp-test.png'
set pointsize 1
set noborder
plot 'gp-test.in' with linespoints, 'gp-test.out' u 1:2:($3-$1):($4-$2) notitle with vectors
