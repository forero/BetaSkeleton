#include "cosmo_fun.h"

float get_B_from_A(float *A, float *B, int n_points, float A_in){
  int index;
  float B_out;
  index = locate_index(A, 0, n_points-1, A_in);
  
  B_out = linear_interp(A[index], A[index+1], B[index], B[index+1], A_in);
  return B_out;
}

float linear_interp(float x_min, float x_max, float y_min, float y_max, float x_inter){
  float m;
  float y_inter;
  m = (y_max - y_min) / (x_max - x_min);
  
  y_inter = y_min + m * (x_inter - x_min);
  return y_inter;
}


int locate_index(float *z, int i_first, int i_last, float z_in){
  /*looks for the corresponding value of z_in in z. 
   this assumes that the array z is order in ascending order*/
  int index;
  int middle;
  index=-1;
  if(z_in>=z[i_first] || z_in<=z[i_last]){
    if((i_last - i_first)<=1){
      index = i_first;
    }else{
      middle = (i_last + i_first)/2;
      if(z_in>=z[i_first] && z_in <=z[middle]){
	index = locate_index(z, i_first, middle, z_in);
      }else{
	index = locate_index(z, middle, i_last, z_in);
      }
    }    
  }
  return index;
}

float *build_comov_r(float *z, int n_points, float omega_m, float omega_l, float w){
  /*Builds an array of comoving_r after an array of redshifts is given. The distance is in units of Mpc/h*/
  int i;
  float delta_z;
  float E_z;
  float *comov_r;
  if(!(comov_r=malloc(n_points * sizeof(float)))){
    fprintf(stderr, "problem with the comov_r allocation\n");
    exit(1);
  }

  comov_r[0] = 0.0;
  
  for(i=1;i<n_points;i++){
    delta_z = z[i] - z[i-1];
    E_z = E_z_value(z[i], omega_m, omega_l, w);
    comov_r[i] = comov_r[i-1] + ((delta_z) * (1.0/E_z) * D_HUBBLE);
  }

  return comov_r;
}

float *build_z(float min_z, float max_z, int n_points){
  float delta_z;
  float *z;
  int i;

  delta_z = (max_z - min_z) / (n_points -1);
  if(!(z=malloc(n_points * sizeof(float)))){
    fprintf(stderr, "problem with the z allocation\n");
    exit(1);
  }

  z[0] = min_z;
  for(i=1;i<n_points;i++){
    z[i] = z[i-1] + delta_z; 
  }
  
  return z;
}


float E_z_value(float z, float omega_m, float omega_l, float w){
  /*hubble constant*/
  float Ez;
  Ez = sqrt(omega_m * pow((1.0+z),3.0) + omega_l* pow((1.0+z), (3.0*(1.0+w))));
  return Ez;
}

