#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "io_mock.h"
#define USAGE "./c2s x y z r phi theta"
#define PI 3.1415926535897932384626433832
/*
  INPUT:
  Files for:
  x position 
  y position 
  z position 

  OUTPUT:
  Files for:
  r position
  phi position
  theta position
*/


int main(int argc, char **argv){
  int n_points;
  float *r, *phi, *theta;
  float *x, *y, *z;
  float tmp;
  int i;

  if(argc!=7){
    fprintf(stderr, "USAGE: %s\n", USAGE);
    exit(1);
  }

  /*load raw data*/
  x = load_mock_file(argv[1], &n_points);
  y = load_mock_file(argv[2], &n_points);
  z = load_mock_file(argv[3], &n_points);
  
  /*uses the same routine to initialized the data*/
  r = load_mock_file(argv[1], &n_points);
  phi = load_mock_file(argv[2], &n_points);
  theta = load_mock_file(argv[3], &n_points);
  
  for(i=0;i<n_points;i++){
    r[i] = sqrt(pow(x[i],2) + pow(y[i],2) + pow(z[i],2));
    theta[i] = acos(z[i]/r[i]);
    tmp = sqrt(x[i]*x[i] + y[i]*y[i]);
    phi[i] = acos(x[i]/tmp);
    if(y[i]<=0.0){
      phi[i] = 2.0*PI - phi[i];
    }	
  }

  /*dump results*/
  dump_mock_file(argv[4], r, n_points);  
  dump_mock_file(argv[5], phi, n_points);  
  dump_mock_file(argv[6], theta, n_points);  

  return 0;
}
