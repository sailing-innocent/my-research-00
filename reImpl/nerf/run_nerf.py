import os
os.environ['TF_FORCE_GPU_ALLOW_GROWTH'] = 'true'

import sys
import tensorflow as tf
import numpy as np
import imageio
import json
import random
import time

def create_nerf(args):
    pass 
    # the model


# 461-573 config parser

def train():
    pass
    # parser
    # args

    # fix seed

    # Load Data -> i_train i_val for llff blender and deepvoxels

    # cast intrinsics h w focal

    # create log dir and copy config file

    # if render_only render iamges = images[i_test]

    # Create optimizer
    # Adam

    # batching get ray

    # BEGIN TRAINING

    ## REST IS LOGGING



if __name__ == "__main__":
    train()