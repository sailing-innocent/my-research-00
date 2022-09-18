# Fundations.Ray-Tracing-One-Weekend

I strongly suggest everyone get started by this tutorial. It help you start to create your own rastering tools as soon as possible. Your own rastering tool plays a critical role when learning Computer Graphics. It will make abstract techniques practical, and make complicated concepts illustrated.

## Progress


## Index

- Overview
- Output an Image
- vec3 class
- Rays, a Simple Camera, and Background
- Adding a sphere
- Surfaces Normals and Multiple Objects
- Antialiasing
- Difuse Material
- Metal
- Dielectrics
- Positionalble Camera
- Defocus Blur

## Overview

## Output an Image

遇到了一个windows上的编码问题，需要注意输出时候的编码，Krita需要UTF-8编码的PPM文件才是可以识别，而 UTF16-LE则不行。

`$PSDefaultParameterValues['Out-File:Encoding']='ascii'`

`$PSDefaultParameterValues['*:Encoding'] = 'ascii'`

真是令人头秃
