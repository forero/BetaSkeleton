#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "io_mock.h"
#define USAGE "./cat2ngl.x x_file y_file z_file m_file ngl_file m_filter fraction"

/*
  INPUT:
  Files for:
  x position 
  y position 
  z position 
  m mass 
  m_filter: filter in mass, only points with m>m_filter are included
  fraction: filter a fraction of the data.

  OUTPUT:
  NGL file: ASCII file with three columns corresponding to x,y,z
*/


int main(int argc, char **argv){
  int n_points;
  float *r, *phi, *theta;
  float *x, *y, *z, *mass;
  float mass_filter, frac;
  float tmp;
  int n_in;
  int i;
  FILE *out;

  if(argc!=8){
    fprintf(stderr, "USAGE: %s\n", USAGE);
    exit(1);
  }

  /*load raw data*/
  x = load_mock_file(argv[1], &n_points);
  y = load_mock_file(argv[2], &n_points);
  z = load_mock_file(argv[3], &n_points);
  mass = load_mock_file(argv[4], &n_points);
  mass_filter = atof(argv[6]);
  frac = atof(argv[7]);

  fprintf(stdout, "Filtering with mass:%e\n", mass_filter);
  fprintf(stdout, "Filtering a fraction:%f\n", frac);


  /*writes data*/
  if(!(out=fopen(argv[5], "w"))){
    fprintf(stderr, "Problem opening file %s\n", argv[5]);
    exit(1);
  }
 
  srand48(n_points);

  n_in=0;
  for(i=0;i<n_points;i++){
    tmp = drand48();
    if((mass[i]> mass_filter) && (tmp<frac)){
      fprintf(out, "%f %f %f\n", x[i], y[i], z[i]);
      n_in++;
    }
  }

  fprintf(stdout, "The number of selected points is %d\n", n_in);

  fclose(out);


  return 0;
}
