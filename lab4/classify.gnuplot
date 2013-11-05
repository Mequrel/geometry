set terminal png
set output 'gp-test.png'
set noborder
unset key

set label 1 'begin' at graph 0.8,0.8 tc rgb 'purple'
set label 2 'end' at graph 0.8,0.75 tc rgb 'blue'
set label 3 'merge' at graph 0.8,0.7 tc rgb 'red'
set label 4 'split' at graph 0.8,0.65 tc rgb 'green'
set label 5 'regular' at graph 0.8,0.6 tc rgb 'aquamarine'
plot 'gp-test.in' with lines, 'gp-test.out' using 1:2:3 with points lc variable pt 7 ps 5
