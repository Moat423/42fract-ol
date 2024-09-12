# 42fract-ol
Beautiful fractal generator

usage:
git clone git@github.com:Moat423/42fract-ol.git fractol
cd fractol
make


options:
now you can execute the program and add after it which fractol you want to have it display.

./fractol mandelbrot
./fractol julia
./fractol tricorn

extended options:
You may add input parameters to tweak the complex number to generate a different julia set.

example:
./fractol "julia" "-0.79" "0.15"

controls:

move with:
up: w
right: a
left: d
down: s

change colourscheme: c
increate max iterations (depth): PgUp
decrease max iterations (depth): PgDn
close: ESC
