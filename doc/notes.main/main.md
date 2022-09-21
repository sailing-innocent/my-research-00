# Research00

这是我进入南京大学读研之后的第一份研究，基本方向和框架都是由我自己兴趣决定，和老师组内的方向基本无关，趁着老师暂时还没管我，抓紧时间自己弄出一些东西了。磨练出扎实的本领才是重要的。

主要任务有三个：

- 复现nerf代码，熟悉其中的过程，不需要训练（训练过程太昂贵了），用C++进行改写
- 复现nerf--代码，用C++进行改写
- 复现instant-ngp的代码，并仿照它的文件结构搭建自己的研究平台

之所以选择这三个项目，是因为在前期探索中发现这三个项目涉及到的核心能力和库都是我必须熟练掌握的。nerf的代码主要熟悉tensorflow，而nerf--主要熟悉pytorch相关的工具。最后instant-ngp是用tiny-cuda-nn配合eigen并行计算，用imgui搭建可视化图形库，后台可以扩展各种directX等，代码优美实用，是我必须掌握的核心能力。

这个research最终的成果会是至少一篇论文和一个可以快速复现各种论文的流水线，这是我整个研究生阶段的基础。

## 第一阶段：复现

这一阶段不要总想着弄出什么新的东西额，而是着重于各种工具的熟悉和论文的复现工作。既要用现有的数据集，还需要能够借用手机等工具现场收集（比如构建一个app来进行录像通信）

### Ray Tracing One Weekend

[RayTracing/raytracing.github.io: Main Web Site (Online Books)](https://github.com/RayTracing/raytracing.github.io/)

这个教程真的非常nice，我愿称之为最好的图形学入门练习。

1. Lights — You can do this explicitly, by sending shadow rays to lights, or it can be done implicitly by making some objects emit light, biasing scattered rays toward them, and then downweighting those rays to cancel out the bias. Both work. I am in the minority in favoring the latter approach.
2. Triangles — Most cool models are in triangle form. The model I/O is the worst and almost everybody tries to get somebody else’s code to do this.
3. Surface Textures — This lets you paste images on like wall paper. Pretty easy and a good thing to do.
4. Solid textures — Ken Perlin has his code online. Andrew Kensler has some very cool info at his blog.
5. Volumes and Media — Cool stuff and will challenge your software architecture. I favor making volumes have the hittable interface and probabilistically have intersections based on density. Your rendering code doesn’t even have to know it has volumes with that method.
6. Parallelism — Run **N** copies of your code on **N** cores with different random seeds. Average the **N** runs. This averaging can also be done hierarchically where **N**/**2** pairs can be averaged to get **N**/**4** images, and pairs of those can be averaged. That method of parallelism should extend well into the thousands of cores with very little coding.

在完成之后，我需要从这个项目中写出自己的光栅渲染器

我的整体研究过程就是：首先在reImpl中复现，然后在sail中重写进我自己的框架，最后提出想法，测试和研究。

### instant-ngp

在经过了之前的铺垫之后，我终于可以开始写我自己的ngp了