# Dependencies.CUDA


## CUDA by Examples: An Introductioni to General Purpose GPU Programming

- Chapter 1:  WHY CUDA? WHY NOW?
- Chapter 2: Getting Started
- Chapter 3: Introduction To CUDA C
- Chapter 4: Parallel Programming in CUDA C
- Chapter 5: Thread Cooperation
- Chapter 6: Constant Memory and Events
- Chapter 7: Texture Memory
- Chapter 8: Graphics Interoperability
- Chapter 9: Atomics
- Chapter 10: Streams
- Chapter 11: CUDA C on Multiple GPUs
- Chapter 12: The Final Countdown
- Appendix: Advanced Atomics

### Chapter 2: Getting Started

- CUDA-enabled graphics processor
- NVIDIA device Driver
- CUDA Development Toolkit
- A Standard C Compiler

### Chapter 3: Introduction To CUDA C

Take a look at first example

#### Hello World

`int count; cudaGetDeviceCount(&count));`

we can then iterate through the devices and query relevant information about each

### Chapter 4: Parallel Programming in CUDA C

blockIdx: one of the built-in variables taht the CUDA runtime defines for us

- example: Julia Set
