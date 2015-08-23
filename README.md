 Youtube Playlist of Toobit Video Documentation
https://www.youtube.com/playlist?list=PLmSUTHzWYMaNGqxUQunqIu3TbsDL2QnI-

Primary goals so far are

Target : Small cheap ARM systems

Code : Semi-Optimized C Prototype

Application : Server based cellular automation platform

Fields : Visual Effects, Music Visualization, Particle Effects, "Living Server Based Textures' 

Toobit is a Project with documented development.

Video documentation is regularity done and frequent version backups are made as well.

This way the project is either useful as a framework and as a reference for the design of such a platform from scratch.

Features to date:

-function pointer based automation
(just design the physics as a function and pass that function into the core)

-"Safe" pointer based pre-processing
(faster access to neighborhood and no need to worry about boundaries)

-Server (Can handle HTTP request)

-Thin Terminal Client (Can deliver and then service a HTML5/Javascript/etc.. client)

-server raw output dump and client injection

-Threading core(lock stepped core of 3 threads to help max out cpu usage..[adjustable thread count coming..])

-Some basics like screen print, speed test, init functions etc..

Future plan.. too many to count but some are
-Mesh networking to allow them to join and sync into larger universes.
-serial node based processing (out from 1 is input into 2.... output 2 into input 3 etc..)
-Visual effects, music viz
-Unreal, Unity, Blender, etc.. pluigin to stream the output into the 3d world as textures, maps, particles, etc..
-so much more.. with little arm systems you could build complex networks of these and do all kinds of i/o :)


 Youtube Playlist of Toobit Video Documentation
https://www.youtube.com/playlist?list=PLmSUTHzWYMaNGqxUQunqIu3TbsDL2QnI-

//-----------------------------
// TOOBIT v0.5
// 2d bit space simulation system
//
// Toobit is part software project, part experiment, part educational material
// Goals
//  -Framework : develop an optimed platform for "complex digital virtual physics systems"
//  -Study : experiment with said systems and seek shiny stuff
//  -Educational Media : document the development on youtube with explaination
//
// "Complex digital virtual physics systems" means systems that have common rules applied 
//   constantly each frame of time to every point of space. Conway's Game of Life is a
//   well known example. Many much more complex systems have been devised and documented.
//   The goal here is not to design one, but explore the developement of an optimized
//   "virtual physics design framework".
//
// I play with alot of embeded ARM systems these days, so I want fast, small and tight
//               you have a dirty mind
//
// Just simple C, it's what I am best at and what seems to be more rare the days.
//
// A major focus here is optimization. This game is all about how big you can make space,
//   how complex the rules can be, and how fast you can run time. 
//
// This will manifest itself in several visible ways
//  -pointers pointers pointers!
//  -Avoidance of restrictive elements
//  -Heavy use of preprocessor
//  -Recompile required for many config changes
//
// *note* threading is planned, but there is much else that must be designed first
//
// Youtube Playlist of Toobit Video Documentation
//  https://www.youtube.com/playlist?list=PLmSUTHzWYMaNGqxUQunqIu3TbsDL2QnI-
