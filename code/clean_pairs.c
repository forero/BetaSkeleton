#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "io_mock.h"

/*
  INPUT:
  skeleton file (pairs of integers)

  OUTPUT:
  clean skeleton file (pairs of integers) without repeated pairs
*/

#define USAGE "./clean.x skeleton_in skeleton_out"
#define TRUE 1
#define FALSE 0

int find_in_list(int *first, int *second, int search_first, int search_second, int n_points);
int main(int argc, char **argv){
  int *data_in;
  int *single;
  int *first;
  int *second;
  int n_points;
  int i;
  int place_in_list;
  FILE *out;

  if(argc!=3){
    fprintf(stderr, "USAGE: %s\n", USAGE);
    exit(1);
  }

  data_in = load_skeleton(argv[1], &n_points);

  /*
    allocates the array to check whether a pair is duplicated
    if duplicated, it sets the flag to zero.
   */

  if(!(single=malloc(sizeof(int) * n_points))){
    fprintf(stderr, "problem in status allocation\n");
    exit(1);
  }

  for(i=0;i<n_points;i++){
    single[i] = TRUE;
  }  

  /*auxiliary arrays to hold the first and integer in the pair. The first array is ranked
    from low to high values*/
  if(!(first=malloc(sizeof(int) * n_points))){
    fprintf(stderr, "problem in auxallocation\n");
    exit(1);
  }  

  if(!(second=malloc(sizeof(int) * n_points))){
    fprintf(stderr, "problem in auxallocation\n");
    exit(1);
  }  


  for(i=0;i<n_points;i++){
    first[i] = data_in[2*i];
    second[i] = data_in[2*i + 1];
  }
  
  /*actual cleaning*/
  for(i=0;i<n_points;i++){
    if(single[i]){
      place_in_list = find_in_list(first, second, first[i], second[i], n_points);
     
      if(place_in_list==-1){
	fprintf(stderr, "error in searching algorithm\n");
	exit(1);
      }
      single[place_in_list] = FALSE;
    }
  }


  /*dump the good pairs into a file*/
  if(!(out=fopen(argv[2],"w"))){
    fprintf(stderr, "problem opening file %s\n", argv[2]);
    exit(1);
  }  
  for(i=0;i<n_points;i++){
    if(single[i]){
      fprintf(out, "%d %d\n", first[i], second[i]);
    }
  }
  fclose(out);

  free(single);
  free(first);
  free(second);
  return 0;
}


int find_in_list(int *first, int *second, int search_first, int search_second, int n_points){
  int i;
  int found;
  int index;
  found = FALSE;

  index = -1;
  i=0;
  do{
    if(first[i]==search_second && second[i]==search_first){
      found = TRUE;
      index = i;
    }
    i++;
  }while(!found && i<n_points);

  return index;
}
