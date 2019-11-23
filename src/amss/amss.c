#include "amss.h"
#include "../utils.h"
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*--------------------------------------------------------------------------*/
/*                                                                          */
/*                    AFFINE MORPHOLOGICAL SCALE-SPACE                      */
/*                                                                          */
/*                  (Copyright Joachim Weickert, 1/2015)                    */
/*                                                                          */
/*--------------------------------------------------------------------------*/


/*
 Explicit scheme with central spatial differences.
 Experimentally stable for time steps ht <= 0.1.
 No numerical guarantee for an extremum principle.
*/

/*--------------------------------------------------------------------------*/

void amss

(float ht,  /* time step size, 0 < ht <= 0.1 */
 long nx,   /* image dimension in x direction */
 long ny,   /* image dimension in y direction */
 float hx,  /* pixel size in x direction */
 float hy,  /* pixel size in y direction */
 float **u) /* input: original image ;  output: smoothed */

/*
 affine morphological scale-space, explicit scheme
*/

{
    long i, j;                   /* loop variables */
    float **f;                   /* u at old time level */
    float fx, fy, fxx, fxy, fyy; /* derivatives */
    float two_hx;                /* 2.0 * hx, time saver */
    float two_hy;                /* 2.0 * hx, time saver */
    float hx_sqr;                /* hx * hx, time saver */
    float hy_sqr;                /* hy * hy, time saver */
    float two_hx_hy;             /* 2.0 * hx * hy, time saver */
    float help;                  /* time saver */


    /* ---- allocate memory for f ---- */

    alloc_matrix (&f, nx + 2, ny + 2);


    /* ---- copy u into f ---- */

    for (i = 1; i <= nx; i++)
        for (j = 1; j <= ny; j++)
            f[i][j] = u[i][j];


    /* ---- create reflecting dummy boundaries for f ---- */

    dummies (f, nx, ny);


    /* ---- loop ---- */

    /* calculate some time savers */
    two_hx = 2.0 * hx;
    two_hy = 2.0 * hy;
    hx_sqr = hx * hx;
    hy_sqr = hy * hy;
    two_hx_hy = 2.0 * hx * hy;

    /* loop */
    for (i = 1; i <= nx; i++)
        for (j = 1; j <= ny; j++) {
            /* central spatial derivatives */
            fx = (f[i + 1][j] - f[i - 1][j]) / two_hx;
            fy = (f[i][j + 1] - f[i][j - 1]) / two_hy;
            fxx = (f[i + 1][j] - 2.0 * f[i][j] + f[i - 1][j]) / hx_sqr;
            fyy = (f[i][j + 1] - 2.0 * f[i][j] + f[i][j - 1]) / hy_sqr;
            if (fx * fy < 0.0)
                fxy = (f[i + 1][j + 1] - f[i][j + 1] - f[i + 1][j] + f[i][j] + f[i - 1][j - 1] -
                       f[i][j - 1] - f[i - 1][j] + f[i][j]) /
                      two_hx_hy;
            else
                fxy = (-f[i - 1][j + 1] + f[i][j + 1] + f[i + 1][j] - f[i][j] - f[i + 1][j - 1] +
                       f[i][j - 1] + f[i - 1][j] - f[i][j]) /
                      two_hx_hy;

            /* evolution */
            help = fx * fx * fyy + fy * fy * fxx - 2.0 * fx * fy * fxy;
            u[i][j] = f[i][j] + ht * sgn (help) * pow (fabs (help), 0.33333333333);
        }


    /* ---- free memory for f ---- */

    disalloc_matrix (f, nx + 2, ny + 2);

    return;

} /* amss */
