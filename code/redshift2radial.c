#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "io_mock.h"
#include "cosmo_fun.h"
#define USAGE "./z2r z_file omega_m omega_l w r_recovered_file"
#define PI 3.1415926535897932384626433832
/*
  INPUT:
  z: file for redshift measurements
  omega_m: float 
  omega_l: float
  w: float
  
  OUTPUT:
  r recovered position [in Mpc/h]: file
*/
int main(int argc, char **argv){
  int n_points;
  float *r;
  float *z;    
  int i;
  float omega_m, omega_l, w;
  float a_exp;
  int RSD;
  int n_list = 100000;
  float min_z=0.0, max_z=10.0;
  float *z_list, *r_list;

  if(argc != 6){
    fprintf(stderr, "USAGE: %s\n", USAGE);
    exit(1);
  }

  /*load raw data*/
  z = load_mock_file(argv[1], &n_points);
  omega_m = atof(argv[2]);
  omega_l = atof(argv[3]);
  w = atof(argv[4]);
  
  /*check in stdout what we are doing*/
  fprintf(stdout, "omega_m=%.2f omega_l=%.2f w=%.2f\n", omega_m, omega_l, w);

  /*Initializes the array with redshift data*/
  z = load_mock_file(argv[1], &n_points);

  /*Initializes lookup lists*/
  z_list = build_z(min_z, max_z, n_list);
  r_list = build_comov_r(z_list, n_list, omega_m, omega_l, w);
    
  /*uses the same routine to initialized the data*/
  r = load_mock_file(argv[1], &n_points);
  
  for(i=0;i<n_points;i++){
    r[i] = get_B_from_A(z_list, r_list, n_list, z[i]);
    //    fprintf(stdout, "z %f, r_in %f\n",z[i], r[i]);
  }
  
  /*dump results*/
  dump_mock_file(argv[5], r, n_points);  

  return 0;
}
