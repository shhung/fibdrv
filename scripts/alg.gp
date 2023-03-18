set title "Fibonacci Running Time"
set xlabel "Fibonacci(n)"
set ylabel "Time(ns)"
set terminal png font " Times_New_Roman,12 "
set output "alg_isolcpu.png"
set xtics 0 ,5 ,100
set key left 

plot \
"../fib_sequence" using 1:2 with linespoints linewidth 2 title "sequence", \
"../fib_fast_double" using 1:2 with linespoints linewidth 2 title "fast doubling", \
"../fib_fast_double_iter" using 1:2 with linespoints linewidth 2 title "fast doubling iter", \