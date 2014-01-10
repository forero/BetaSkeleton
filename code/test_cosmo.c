#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "cosmo_fun.h"

int main(int argc, char **argv){
  int i;
  float omega_m = 0.3;
  float omega_l = 0.7;
  float w = -1.0;
  float *z;
  float *r_comov;
  float min_z=0.0, max_z=1.0;
  int n_points = 4000;
  FILE *out;
  char filename[256];
  int id;
  float rnd;
  float tmp;

  z = build_z(min_z, max_z, n_points);
  r_comov = build_comov_r(z, n_points, omega_m, omega_l, w);

  sprintf(filename, "table_z_comovr_%.2f_%.2f_%.2f.dat", omega_m, omega_l, w);
  if(!(out=fopen(filename, "w"))){
    fprintf(stderr, "problem opening file filename %s\n", filename);
    exit(1);
  }
  for(i=0;i<n_points;i++){
    fprintf(out, "%f %f\n", z[i], r_comov[i]);
  }
  fclose(out);
  

  


  
  sprintf(filename, "random_table_findr_%.2f_%.2f_%.2f.dat", omega_m, omega_l, w);
  if(!(out=fopen(filename, "w"))){
    fprintf(stderr, "problem opening file filename %s\n", filename);
    exit(1);
  }

  srand48(n_points);
  for(i=0;i<n_points;i++){
    rnd = drand48() * (z[n_points - 1] - z[0]) + z[0];
    tmp = get_B_from_A(z, r_comov, n_points, rnd);
    fprintf(out, "%f %f\n", rnd, tmp);
  }
  fclose(out);


  sprintf(filename, "random_table_findz_%.2f_%.2f_%.2f.dat", omega_m, omega_l, w);
  if(!(out=fopen(filename, "w"))){
    fprintf(stderr, "problem opening file filename %s\n", filename);
    exit(1);
  }


  for(i=0;i<n_points;i++){
    rnd = drand48() * (r_comov[n_points - 1] - r_comov[0]) + r_comov[0];
    tmp = get_B_from_A(r_comov, z, n_points, rnd);
    fprintf(out, "%f %f\n", tmp, rnd);
  }
  fclose(out);
  

  return 0;
}
