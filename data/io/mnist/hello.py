import numpy as np
import os
import struct

def decode_idx3_ubyte(idx3_ubyte_file):
    bin_data = open(idx3_ubyte_file, 'rb').read()
    offset = 0
    fmt_header = '>iiii'
    magic_number,num_images,num_rows,num_cols = struct.unpack_from(fmt_header, bin_data, offset)
    print("magic_number: {}, num_images: {}, size: {} * {}".format(magic_number, num_images, num_rows, num_cols))

    # decode dataset
    image_size = num_rows * num_cols
    offset += struct.calcsize(fmt_header)
    images = np.empty((num_images, num_rows, num_cols))
    for i in range(num_images):
        if (i+1)%10000==0:
            print("decoded: {} image(s)".format(i+1))
    return images

def decode_idx1_ubyte(idx1_ubyte_file):
    bin_data = open(idx1_ubyte_file, 'rb').read()

    offset = 0
    fmt_header='>ii'
    magic_number,num_images = struct.unpack_from(fmt_header, bin_data, offset)
    print("magic_num: {}, num_images: {}".format(magic_number, num_images))
    offset+=struct.calcsize(fmt_header)
    fmt_image='>B'
    labels = np.empty(num_images)
    for i in range(num_images):
        if (i+1)%10000==0:
            print('decoded: {}'.format(i+1))
        labels[i] = struct.unpack_from(fmt_image, bin_data, offset)[0]
        offset+=struct.calcsize(fmt_image)

    print(labels[0])
    return labels

if __name__ == '__main__':
    basepath = "E:\data\datasets\MNIST"
    train_image_fname = "train-images.idx3-ubyte" # 60k
    train_label_fname = "train-labels.idx1-ubyte" # 60k
    test_image_fname = "t10k-images.idx3-ubyte" # 10k
    test_label_fname = "t10k-labels.idx1-ubyte" # 10k
    train_images = decode_idx3_ubyte(os.path.join(basepath, train_image_fname))
    train_labels = decode_idx1_ubyte(os.path.join(basepath, train_label_fname))
    test_images = decode_idx3_ubyte(os.path.join(basepath, test_image_fname))
    test_labels = decode_idx1_ubyte(os.path.join(basepath, test_label_fname))


