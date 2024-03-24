set terminal gif size 1000,800 animate delay 20
set output 'animate3dFromInstructionLines.gif'
set xrange [0:1]
set yrange [0:0.5]
set zrange [-0.01:0.01]
stats 'output.txt' name 'A'
do for [i=0:int(A_blocks-1)] { splot 'output.txt' index i using 1:2:3 with lines title 'Step = '.(i+1) }
