# fundations.Game-Engine-Architecture


## Progress


## Index

- Fundations
  - Introduction
  - Tools of the Trade
  - Fundamentals of Software Engineering for Games
  - Parallelism and Concurrent Programming
  - 3D Math for Games
- Low-Level Engine Systems
  - Engine Support Systems
  - Resources and the File System
  - The Game Loop and Real-Time Simulation
  - Human Interface Devices
  - Tools for Debugging and Development
- Graphics, Motion and Sound
  - The Rendering Engine
  - Animation Systems
  - Collision and Rigid Body Dynamics
  - Audio
  - Gameplay
  - Introduction to Gameplay Systems
- Gameplay
  - Introduction to Gameplay Systems
  - Runtime Gameplay Foundation Systems

### Fundations

a solid C++ fundations is obtained from [46][36][37]

In this book you will learn:
- how real industrial-strength production game engines are architected
- how game development teams rea organized and work in the real world
- which major subsystems and design patterns appear again and again in virtually every game engine
- the typical requirements for each major subsystem
- which subsystems are genre- or game-agnostic, and which ones are typically designed explicitly for specific genre or game
- where the engine normally ends and game begins

Structure of a typical game development team
- runtime programmer
- tools programmer
- TD, CTO

Concept Artists, 3D modelers, Texture Artists, Lighting artists, Animators, Motion capture actors, Sound designers, Voice actors

1.4.8 Virtual, Augmented and Mixed Reality
1.5 Game Engine Survey
1.6.3 Operating System

SDKs

DirectX, OpenGL, Vulkan, etc
Havok, PhysX, ODE
Boost
Folly
Kynapse
Granny, Havok, Animation, etc.
Euphoria

- Data Structures and Algorithms
  - boost
  - folly
  - loki
- Graphics
  - Glide
  - OpenGL
  - DirectX
  - libgcm: PlayStation 3
  - Edge: Naughty Dog and Sony for PS3
  - Vulkan
- Collision and Physics
  - Havok
  - PhysX
  - Open Dynamic Engine ODE
- Character Animation
  - Granny
  - Havok Animation
  - Orbis Anim

1.6.6 Core Systems
Assertions: lines of error-checking code -> section 3.2.3.3
Memory management:
Math Library
Custom data structure and algorithms

Parser, Unit Testing, Curves & Surfaces Library, String & Hash, Debug, Locolization Services, Asyn File IO, Movie Player

1.6.7 Resource Manager
1.6.8 Rendering Engine

For very small game worlds, a simple frustum cull (i.e. removing objects that the camera cannot 'see') is probably all that is required. For larger game worlds, a more advanced spatial subdivision data structure might be used to improve rendering efficiency by allowing the potentially visible set (PVS) of objects to be determined very quickly.

Spatial subdivisiions can take many forms, includign a binary space partitioining tree, a quadtree, an octree, a kdtree or a sphere hierarchy ---> Scene Graph.

Front-End
- heads-up display (HUD)
- in-game menus, a console and/or other development tools
- in-game GUI

1.6.9 Profiling and Debugging Tools
- Intels VTune
- IBM Quantify and Purify
- Insure++
- Valgrind

However, most game engines also incorporate a suite of custom profiling and debugging tools.

Ragdoll Physics: Collision & Physics  Forces & Constraints Ray/Shape Casting Rigid Bodies, Phantoms, Shapes/Collidables

1.6.13 Audio

Microsoft XAudio2
SoundRIOT
Sound Forge

1.6.14 Networking

1.6.15 Gameplay Foundations
- Static World Elements
- Dynamic Game Object Model: building roads, terrains, player character & non-player character
- Real-Time Agent-Based Simulation
- Event/Messaging System
- World Loading/Streaming
- Scripting System
- High-Level Game Flow System / FSM

1.6.16 Game-Specific Subsystems

On top of the gameplay foundation layer and the other low-level engine components.

1.7 Tools and the Assets Pipeline
- DDC: digit content creation
Maya, 3DSMAX, Photoshop, Houdini, Sound Forge

1.7.2 The Asset Conditioning Pipeline
The data formats used by digital content creation applications are rarely suitable for direct use in game.
- DCC application's in-memory model is much larger: e.g. Maya stores directed ascyclic graph of scene nodes and history of all edits
- DCC application's file format is too slow to read at runtime

therefore, the data produced by DCC app is usually exported to a more accessible standardized format, XML, JSON or simply binary formats
-> asset conditioning pipeline (ACP)

1.7.2.1 3D Model/Mesh Data
A mesh is complex shape composed of triangles and vertices.

Brush Geometry: a collection of convex huls.
Skeletal Animation Data: A special kind of mesh that is bound to a skeltal hierarchy for the purposes of articulated animation

Audio Data: in mono, sterio, Wave files .wav, .vag for PS

1.7.3 The World Editor
- there are no commertcially available game world editors
- Quake technolgogy, Hammer, UnreaEd, Sandbox
1.7.4 Resource Database
every asset also carries with it a great deal of metadata.

- unique id
- .ma file paht
- frame range

see 7.2.1.3

## Chapter 2  Tools of the Trade

2.1 Version Control
2.2 Compilers, Linkers and IDE
2.3 Profiling Tools
Games are typically high-performance real-time programs. As such, game engine programmers are always looking for ways to speed up their code.
see Chapter 4

Pareto Principle

Intel's VTune is the gold standard in statistical profilers for Windows machines employing Intel Pentium processors.

https://www.intel.com/content/www/us/en/developer/tools/oneapi/vtune-profiler.html#gs.cbuyrz

purify toolkit

## Chapter 3: Fundamentals of Software Engineering for Games

### 3.1 C++ Review and best practise

3.1.1 Brief Review of Object-Oriented Programming
oop[7]and cpp[46]and[36]

Classes and Objects
- A class is a specification describing how individual instances of the class
- Encapsulation: means an object presents only a limited interface to the outside world,
- Inheritance: allows new classes to be defined as extensions to preexisting classes.

We can draw diagrams of calss hierarchies using the convensions defined by UML. A rectangle represents a class and a arrow with hollow triangular head represents inheritance.

- Multiple Inheritance: MI, meaning that a class can have more than one parent class. -> deadly diamond, in C++ virtual inheritance allows one to avoid this doubling of the grandparent's data.

Such classes are sometimes called mix-in classes.

3.1.1.4 Polymorphism

allows a collection of objects of different types to be manipulated through a single common interface.

For example, a 2D painting program might be given a list of various shapes to draw on a screen. But each shape has its own drawing method.

3.1.1.6 Design Patterns
- Singleton
- Iterator
- Abstract Factory

The game industry has its own set of design patterns for addressing problems in every realm from rendering to collision to animation to audio.

Janitors and RAII

resource acquisition is initialization RAII

At Naughty Dog, we call such class janitors because they clean up after you.

### 3.2 Catching and Handling Errors

### 3.3 Data, Code, and Memory Layout

3.3.7.2 Memory Layout of C++ Classes
inheritance and virtual functions make C++ classes a little different from C structures.

When class B inherits from class A, B's data members simply appear immediately after A's memory.

Each new derived class simply tacks its data member on at the end.

alignment requirements may introduce padding.

If a class contains or inherites one more virtual functions, then four additional bytes (or eight bytes if the target hardware is 64bit) are added to the class layout, typically at the very beginning of the class' layout.

virtual table pointer or vpointer.

they contain a pointer to a data structure known as the virtual function table or vtable.

pure virtual means it does not provide implementations and the derived class has to override it if it want to be instantiable.

each class has its own vtable pointer to its own vfunction implementation.


### 3.4 Computer Composition

### 3.5 Memory Architectures

## Chapter 4: Parrallelism and Concurrent Programming

### 4.2

4.2.2 Latency versus Troughput

## Chapter 5: 3D Math for games

