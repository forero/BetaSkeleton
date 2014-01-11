#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "io_mock.h"
#define USAGE "./s2c r phi theta x y z"
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
  int i;

  if(argc!=7){
    fprintf(stderr, "USAGE: %s\n", USAGE);
    exit(1);
  }

  /*load raw data*/
  r = load_mock_file(argv[1], &n_points);
  phi = load_mock_file(argv[2], &n_points);
  theta = load_mock_file(argv[3], &n_points);

  
  /*uses the same routine to initialized the data*/
  x = load_mock_file(argv[1], &n_points);
  y = load_mock_file(argv[2], &n_points);
  z = load_mock_file(argv[3], &n_points);
  
  for(i=0;i<n_points;i++){
    if(r[i]<0.0){
      r[i] = -r[i];
    }
    //    fprintf(stdout, "phi %f\n", phi[i]);
    x[i] = r[i] * sin(theta[i]) * cos(phi[i]);
    y[i] = r[i] * sin(theta[i]) * sin(phi[i]);
    z[i] = r[i] * cos(theta[i]);
  }

  /*dump results*/
  dump_mock_file(argv[4], x, n_points);  
  dump_mock_file(argv[5], y, n_points);  
  dump_mock_file(argv[6], z, n_points);  

  return 0;
}
