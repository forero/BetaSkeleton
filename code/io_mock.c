#include "io_mock.h"

void dump_mock_file(char *filename, float *data, int n_data){
  int dumb=4;
  FILE *out;

  if(!(out = fopen(filename, "w"))){
    fprintf(stderr, "problem opening file %s\n", filename);
    exit(1);  
  }
  
  fwrite(&dumb, 4, 1, out);
  fwrite(&n_data, sizeof(int), 1, out);
  fwrite(&dumb, 4, 1, out);

  fwrite(&dumb, 4, 1, out);
  fwrite(data, sizeof(float), n_data, out);
  fwrite(&dumb, 4, 1, out);

  fclose(out);
}



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

  fclose(in);
  return data;
}
