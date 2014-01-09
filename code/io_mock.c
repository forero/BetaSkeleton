#include "io_mock.h"


float *load_ngl_file(char *filename, int *n_data){
  int n_lines;
  FILE *in;
  int i,c;
  float *ngl_data;
   
  if(!(in=fopen(filename, "r"))){
    fprintf(stderr, "problem opening file %s\n", filename);
    exit(1);
  }

  n_lines = 0;
  do{
    c=getc(in);
    if(c=='\n')
      n_lines++;
  }while(c!=EOF);
  fprintf(stdout, "there are %d lines to read\n", n_lines);
  rewind(in);
  
  if(!(ngl_data=malloc(sizeof(float) * 3 * n_lines))){
    fprintf(stderr, "problem allocating gnl data data\n");
    exit(1);
  }
  
  for(i=0;i<n_lines;i++){
    fscanf(in, "%f %f %f\n", 
	   &(ngl_data[3*i + 0]), &(ngl_data[3*i + 1]), &(ngl_data[3*i + 2]));
  }  
  fclose(in);
  
  *n_data = n_lines;
  return ngl_data;
}

int *load_skeleton(char *filename, int *n_data){
  int n_lines;
  FILE *in;
  int i,c;
  int *skel_data;

  if(!(in=fopen(filename, "r"))){
    fprintf(stderr, "problem opening file %s\n", filename);
    exit(1);
  }

  n_lines = 0;
  do{
    c=getc(in);
    if(c=='\n')
      n_lines++;
  }while(c!=EOF);
  fprintf(stdout, "there are %d lines to read\n", n_lines);
  rewind(in);
  
  if(!(skel_data=malloc(sizeof(int) * 2 * n_lines))){
    fprintf(stderr, "problem allocating skeleton pair data\n");
    exit(1);
  }
  
  for(i=0;i<n_lines;i++){
    fscanf(in, "%d %d\n", &(skel_data[2*i + 0]), &(skel_data[2*i + 1]));
  }  
  fclose(in);

  *n_data = n_lines;
  return skel_data;
}


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
