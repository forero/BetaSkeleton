#ifndef __IO_MOCK
#define __IO_MOCK
#include <stdio.h>
#include <stdlib.h>

float * load_mock_file(char *filename, int *n_points);
void dump_mock_file(char *filename, float *data, int n_data);

#endif
