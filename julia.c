#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <omp.h>


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* ~~~~~~~~~~ PARAMETERS TO PLAY AROUND WITH ~~~~~~~~~~*/
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* This determines the color distribution of the Julia Set */
static const double window = 3.0; /* keep in the range of 1...10*/

/* These determine the shape of the Julia Set */
static const double re_c = -0.46; /* keep in the range of (-1,1)*/
static const double im_c = 0.58;  /* keep in the range of (-1,1)*/


/* Julia Loop Logic: Don't touch unless you understand what to do! */
uint8_t julia_loop(double x, double y)
{
    uint8_t n=255;
    double re_z = x, im_z = y; 
    double sqr_abs_z = 0;
    while (sqr_abs_z < window && n != 0) {
        double re_z_now = re_z * re_z - im_z * im_z + re_c;
        double im_z_now = 2 * re_z * im_z + im_c;
        re_z = re_z_now;
        im_z = im_z_now;
        sqr_abs_z = re_z * re_z + im_z * im_z;
        n -= 5;
    }
    return n;
}



int main(int argc, char**argv)
{
    /* Default Size of Image is 500 x 500 pixels */
    int n = argc > 1 ? atoi(argv[1]) : 500;
    if (argc > 2) {
        fprintf(stderr, "usage: julia [image_size]\n");
        return -1;
    }

    uint8_t* julia_counts = (uint8_t*) calloc(n*n, sizeof(uint8_t));
    printf("Generating %d x %d Julia Set Data\n", n, n);

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* ~~~~~~~~~~~~ PARALLELIZE AND OFFLOAD ME ~~~~~~~~~~~~*/
    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* Main Computational Loop */
    for (int i = 0; i < n; ++i){ 
        for (int j = 0; j < n; ++j){
            double x = -1.0 + (double)i*(2.0/(n-1)) ;
            double y = -1.0 + (double)j*(2.0/(n-1)) ;
            julia_counts[i + j*n] = julia_loop(x, y);
        }
    }
    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* ~~~~~~~~~~~~ PARALLELIZE AND OFFLOAD ME ~~~~~~~~~~~~*/
    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    /* Dump julia_counts into a .txt file named julia.txt*/
    FILE *fid = fopen("julia.txt", "w");
    fprintf(fid, "%d\n", n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            fprintf(fid, "%d\n", julia_counts[i + j*n]);
    fclose(fid);

    return 1;

}
