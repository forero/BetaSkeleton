#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "io_mock.h"

/*
  INPUTS
  ngl_file position [file]
  skeleton pairs [file]

  OUTPUTS
  pair's length along x
  pair's lenght along y
  pair's lenght along z
*/

#define USAGE "./skel_shape.x ngl_file skel_clean_pair_file pair_lenght_x_file pair_lenght_y_file pair_lenght_z_file"

int main(int argc, char **argv){
  int n_points;
  int n_pairs;
  int pair_a, pair_b;
  float *ngl_data;
  float *len_x, *len_y, *len_z;
  int *pairs;
  int i;

  if(argc!=6){
    fprintf(stderr, "USAGE: %s\n", USAGE) ;
    exit(1);
  }
  
  /*load raw data*/
  ngl_data = load_ngl_file(argv[1], &n_points);
  pairs = load_skeleton(argv[2], &n_pairs);

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
    len_x[i] = fabs(ngl_data[3*pair_b + 0] - ngl_data[3*pair_a + 0]);
    len_y[i] = fabs(ngl_data[3*pair_b + 1] - ngl_data[3*pair_a + 1]);
    len_z[i] = fabs(ngl_data[3*pair_b + 2] - ngl_data[3*pair_a + 2]);
    /*
    if(i==9){
      fprintf(stdout, "pair_a pair_b [%d %d]\n", pair_a, pair_b);
      fprintf(stdout, "paira [x y z] = [%f %f %f]\n", 
	      ngl_data[3*pair_a + 0],
	      ngl_data[3*pair_a + 1],
	      ngl_data[3*pair_a + 2]	      );
    }
    */
  }

  /*dump the data*/
  dump_mock_file(argv[3], len_x, n_pairs);
  dump_mock_file(argv[4], len_y, n_pairs);
  dump_mock_file(argv[5], len_z, n_pairs);

  return 0;
}
