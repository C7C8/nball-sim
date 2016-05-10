#NBall-Sim
Remnants of an old (er...) research project, it's supposed to simulate gravity
in a two-dimensional environment using Verlet integration. The code is of
rather poor quality as its development was rather... rushed. It has a LOT of 
things in it I wouldn't do normally, like having the entire source be in one
file or using the awful "Hydra Engine" that I wrote years ago so I could screw
around with graphics a little bit.

##Features

* N-body gravity simulation that (mostly) conserves energy.
* Configurable (in the source) for various situations, including collisions (elastic + inlastic) and drag.
* "Science mode" that lets the simulation play until one body controls x% of the mass, then continues for repeated trials over time.
* A variable gravitational "constant", set by default to 1000 N m^2 / kg^2.

##Controls

* LMB - Place a ball. Click and hold to set speed and direction.
* C - clear all objects
* F - fullscreen (experimental, won't scale to your monitor)
* E - turn colliding edges on or off
* S - kill all motion
* W - increase ball mass, size increases with square root of mass
* Q - decrease ball mass, size decreases with square root of mass
* R - set random mass for ball in-placing
* Z - toggle center of mass readout (the little red dot)
* T - toggle trails
* p - toggle persistant (infinitely long) trails
* o - randomly distribute a set number of balls across the screen
* l - science mode only, skips the current trial and moves on to the next one.

##Compiling
I'm working on fixing it so it will compile using autotools, which it does...
it just crashes after loading the sprite it's supposed to. If you want to try
and compile it, you'll need the SDL2 and SLD2-image development libraries, as
well as the following flags:

    -lSLD2 -lSDL2_image -std=c++1y

Good luck.
