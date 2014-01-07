#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "io_mock.h"
#define USAGE "./sub_sample.x filein_x filein_y filein_z fileout frac\n"

/*
  This program reads a list of three files [x,y,z] and selects a fraction 
  "frac" of this points to be written in the file fileout
*/

int main(int argc, char **argv){
  float frac;
  FILE *in;
  FILE *out;
  float * x, * y, * z;
  int n_points;
  int i;
  float tmp;

  x = load_mock_file(argv[1], &n_points);
  y = load_mock_file(argv[2], &n_points);
  z = load_mock_file(argv[3], &n_points);
  frac = atof(argv[5]);

  srand48(frac*1000);


  if(!(out=fopen(argv[4], "w"))){
    fprintf(stderr, "Problem opening file %s\n", argv[4]);
    exit(1);
  }

  for(i=0;i<n_points;i++){
    tmp = drand48();
    if(tmp<frac){
      fprintf(out, "%e %e %e\n", x[i], y[i], z[i]);
    }
  }

  fclose(out);

  return 0;
}
