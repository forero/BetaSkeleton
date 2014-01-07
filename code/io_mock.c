#include "io_mock.h"

float *load_mock_file(char *filename, int *n_data){
  float *data;
  int n_points;
  int dumb;
  FILE *in;

  if(!(in = fopen(filename, "r"))){
    fprintf(stderr, "problem opening file %s\n", filename);
    exit(1);  
  }
  
  fread(&dumb, 4, 1, in);
  fread(&n_points, sizeof(int), 1, in);
  fread(&dumb, 4, 1, in);

  *n_data = n_points;

  if(!(data=malloc(sizeof(float) * n_points))){
    fprintf(stderr, "Problem of data allocation in io_mock.c\n");
    exit(1);
}

  fread(&dumb, 4, 1, in);
  fread(data, sizeof(float), n_points, in);
  fread(&dumb, 4, 1, in);
 
  return data;
}
