#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "io_mock.h"
#include "cosmo_fun.h"
#define USAGE "./r2z r_file v_rad_file omega_m omega_l w RSD z_shift_file"
#define PI 3.1415926535897932384626433832
/*
  INPUT:
  r position [in Mpc/h]: file
  v_rad: file local peculiar radial velocities
  omega_m:float 
  omega_l: float
  w: float
  RSD switch: integer. !=0 means that RSD is included
  
  OUTPUT:
  z_shift (redshift) 
*/
int main(int argc, char **argv){
  int n_points;
  float *r, *v_rad;
  float *z;    
  int i;
  float omega_m, omega_l, w;
  float a_exp;
  int RSD;
  int n_list = 100000;
  float min_z=0.0, max_z=10.0;
  float *z_list, *r_list;


  if(argc!=8){
    fprintf(stderr, "USAGE: %s\n", USAGE);
    exit(1);
  }

  /*load raw data*/
  r = load_mock_file(argv[1], &n_points);
  v_rad = load_mock_file(argv[2], &n_points);
  omega_m = atof(argv[3]);
  omega_l = atof(argv[4]);
  w = atof(argv[5]);
  RSD = atoi(argv[6]);
  
  /*check in stdout what we are doing*/
  fprintf(stdout, "omega_m=%.2f omega_l=%.2f w=%.2f\n", omega_m, omega_l, w);
  if(RSD){
    fprintf(stdout, "RSD are ON!\n");
  }else{
    fprintf(stdout, "RSD are OFF!\n");
  }

  /*Initializes the array with radius data*/
  z = load_mock_file(argv[1], &n_points);

  /*Initializes lookup lists*/
  z_list = build_z(min_z, max_z, n_list);
  r_list = build_comov_r(z_list, n_list, omega_m, omega_l, w);
    
  /*uses the same routine to initialized the data*/
  z = load_mock_file(argv[1], &n_points);
  
  for(i=0;i<n_points;i++){
    z[i] = get_B_from_A(r_list, z_list, n_list, r[i]);
    //    fprintf(stdout, "z %f, r_in %f\n",z[i], r[i]);
    a_exp = 1.0/(z[i]+1.0);
    if(RSD){
      z[i] = z[i] - (v_rad[i]/a_exp)/C_LIGHT;
    }
  }
  
  /*dump results*/
  dump_mock_file(argv[7], z, n_points);  

  return 0;
}
