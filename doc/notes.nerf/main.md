# NeRF

这是原版的代码，使用tensorflow写成，训练得非常慢

借着梳理这份代码的过程我需要熟悉以下tensorflow和相关工具的用法，以及坑爹的1.0 2.0代码改写

- project page: http://tancik.com/
- supplement video: https://youtu.be/JuH79E8rdKc
- paper: https://arxiv.org/abs/2003.08934

[NeRF: Representing Scenes as Neural Radiance Fields for View Synthesis](http://tancik.com/nerf)  
 [Ben Mildenhall](https://people.eecs.berkeley.edu/~bmild/)\*<sup>1</sup>,
 [Pratul P. Srinivasan](https://people.eecs.berkeley.edu/~pratul/)\*<sup>1</sup>,
 [Matthew Tancik](http://tancik.com/)\*<sup>1</sup>,
 [Jonathan T. Barron](http://jonbarron.info/)<sup>2</sup>,
 [Ravi Ramamoorthi](http://cseweb.ucsd.edu/~ravir/)<sup>3</sup>,
 [Ren Ng](https://www2.eecs.berkeley.edu/Faculty/Homepages/yirenng.html)<sup>1</sup> <br>
 <sup>1</sup>UC Berkeley, <sup>2</sup>Google Research, <sup>3</sup>UC San Diego  
  \*denotes equal contribution  
in ECCV 2020 (Oral Presentation, Best Paper Honorable Mention)

- build environment: conda env -f environment.yml
- conda activate nerf
- bash download_example_data.sh
- tensorboard --logdir=logs/summarises --port=6006

deps:
- tensorflow 1.15
- matplotlib
- numpy
- imageio
- configargparse

The LLFF dataloader requires ImageMagick

llff data and real data: https://drive.google.com/drive/folders/128yBriW1IG_3NJ5Rp7APSTZsJqdJdfc1

- download_example_data
- python run_nerf.py --config config_fern.txt

After 200K iterations (about 15 hours), you should get a video in logs/fern_test/fern_test_spiral_200000_rgb.mp4

download example_weight

to get a pre-trained high-res NeRF for Fern Database. Now you can render_demo.ipynb to render new view

## Replicating the paper results

start with configs in paper_configs

with synthesis Blender data and LLFF scenes are hosted 

and DeepVoxels data is hosted 

extract_mesh.ipynb to extract a triangle mesh from a trained NeRF network.

- PyMCubes
- trimesh
- pyrender

### Don't have poses?

img2poses.py 

in `run_nerf.py` and all other code, we use the same pose coordinates as in OpenGL: x right Y up and Z backwards (right handed)

Poses are stored in 3x4 numpy arrays that represent camera-to-world transformation matrix. Check data loading part.

