# Creating the Julia Set

In this HW, we cover using the Xeon Phi accelerators on the cluster. 
If you have any questions, don't hesitate to post on Piazza or come to OH! 

**Submission:** A tarball/git-link of the provided directory

# How to form the Julia Set

The Julia Set is a famous mathematical object that you may have seen before. 
It is one of the canonical fractals common in mathematical art and dynamical systems. 
The mathematical definition of fractals and the dynamical systems giving
rise to fractal behavior is out-of-scope for this course, so if you are curious, 
please refer to outside resources for more information. We found 
[this link](http://www.karlsims.com/julia.html) to be particularly 
easy to understand. 

To be a bit less precise, let's say that one has a 2 dimensional array
of pixels. If we color each pixel based on a recursive formula
involving that pixel's previous color (with a some base case dependent upon that pixel's location)
, we will often obtain very interesting mathematical behavior. The Julia Set arises from 
a specific recursive formula with mathematical behavior known as fractal. 
Fractal behavior often results in very pretty pictures! If you don't know what the Julia 
set looks like, run the code and find out!

# Instructions

We have given you *julia.c*, the makefile, submission script and a visualizer written in Python. 
You run *julia.c* as follows:

```
./julia 100
```

Where 100 is the desired width and length of your image. *julia* will then spit out
a text file containing pixel information and metadata. We then use 

```
python visualizer.py julia.txt
```

To generate the image. If you don't feel like using any input arguments, we have set
the default image size to 500 pixels by 500 pixels and the default output name to *julia.txt*.
Your job is thus to parallelize and offload the marked portion in *julia.c* to the Xeon Phis. 

*julia.c* and *visualize.py* both contain parameters for you to play around with, in order to
get your very own "custom Julia Set". Please do take a look at which parameters you can modify!
We are looking forward to seeing a variety of different images. 

# Offloading

As with many accelerator programming models, you need to explicitly copy data 
between the host and the device (the CPU and Xeon Phi in this case). OpenMP is 
once again the language you will be using. For instructions, please check the 
class slides for a quick tutorial and these 
[slides](https://portal.tacc.utexas.edu/documents/13601/901837/offload_slides_DJ2013-3.pdf) 
for an alternative. 

We have included a specific makefile recipe for offloading named *julia-xeonphi* which
contains the compiler flags necessary for offloading. 

# Important Final Thoughts

If you are generating a large image using *visualize.py*, please use your personal 
computer so you don't slow down the login node for everyone else. 
You can still submit job files, but don't run visualize.py afterwards on 
the login node; simply copy *julia.txt* to your personal computer. 

On another note, we will be working with other accelerators (GPUs) for the 
next Programming Project in case you were hoping to get some hands-on experience with GPUs. 

# Tips and Hints

All you need to do is use the Xeon Phis to work on the array *julia_counts*
by declaring it as something to be offloaded. Then, you may parallelize the outer for loop
in the same way you did for the previous HW. 

If you are feeling especially motivated, try vectorizing the computational kernel
*julia_loop*. It's current form is rather inefficient, as it works on individual pixels rather than
sets of pixels! 


