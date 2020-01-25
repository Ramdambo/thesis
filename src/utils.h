#ifndef utils_h__
#define utils_h__

#include <stdlib.h> 

/* Matrix alloc and disalloc utils */
void alloc_vector (float **, long);
void alloc_vector_long (long **, long);
void alloc_matrix (float ***, long, long);
void alloc_cubix (float ****, long, long, long);
void disalloc_vector (float *, long);
void disalloc_matrix (float **, long, long);
void disalloc_cubix (float ***, long, long, long);

/* Read utilities */
void read_string (char *);
void read_long (long *);
void read_float (float *);

/* Image utilities */
void read_pgm_and_allocate_memory (const char *, long *, long *, float ***);
void comment_line (char *, char *, ...);
void write_pgm (float **, long, long, char *, char *);
void dummies (float **, long, long);
void imgcpy (float**, float**, size_t, size_t);

/* Math utilities */
float sgn (float);
void analyse_grey (float **, long, long, float *, float *, float *, float *);
void mask (float **, float **, long, long, int);
long clamp (long, long, long);
float degrees(float);

#endif // utils_h__
