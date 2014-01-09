#include <stdio.h>
#include <stdlib.h>
#include "io_mock.h"

/*
  INPUTS
  x position [file]
  y position [file]
  z position [file]
  skeleton pairs [file]

  OUTPUTS
  pair's length along x
  pair's lenght along y
  pair's lenght along z
*/

#define USAGE "./skeleton_shape.x x_file y_file z_file skel_clean_pair_file pair_lenght_x_file pair_lenght_y_file pair_lenght_z_file"

int main(int argc, char **argv){
  int n_points;
  int n_pairs;
  float *x, *y, *z;
  float *len_x, *len_y, *len_z;
  int *pairs;
  int i;

  if(argc!=8){
    fprintf(stderr, "USAGE: %s\n", USAGE) ;
    exit(1);
  }
  
  /*load raw data*/
  x = load_mock_file(argv[1], &n_points);
  y = load_mock_file(argv[2], &n_points);
  z = load_mock_file(argv[3], &n_points);
  pairs = load_skeleton(argv[4], &n_pairs);

  /*malloc data to dump*/
  if(!(len_x=malloc(n_pairs * sizeof(float)))){
    fprintf(stderr, "problem with len_x allocation\n");
    exit(1);
  }
  if(!(len_y=malloc(n_pairs * sizeof(float)))){
    fprintf(stderr, "problem with len_y allocation\n");
    exit(1);
  }
  if(!(len_z=malloc(n_pairs * sizeof(float)))){
    fprintf(stderr, "problem with len_z allocation\n");
    exit(1);
  }

  /*initialization*/
  for(i=0;i<n_pairs;i++){
    len_x[i] = -1;len_y[i] = -1; len_z[i] = -1;
  }

  /*compute the properties*/
  for(i=0;i<n_pairs;i++){
    pair_a = pairs[i*2];
    pair_b = pairs[i*2 + 1];
    
    len_x[i] = fabs(x[pair_b] - x[pair_a]);
    len_y[i] = fabs(y[pair_b] - y[pair_a]);
    len_z[i] = fabs(z[pair_b] - z[pair_a]);
  }

  /*dump the data*/
  dump_mock_file(argv[5], len_x, n_pairs);
  dump_mock_file(argv[6], len_x, n_pairs);
  dump_mock_file(argv[7], len_x, n_pairs);

  return 0;
}
