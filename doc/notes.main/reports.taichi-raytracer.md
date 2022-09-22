# Taichi-Ray-Tracer

在学习完taichi和ray-tracing-one-weekend之后，想要两个移植项目，一个是directX+win，一个就是taichi。ttaichi会相对容易一点，正好巩固一下知识。

## Start Up

首先写基本结构，渲染出一张图像出来

```py
import taichi as ti 

ti.init(arch=ti.vulkan)

res_width = 500
res_height = 300
nw = res_width
nh = res_height
pixels = ti.Vector.field(3, dtype=float, shape=(nw, nh))
max_step = 100000

@ti.kernel
def paint(t: float):
    for i, j in pixels:
        if (i < nw /2):
            pixels[i,j] = (0.8, 0.1, 0.2)
        else:
            pixels[i,j] = (0.1, 0.1, 0.8)

def main():
    gui = ti.GUI("Ray Tracer", res = ( res_width, res_height))
    for i in range(max_step):
        paint(i)
        gui.set_image(pixels)
        gui.show()

if __name__ == "__main__":
    main()
```

因为taichi已经替我们完成了基本的矩阵运算库，所以我们可以直接从光线开始。