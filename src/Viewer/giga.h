#ifndef SRC_DATA_OF_OBJECT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct min_max_struct {
  double x_min;
  double x_max;
  double y_min;
  double y_max;
} min_max_t;

void count_vertexes_and_edges(char*, unsigned int*, unsigned int*, min_max_t*);
void get_vertexes_and_edges_data(char*, unsigned int, unsigned int, double**,
                                 unsigned int**);

#endif  // SRC_DATA_OF_OBJECT_H_
