import os
import imageio.v3 as iio

basepath = "E:/data/datasets/ancient_ocr_data"
traindir = "train/image"
imgfname = "image_1.jpg"

imgpath = os.path.join(basepath, traindir, imgfname)
im = iio.imread(imgpath)
print(im.shape) # (1256, 1650, 3)
iio.imwrite("test.jpg", im)
