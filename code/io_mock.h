#ifndef __IO_MOCK
#define __IO_MOCK
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float * load_mock_file(char *filename, int *n_points);
void dump_mock_file(char *filename, float *data, int n_data);
int *load_skeleton(char *filename, int *n_data);

#endif
