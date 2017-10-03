#!/usr/bin/env python

"""
Generate Julia Set Image
"""

import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import sys

'''
Feel free to play around with parameter colormap for pretty pics...
See https://matplotlib.org/examples/color/colormaps_reference.html
for a complete list or make your own! We personally like the
alternative colormaps 'terrain', 'inferno', and 'RdGy'
'''
colormap=plt.get_cmap('cubehelix')

# Read in text file, apply colormap, and save
def main(fname='julia.txt'):
    my_data = np.genfromtxt(fname, delimiter='\n')
    n = int(my_data[0]);
    juliadata = my_data[1:]
    print("Generating {0} x {0} Julia Set Image".format(n))
    juliaimage = np.reshape(juliadata, (n, n))
    plt.imshow(juliaimage, extent=[0, 1, 0, 1], cmap=colormap)
    plt.axis('tight')
    plt.axis('off')
    plt.savefig('julia.png',bbox_inches='tight', dpi=500)


if __name__ == "__main__":
    main(*sys.argv[1:])
