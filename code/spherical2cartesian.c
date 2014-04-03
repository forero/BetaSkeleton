#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "io_mock.h"
#define USAGE "./s2c file_r file_phi file_theta file_mass_in file_x file_y file_z file_mass_out min_theta max_theta min_phi max_phi min_r max_r"
#define PI 3.1415926535897932384626433832
/*
  INPUT:
  Files for:
  r position
  phi position
  theta position


  OUTPUT:
  Files for:
  x position 
  y position 
  z position 
*/


int main(int argc, char **argv){
  int n_points;
  float *r, *phi, *theta;
  float *x, *y, *z;
  float *mass_in;
  float *mass_out;
  int i;
  int j;
  float min_theta, max_theta, min_phi, max_phi, min_r, max_r;
  int n_in;

  if(argc!=15){
    fprintf(stderr, "USAGE: %s\n", USAGE);
    exit(1);
  }

  /*load raw data*/
  r = load_mock_file(argv[1], &n_points);
  phi = load_mock_file(argv[2], &n_points);
  theta = load_mock_file(argv[3], &n_points);
  mass_in = load_mock_file(argv[4], &n_points);
  
  /*uses the same routine to initialized the data*/
  x = load_mock_file(argv[1], &n_points);
  y = load_mock_file(argv[2], &n_points);
  z = load_mock_file(argv[3], &n_points);
  mass_out = load_mock_file(argv[4], &n_points);


  /*get the minimum and maximum*/
  min_theta = atof(argv[9]);
  max_theta = atof(argv[10]);
  min_phi = atof(argv[11]);
  max_phi = atof(argv[12]);
  min_r = atof(argv[13]);
  max_r = atof(argv[14]);

  /*convert the input angles (in degrees) into radians*/
  min_phi = min_phi * PI/180.0;
  max_phi = max_phi * PI/180.0;
  min_theta = min_theta * PI/180.0;
  max_theta = max_theta * PI/180.0;

  j=0;
  n_in=0;
  for(i=0;i<n_points;i++){   
    if(r[i]<0.0){
      r[i] = -r[i];
    }
    
    if((r[i]>min_r && r[i]<max_r)&&(theta[i]<max_theta && theta[i]>min_theta) && (phi[i]>min_phi && phi[i]<max_phi)){
      //    fprintf(stdout, "phi %f\n", phi[i]);
      x[j] = r[i] * sin(theta[i]) * cos(phi[i]);
      y[j] = r[i] * sin(theta[i]) * sin(phi[i]);
      z[j] = r[i] * cos(theta[i]);
      mass_out[j] = mass_in[i];
      j++;
      n_in++;
    }    
  }
  fprintf(stdout, "There are %d points selected out of %d\n", n_in, n_points);

  /*dump results*/
  dump_mock_file(argv[5], x, n_in);  
  dump_mock_file(argv[6], y, n_in);  
  dump_mock_file(argv[7], z, n_in);  
  dump_mock_file(argv[8], mass_out, n_in);  

  return 0;
}
