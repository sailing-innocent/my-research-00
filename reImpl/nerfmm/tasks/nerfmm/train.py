from re import L
import sys
import os 
import argparse
import torch


def parse_args():
    pass

def gen_detail_name(args):
    pass

def store_current_pose(pose_net, pose_history_dir, epoch_i):
    pass

def model_render_image():
    pass

def eval_one_epoch_img():
    pass

def set_randomness(args):
    pass

def main(args):
    my_devices = torch.device('cuda:'+str(args.gpu_id))

    """Create Folders"""

    """LOG"""

    """Summary Writer"""

    """"""

    return

if __name__ == '__main__':
    args = parse_args()
    set_randomness(args)
    main(args)