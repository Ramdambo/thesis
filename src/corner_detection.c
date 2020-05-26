#include "mask.h"
#include "utils.h"
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define pi 3.1415927

/*--------------------------------------------------------------------------*/
/*                                                                          */
/*               CORNER DETECTION WITH THE STRUCTURE TENSOR                 */
/*                                                                          */
/*                  (Copyright Joachim Weickert, 12/2005)                   */
/*                                                                          */
/*--------------------------------------------------------------------------*/

/*
 features:
 - for greyscale and colour images
 - presmoothing at noise scale:  convolution-based, Neumann b.c.
 - presmoothing at integration scale: convolution-based, Dirichlet b.c.
*/

#ifndef max
#define max(x, y) ((x) > (y) ? (x) : (y))
#endif

typedef struct {
  long i;
  long j;
  float val;
} pixel_t;

int float_cmp(const void *a, const void *b) {
  const float v1 = *((const float *)a);
  const float v2 = *((const float *)b);
  if (v1 < v2)
    return -1;
  return v1 > v2;
}

int pixel_cmp(const void *a, const void *b) {
  const pixel_t v1 = *((const pixel_t *)a);
  const pixel_t v2 = *((const pixel_t *)b);
  if (v1.val < v2.val)
    return -1;
  return v1.val > v2.val;
}

void gauss_conv

    (float sigma,     /* standard deviation of Gaussian */
     long nx,         /* image dimension in x direction */
     long ny,         /* image dimension in y direction */
     float hx,        /* pixel size in x direction */
     float hy,        /* pixel size in y direction */
     float precision, /* cutoff at precision * sigma */
     long bc,         /* type of boundary condition */
                      /* 0=Dirichlet, 1=reflecing, 2=periodic */
     float **f)       /* input: original image ;  output: smoothed */

/*
 Gaussian convolution.
*/

{
  long i, j, p; /* loop variables */
  long length;  /* convolution vector: 0..length */
  float sum;    /* for summing up */
  float *conv;  /* convolution vector */
  float *help;  /* row or column with dummy boundaries */

  /* ------------------------ diffusion in x direction -------------------- */

  /* calculate length of convolution vector */
  length = (long)(precision * sigma / hx) + 1;
  if ((bc != 0) && (length > nx)) {
    printf("gauss_conv: sigma too large \n");
    exit(0);
  }

  /* allocate storage for convolution vector */
  alloc_vector(&conv, length + 1);

  /* calculate entries of convolution vector */
  for (i = 0; i <= length; i++)
    conv[i] = 1 / (sigma * sqrt(2.0 * 3.1415926)) *
              exp(-(i * i * hx * hx) / (2.0 * sigma * sigma));

  /* normalization */
  sum = conv[0];
  for (i = 1; i <= length; i++)
    sum = sum + 2.0 * conv[i];
  for (i = 0; i <= length; i++)
    conv[i] = conv[i] / sum;

  /* allocate storage for a row */
  alloc_vector(&help, nx + length + length);

  for (j = 1; j <= ny; j++) {
    /* copy in row vector */
    for (i = 1; i <= nx; i++)
      help[i + length - 1] = f[i][j];

    /* assign boundary conditions */
    if (bc == 0) /* Dirichlet boundary conditions */
      for (p = 1; p <= length; p++) {
        help[length - p] = 0.0;
        help[nx + length - 1 + p] = 0.0;
      }
    else if (bc == 1) /* reflecting b.c. */
      for (p = 1; p <= length; p++) {
        help[length - p] = help[length + p - 1];
        help[nx + length - 1 + p] = help[nx + length - p];
      }
    else if (bc == 2) /* periodic b.c. */
      for (p = 1; p <= length; p++) {
        help[length - p] = help[nx + length - p];
        help[nx + length - 1 + p] = help[length + p - 1];
      }

    /* convolution step */
    for (i = length; i <= nx + length - 1; i++) {
      /* calculate convolution */
      sum = conv[0] * help[i];
      for (p = 1; p <= length; p++)
        sum = sum + conv[p] * (help[i + p] + help[i - p]);
      /* write back */
      f[i - length + 1][j] = sum;
    }
  } /* for j */

  /* disallocate storage for a row */
  disalloc_vector(help, nx + length + length);

  /* disallocate convolution vector */
  disalloc_vector(conv, length + 1);

  /* ------------------------ diffusion in y direction -------------------- */

  /* calculate length of convolution vector */
  length = (long)(precision * sigma / hy) + 1;
  if ((bc != 0) && (length > ny)) {
    printf("gauss_conv: sigma too large \n");
    exit(0);
  }

  /* allocate storage for convolution vector */
  alloc_vector(&conv, length + 1);

  /* calculate entries of convolution vector */
  for (j = 0; j <= length; j++)
    conv[j] = 1 / (sigma * sqrt(2.0 * 3.1415927)) *
              exp(-(j * j * hy * hy) / (2.0 * sigma * sigma));

  /* normalization */
  sum = conv[0];
  for (j = 1; j <= length; j++)
    sum = sum + 2.0 * conv[j];
  for (j = 0; j <= length; j++)
    conv[j] = conv[j] / sum;

  /* allocate storage for a row */
  alloc_vector(&help, ny + length + length);

  for (i = 1; i <= nx; i++) {
    /* copy in column vector */
    for (j = 1; j <= ny; j++)
      help[j + length - 1] = f[i][j];

    /* assign boundary conditions */
    if (bc == 0) /* Dirichlet boundary conditions */
      for (p = 1; p <= length; p++) {
        help[length - p] = 0.0;
        help[ny + length - 1 + p] = 0.0;
      }
    else if (bc == 1) /* reflecting b.c. */
      for (p = 1; p <= length; p++) {
        help[length - p] = help[length + p - 1];
        help[ny + length - 1 + p] = help[ny + length - p];
      }
    else if (bc == 2) /* periodic b.c. */
      for (p = 1; p <= length; p++) {
        help[length - p] = help[ny + length - p];
        help[ny + length - 1 + p] = help[length + p - 1];
      }

    /* convolution step */
    for (j = length; j <= ny + length - 1; j++) {
      /* calculate convolution */
      sum = conv[0] * help[j];
      for (p = 1; p <= length; p++)
        sum = sum + conv[p] * (help[j + p] + help[j - p]);
      /* write back */
      f[i][j - length + 1] = sum;
    }
  } /* for i */

  /* disallocate storage for a row */
  disalloc_vector(help, ny + length + length);

  /* disallocate convolution vector */
  disalloc_vector(conv, length + 1);

  return;

} /* gauss_conv */

/* ------------------------------------------------------------------------ */

void struct_tensor

    (float **v,   /* image !! gets smoothed on exit !! */
     long nx,     /* image dimension in x direction */
     long ny,     /* image dimension in y direction */
     float hx,    /* pixel size in x direction */
     float hy,    /* pixel size in y direction */
     float sigma, /* noise scale */
     float rho,   /* integration scale */
     float **dxx, /* element of structure tensor, output */
     float **dxy, /* element of structure tensor, output */
     float **dyy) /* element of structure tensor, output */

/*
 Calculates the structure tensor.
*/

{
  long i, j;            /* loop variables */
  float dv_dx, dv_dy;   /* derivatives of v */
  float h1, h2, h3, h4; /* time saver */

  /* ---- initialization ---- */

  for (i = 1; i <= nx; i++) {
    for (j = 1; j <= ny; j++) {
      dxx[i][j] = 0.0;
      dxy[i][j] = 0.0;
      dyy[i][j] = 0.0;
    }
  }

  float alpha = 0.2;
  h1 = (1.0 - 2.0 * alpha) / (2.0 * hx);
  h2 = alpha / (2.0 * hx);
  h3 = (1.0 - 2.0 * alpha) / (2.0 * hy);
  h4 = alpha / (2.0 * hy);

  /* ---- smoothing at noise scale ---- */

  if (sigma > 0.0) {
    gauss_conv(sigma, nx, ny, hx, hy, 3.0, 1, v); /* refl. b.c. */
  }

  /* ---- building tensor product ---- */

  dummies(v, nx, ny);

  for (i = 1; i <= nx; i++) {
    for (j = 1; j <= ny; j++) {
      /* modified Sobel derivatives */
      dv_dx = h1 * (v[i + 1][j] - v[i - 1][j]) +
              h2 * (v[i + 1][j - 1] - v[i - 1][j - 1] + v[i + 1][j + 1] -
                    v[i - 1][j + 1]);
      dv_dy = h3 * (v[i][j + 1] - v[i][j - 1]) +
              h4 * (v[i - 1][j + 1] - v[i - 1][j - 1] + v[i + 1][j + 1] -
                    v[i + 1][j - 1]);
      /* tensor product */
      dxx[i][j] = dv_dx * dv_dx;
      dxy[i][j] = dv_dx * dv_dy;
      dyy[i][j] = dv_dy * dv_dy;
    }
  }

  /* ---- smoothing at integration scale, Dirichlet b.c. ---- */

  if (rho > 0.0) {
    gauss_conv(rho, nx, ny, hx, hy, 3.0, 0, dxx);
    gauss_conv(rho, nx, ny, hx, hy, 3.0, 0, dxy);
    gauss_conv(rho, nx, ny, hx, hy, 3.0, 0, dyy);
  }

  return;

} /* struct_tensor */

/* ------------------------------------------------------------------------ */

void PA_trans

    (float a11,   /* coeffs of (2*2)-matrix */
     float a12,   /* coeffs of (2*2)-matrix */
     float a22,   /* coeffs of (2*2)-matrix */
     float *c,    /* 1. comp. of 1. eigenvector, output */
     float *s,    /* 2. comp. of 1. eigenvector, output */
     float *lam1, /* larger  eigenvalue, output */
     float *lam2) /* smaller eigenvalue, output */

/*
 Principal axis transformation, checked for correctness.
*/

{
  float help, norm; /* time savers */

  /* ---- compute eigenvalues and eigenvectors ---- */

  help = sqrt(powf(a22 - a11, 2.0) + 4.0 * a12 * a12);

  if (help == 0.0)
  /* isotropic situation, eigenvectors arbitrary */
  {
    *lam1 = *lam2 = a11;
    *c = 1.0;
    *s = 0.0;
  }

  else if (a11 > a22) {
    *lam1 = 0.5 * (a11 + a22 + help);
    *lam2 = 0.5 * (a11 + a22 - help);
    *c = a11 - a22 + help;
    *s = 2.0 * a12;
  }

  else {
    *lam1 = 0.5 * (a11 + a22 + help);
    *lam2 = 0.5 * (a11 + a22 - help);
    *c = 2.0 * a12;
    *s = a22 - a11 + help;
  }

  /* ---- normalize eigenvectors ---- */

  norm = sqrt(*c * *c + *s * *s);
  if (norm > 0.0) {
    *c = *c / norm;
    *s = *s / norm;
  } else {
    *c = 1.0;
    *s = 0.0;
  }

  return;

} /* PA_trans */

/*--------------------------------------------------------------------------*/

void non_maximum_suppression(float **w, long nx, long ny, float **v) {
  long i, j, k, l; /* Loop variables */
  for (i = 1; i <= nx; i++) {
    for (j = 1; j <= ny; j++) {
      if (w[i][j] <= 0.001) {
        continue;
      }
      int max = 1;
      /* Check if current pixel is maximum in 3x3 neighbourhood */
      for (k = i - 1; k <= i + 1; ++k) {
        for (l = j - 1; l <= j + 1; ++l) {
          if (w[k][l] > w[i][j]) {
            max = 0;
          }
        }
      }
      if (max) {
        v[i][j] = w[i][j];
      } else {
        v[i][j] = 0.0f;
      }
    }
  }
}

void non_maximum_suppression_circle(float **w, long nx, long ny, long radius,
                                    float **v) {
  long i, j, k, l; /* Loop variables */
  int max;         /* Variables for non maximum suppression */

  for (i = 1; i <= nx; i++) {
    for (j = 1; j <= ny; j++) {
      max = 1;
      /* To speed up the process, weed out outliers by first comparing them to
       * an epsilon */
      if (w[i][j] <= 0.001) {
        continue;
      }
      /* Check if current pixel is maximum in circular neighbourhood of given
       * radius */
      for (k = i - radius; k <= i + radius; k++) {
        for (l = j - radius; l <= j + radius; l++) {
          if (out_of_bounds(k, nx) || out_of_bounds(l, ny) ||
              !in_circle(k, l, i, j, radius)) {
            continue;
          }
          if (w[k][l] > w[i][j]) {
            max = 0;
          }
        }
      }
      if (max) {
        v[i][j] = w[i][j];
      } else {
        v[i][j] = 0;
      }
    }
  }
}

void total_pixel_percentage_thresholding(float **u, long nx, long ny,
                                         int radius, float perc) {
  long i, j;
  long n_total = nx * ny;
  pixel_t vals[n_total];

  /* Max number of pixels per corner region given by upper bound of Gauss'
   * circle problem */
  float max_area_p_corner =
      radius < 0 ? 1 : pi * radius * radius + powf(radius, 131.0 / 208.0);

  long n_corners = ceil((perc * n_total) / max_area_p_corner);

  /* Flatten cornerness map and prepare for sorting */
  long idx = 0;
  for (i = 1; i <= nx; ++i) {
    for (j = 1; j <= ny; ++j) {
      if (u[i][j] > 0.01) {
        vals[idx++] = (pixel_t){i, j, u[i][j]};
      }
    }
  }

  qsort(vals, idx, sizeof(pixel_t), pixel_cmp);

  /* Initialize */
  for (i = 1; i <= nx; i++) {
    for (j = 1; j <= ny; j++) {
      u[i][j] = 0;
    }
  }

  /* Keep best corners */
  for (i = idx - 1; i > max(idx - n_corners, 0); --i) {
    long x = vals[i].i;
    long y = vals[i].j;
    u[x][y] = 255.0f;
  }
}

void percentile_thresholding(float **u, long nx, long ny, float perc) {
  long i, j;           /* Loop variables */
  float vals[nx * ny]; /* Array for threshold computation */
  long n_vals = 0;     /* Number of elements in the array */

  /* Flatten cornerness map and prepare for sorting */
  for (i = 1; i <= nx; ++i) {
    for (j = 1; j <= ny; ++j) {
      /* Preliminary thresholding to weed out outliers */
      if (fabs(u[i][j]) < 0.01) {
        continue;
      } else {
        vals[n_vals++] = u[i][j];
      }
    }
  }

  qsort(vals, n_vals, sizeof(float), float_cmp);

  long index = clamp((long)ceil(n_vals * perc), 0, n_vals);

  float thresh = vals[index];

  /* Apply percentile threshold */
  long n_corners = 0;
  for (i = 1; i <= nx; i++) {
    for (j = 1; j <= ny; j++) {
      if (u[i][j] <= thresh) {
        u[i][j] = 0;
      } else {
        u[i][j] = 255.0f;
      }
    }
  }
}

void corner_detection

    (float **f,    /* image, unaltered */
     float **v,    /* corner locations, output */
     long nx,      /* image dimension in x direction */
     long ny,      /* image dimension in y direction */
     float hx,     /* pixel size in x direction */
     float hy,     /* pixel size in y direction */
     long type,    /* type of corner detector */
     float perc,   /* percentile */
     float radius, /* radius for non maximum suppression */
     float sigma,  /* noise scale */
     float rho,    /* integration scale */
     bool cnms,    /* flag to enable circular non maximum suppression */
     bool tppt /* flag to enable total pixel percentage thresholding */)

/*
 calculates structure tensor based corner detector;
 v[i][j]=255 for corners;
 v[i][j]=0   else;
*/

{
  long i, j;                 /* loop variables */
  float **u;                 /* loop */
  float **dxx, **dxy, **dyy; /* tensor components */
  float **w;                 /* field for corner detection */
  float c, s;                /* cosine, sine */
  float lam1, lam2;          /* eigenvalues */
  float det, trace;          /* determinant, trace */

  /* allocate storage */
  alloc_matrix(&u, nx + 2, ny + 2);
  alloc_matrix(&dxx, nx + 2, ny + 2);
  alloc_matrix(&dxy, nx + 2, ny + 2);
  alloc_matrix(&dyy, nx + 2, ny + 2);
  alloc_matrix(&w, nx + 2, ny + 2);

  /* copy f into u */
  imgcpy(f, u, nx + 2, ny + 2);

  /* calculate structure tensor of u */
  struct_tensor(u, nx, ny, hx, hy, sigma, rho, dxx, dxy, dyy);

  if (type == 0)
    /* Rohr: det(J) */
    for (i = 1; i <= nx; i++) {
      for (j = 1; j <= ny; j++) {
        w[i][j] = dxx[i][j] * dyy[i][j] - dxy[i][j] * dxy[i][j];
      }
    }

  if (type == 1)
    /* Tomasi-Kanade: smaller eigenvalue */
    for (i = 1; i <= nx; i++) {
      for (j = 1; j <= ny; j++) {
        PA_trans(dxx[i][j], dxy[i][j], dyy[i][j], &c, &s, &lam1, &lam2);
        w[i][j] = lam2;
      }
    }

  if (type == 2)
    /* Foerstner-Harris: det(J)/trace(J)
     * -> Harmonic mean */
    for (i = 1; i <= nx; i++) {
      for (j = 1; j <= ny; j++) {
        /* Adding a small epsilon to prevent division through zero */
        trace = dxx[i][j] + dyy[i][j] + 0.000001;
        det = dxx[i][j] * dyy[i][j] - dxy[i][j] * dxy[i][j];
        w[i][j] = 2 * det / trace;
      }
    }

  dummies(w, nx, ny);

  if (!cnms) {
    non_maximum_suppression(w, nx, ny, v);
  } else {
    non_maximum_suppression_circle(w, nx, ny, radius, v);
  }

  if (!tppt) {
    percentile_thresholding(v, nx, ny, perc);
  } else {
    total_pixel_percentage_thresholding(v, nx, ny, radius, perc);
  }

  /* free storage */
  disalloc_matrix(u, nx + 2, ny + 2);
  disalloc_matrix(dxx, nx + 2, ny + 2);
  disalloc_matrix(dxy, nx + 2, ny + 2);
  disalloc_matrix(dyy, nx + 2, ny + 2);
  disalloc_matrix(w, nx + 2, ny + 2);
} /* corner_detection */

/*--------------------------------------------------------------------------*/

void draw_corners

    (float **u, /* image, altered ! */
     long nx,   /* image dimension in x direction */
     long ny,   /* image dimension in y direction */
     float **v) /* image with corner locations */

/*
 draws corners into the image u, at locations specified by v
 v[i][j]=255 for corners;
 v[i][j]=0   else;
*/

{
  long i, j; /* loop variables */
  long k, l; /* loop variables */

  dummies(u, nx, ny);

  for (i = 5; i <= nx - 4; i++) {
    for (j = 5; j <= ny - 4; j++) {
      /* draw corner */
      if (v[i][j] == 255.0) {
        for (k = i - 4; k <= i + 4; k++) {
          for (l = j - 4; l <= j + 4; l++) {
            /* black outer circle */
            if ((k - i) * (k - i) + (l - j) * (l - j) <= 20)
              u[k][l] = 0.0;
            /* white interior */
            if ((k - i) * (k - i) + (l - j) * (l - j) <= 6)
              u[k][l] = 255.0;
          }
        }
      }
    }
  }
} /* draw_corners */

/*--------------------------------------------------------------------------*/

int main(int argc, char **argv)

{
  char *in;    /* Filename input image */
  float **u;   /* Input image */
  float **v;   /* Image with corner location */
  long nx, ny; /* Image size in x, y direction */
  long count;  /* Number of corners */

  /* Variables given from command line interface */
  char *out = "corners.pgm"; /* Filename output image */
  long type = 2;             /* Type of corner detector */
  float q = 0.1;             /* Percentile parameter to compute threshold */
  float sigma = 1;           /* Noise scale */
  float rho = 2.5;           /* Integration scale */
  float mask_factor = 0;     /* Factor to scale integration scale with to obtain
                                radius of corner regions */

  /* Flags for corner detection options */
  bool enable_cnms = 0;
  bool enable_tppt = 0;
  bool display_mask = 0;

  printf("\n");
  printf("CORNER DETECTION WITH THE STRUCTURE TENSOR\n\n");

  int c;
  while ((c = getopt(argc, argv, "q:c:s:r:o:m:CMP")) != -1) {
    switch (c) {
    case 'q':
      q = atof(optarg);
      if (q < 0 || q > 1) {
        fprintf(stderr, "Percentile has to be between 0 and 1!\n");
        abort();
      }
      break;
    case 'c':
      type = atoi(optarg);
      break;
    case 's':
      sigma = atof(optarg);
      break;
    case 'r':
      rho = atof(optarg);
      break;
    case 'o':
      out = optarg;
      break;
    case 'm':
      mask_factor = atof(optarg);
      break;
    case 'C':
      enable_cnms = 1;
      break;
    case 'P':
      enable_tppt = 1;
      break;
    case 'M':
      display_mask = 1;
      break;
    default:
      abort();
    }
  }

  if (optind == argc) {
    fprintf(stderr, "No input file specified. Aborting...\n");
    abort();
  }

  if (argc - optind > 1) {
    fprintf(stderr, "Too many positional arguments. Aborting...\n");
    abort();
  }

  in = argv[optind];

  read_pgm_and_allocate_memory(in, &nx, &ny, &u);

  /* Allocate storage for corner locations */
  alloc_matrix(&v, nx + 2, ny + 2);

  /* Initialize corner map */
  for (long i = 1; i <= nx; ++i) {
    for (long j = 1; j <= ny; ++j) {
    v[i][j] = 0.0f;
    }
  }

  /* Compute mask radius in dependence of rho */
  float mask_radius = mask_factor * rho;

  printf("Using parameters:\n");
  printf("  Corner detector:    ");
  if (type == 0) {
    printf("Rohr\n");
  } else if (type == 1) {
    printf("Tomasi-Kanade\n");
  } else if (type == 2) {
    printf("Foerstner-Harris\n");
  } else {
    fprintf(stderr, "Invalid feature detection method.");
    abort();
  }
  printf("  Initial image:      %-s\n", in);
  printf("  Output image:       %-s\n", out);
  printf("  Sigma:              %-8.2f\n", sigma);
  printf("  Rho:                %-8.2f\n", rho);
  printf("  Percentile:         %-8.2f\n", q);
  printf("  Mask factor:        %-8.2f\n", mask_factor);
  printf("  Mask radius:        %-8.2f\n", mask_radius);
  printf("  CNMS enabled:       %-5s\n", enable_cnms ? "true" : "false");
  printf("  TPPT enabled:       %-5s\n", enable_tppt ? "true" : "false");
  printf("  Compute mask:       %-5s\n", display_mask ? "true" : "false");
  printf("\n");

  corner_detection(u, v, nx, ny, 1.0, 1.0, type, q, mask_radius, sigma, rho,
                   enable_cnms, enable_tppt);
  /*corner_detection(u, nx, ny, 1.0, 1.0, type, q, mask_radius, enable_cnms,*/
  /*enable_tppt, sigma, rho, v);*/

  long n_corners = 0;
  for (long i = 1; i <= nx; ++i) {
    for (long j = 1; j <= ny; ++j) {
      if (v[i][j] == 255.0f) {
        n_corners++;
      }
    }
  }

  printf("Number of detected corners:       %-8ld\n", n_corners);

  if (display_mask) {
    /* Create mask with disk shaped corner regions */
    mask(u, nx, ny, mask_radius, v);

    long n_mask_pixels = 0;
    for (long i = 1; i <= nx; ++i) {
      for (long j = 1; j <= ny; ++j) {
        if (u[i][j] == 255.0f) {
          n_mask_pixels++;
        }
      }
    }
    printf("Number of pixels in mask:       %-8ld\n", n_mask_pixels);
    printf("Percentage:                     %-8.2f\n",
           100.0f * ((float)n_mask_pixels) / (nx * ny));
  } else {
    /* Insert corner marks into the image */
    draw_corners(u, nx, ny, v);
  }

  write_pgm(u, nx, ny, out, NULL);

  /* ---- disallocate storage ---- */

  disalloc_matrix(u, nx + 2, ny + 2);
  disalloc_matrix(v, nx + 2, ny + 2);
}
