set terminal png
set output 'gp-test.png'
# 
set pointsize 1
plot 'gp-test.out' u 9:10 linecolor rgb "blue" with circles, 'gp-test.in' u 1:2:($3-$1):($4-$2) notitle with vectors
