#ifndef __COSMO_FUN
#define __COSMO_FUN
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define C_LIGHT 299792.458 /* in km/s */
#define D_HUBBLE 2997.92458 /*Hubble distance in Mpc/h*/

float * build_comov_r(float *z, int n_points, float omega_m, float omega_l, float w);
float E_z_value(float z, float omega_m, float omega_l, float w);
float * build_z(float min_z, float max_z, int n_points);
int locate_index(float *z, int i_first, int i_last, float z_in);
float linear_interp(float x_min, float x_max, float y_min, float y_max, float x_inter);
float get_B_from_A(float *A, float *B, int n_points, float A_in);
#endif
