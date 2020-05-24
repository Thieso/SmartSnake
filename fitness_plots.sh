#!/bin/sh

# plots of the fitness data created by the main script using gnuplot

# plot of best fitness value over all generations
gnuplot -persist <<-EOFMarker
    set title "Best Fitness" font ",14" textcolor rgbcolor "royalblue"
    set xlabel "Generation" font ",10" textcolor rgbcolor "royalblue"
    show xlabel
    plot "fitness" using 2 title 'Best Fitness' with lines
EOFMarker

# plot of sum of fitness values for each generation
gnuplot -persist <<-EOFMarker
    set title "Fitness Sum" font ",14" textcolor rgbcolor "royalblue"
    set xlabel "Generation" font ",10" textcolor rgbcolor "royalblue"
    show xlabel
    plot "fitness" using 3 title 'Fitness Sum' with lines
EOFMarker

