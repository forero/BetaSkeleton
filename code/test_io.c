#include <stdio.h>
#include <stdlib.h>
#include "io_mock.h"

int main(int argc, char **argv){
  int n_points;
  float *data;
  float min, max;
  int i;
  min = 1E20;
  max =-1E20;


  fprintf(stdout, "Testing the IO routine with %s\n", argv[1]);
  data = load_mock_file(argv[1], &n_points);

  fprintf(stdout, "The number of points is %d\n", n_points);

  for(i=0;i<n_points;i++){
    if(data[i]<min)
      min = data[i];
    if(data[i]>max)
      max = data[i];
  }

  fprintf(stdout, "Minimum value: %e\n", min);
  fprintf(stdout, "Maximum value: %e\n", max);

  return 0;
}
