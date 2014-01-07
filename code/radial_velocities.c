#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "io_mock.h"

#define USAGE "./rv.x xp yp zp vx vy vz vr_outfile"

/*
  INPUTS:
  x position (comoving) [Mpc/h]
  y position (comoving) [Mpc/h]
  z position (comoving) [Mpc/h]
  x velocity (physical) [km/s]
  y velocity (physical) [km/s]
  z velocity (physical) [km/s]

  OUTPUT:
  radial velocity component (physical) [km/s]
*/
int main(int argc, char **argv){
  int n_points;
  int i;
  float *vr;
  float norm_r;
  float *x, *y, *z, *vx, *vy, *vz;

  if(argc!=8){
    fprintf(stderr, "%s\n", USAGE);
    exit(1);
  }

  /*load all the relevant data*/
  x = load_mock_file(argv[1], &n_points);
  y = load_mock_file(argv[2], &n_points);
  z = load_mock_file(argv[3], &n_points);
  vx = load_mock_file(argv[4], &n_points);
  vy = load_mock_file(argv[5], &n_points);
  vz = load_mock_file(argv[6], &n_points);

  if(!(vr=malloc(n_points * sizeof(float)))){
    fprintf(stderr, "Problem in the allocation of the radial velocity array\n");
    exit(1);
  }
  
  /*initialization*/
  for(i=0;i<n_points;i++){
    vr[i] = 0.0;
  }

  for(i=0;i<n_points;i++){
    norm_r  = sqrt(pow(x[i],2) + pow(y[i],2) + pow(z[i],2));    
    vr[i] = (x[i]*vx[i] + y[i]*vy[i] + z[i]*vz[i])/norm_r;
  }
  
  
  /*dump data*/
  dump_mock_file(argv[7], vr, n_points);

  return 0;
}
