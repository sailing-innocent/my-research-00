import os
os.environ['TF_FORCE_GPU_ALLOW_GROWTH'] = 'true'

import sys
import tensorflow as tf
import numpy as np
import imageio
import time

from utils import *

# print("Num GPUs Available: ", len(tf.config.list_physical_devices('GPU')))

def config_parser():
    import configargparse
    parser = configargparse.ArgumentParser()
    parser.add_argument('--config', is_config_file=True, help='config file path')
    #... the config parser

def train():
    parser = config_parser()
    """
    args = parser.parse_args()

    if args.random_seed is not None:
        print('Fixing random seed')

    # Load Data
    if args.dataset_type == 'llff':
        images, poses, bds, render_poses, i_test = load_llff_data(args.datadir, args.factor, recenter=True, be_factor=.75, spherify=args.spherify)
    elif args.dataset_type == 'blender':
        # load blender
        pass
    elif args.dataset_type == 'deepvoxels':
        # load deepvoxels
        pass
    else:
        print("Unknown dataset type", args.dataset_type, 'exiting')
        return

    # Short circuit if only rendering out from trained model
    if args.render_only:
        print("RENDER ONLY")
    """
    model = init_nerf_model()
    model.summary()
    # plot_model(model, to_file="test.png", show_shapes=True)

if __name__ == '__main__':
    train()