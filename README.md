# 3d_wire_framing
A simple program which reads (in a text file) a map of altitudes and produces an interactive 3d wire frame

This is the first project of the graphics branch of 42.
It is built with library 'minilibx' in C, which includes very basic graphics functions such as putting a pixel on screen.

## Features
* Simple file format definition (array of space-separated integers)
* 3D rotations with the mouse
* Camera controls (zoom, translate)
* Color gradients controled by keyboard (separate RGB adjustments)

## Compiling and running
Run `make`. An executable will compile. Currently only tested on OS X.

Run with `./fdf [map]`. A bunch of sample maps are provided in the `test maps` directory.

![alt text](https://github.com/conanwu777/3d_wire_framing/blob/master/img1.png)
![alt text](https://github.com/conanwu777/3d_wire_framing/blob/master/img2.png)
![alt text](https://github.com/conanwu777/3d_wire_framing/blob/master/img3.png)
![alt text](https://github.com/conanwu777/3d_wire_framing/blob/master/img4.png)
![alt text](https://github.com/conanwu777/3d_wire_framing/blob/master/img5.png)
