#include "giga.h"

void count_vertexes_and_edges(char *path, unsigned int *number_of_vertexes,
                              unsigned int *number_of_edges,
                              min_max_t *start_scale) {
  char buf[10000];
  FILE *fp = fopen(path, "r");
  if (fp != NULL) {
    int first = 1;
    while (fgets(buf, 10000, fp) != NULL) {
      if (strstr(buf, "v ") != NULL) {
        ++*number_of_vertexes;
        double x, y, z;
        if (sscanf(buf, "v %lf %lf %lf", &x, &y, &z) == 3) {
          if (first == 0) {
            if (x < start_scale->x_min) {
              start_scale->x_min = x;
            } else if (x > start_scale->x_max) {
              start_scale->x_max = x;
            }
            if (y < start_scale->y_min) {
              start_scale->y_min = y;
            } else if (y > start_scale->y_max) {
              start_scale->y_max = y;
            }
          } else {
            start_scale->x_min = x;
            start_scale->x_max = x;
            start_scale->y_min = y;
            start_scale->y_max = y;
            first = 0;
          }
        }
      } else if (strstr(buf, "f ") != NULL) {
        char sep[] = " \n\r";
        char *part = strtok(buf, sep);
        part = strtok(NULL, sep);
        while (part != NULL) {
          ++*number_of_edges;
          part = strtok(NULL, sep);
        }
      }
    }
    *number_of_edges *= 2;
    fclose(fp);
  }
}

void get_vertexes_and_edges_data(char *path, unsigned int number_of_vertexes,
                                 unsigned int number_of_edges,
                                 double **vertexes_data,
                                 unsigned int **edges_data) {
  unsigned int count_points_v = 0;
  unsigned int count_points_e = 0;
  int negative_vertexes = 0;
  *vertexes_data = malloc(sizeof(double) * (number_of_vertexes * 3));
  *edges_data = malloc(sizeof(unsigned int) * number_of_edges);
  char buf[10000];
  FILE *fp = fopen(path, "r");
  if (fp != NULL) {
    while (fgets(buf, 10000, fp) != NULL) {
      char sep[] = " \n\r";
      char *part = NULL;
      if (strstr(buf, "v ") != NULL) {
        ++negative_vertexes;
        part = strtok(buf, sep);
        part = strtok(NULL, sep);
        while (part != NULL) {
          (*vertexes_data)[count_points_v++] = strtod(part, NULL);
          part = strtok(NULL, sep);
        }
      } else if (strstr(buf, "f ") != NULL) {
        part = strtok(buf, sep);
        part = strtok(NULL, sep);
        double close_vertex = strtod(part, NULL);
        int next = 0;
        while (part != NULL) {
          double tmp = strtod(part, NULL);
          if (tmp < 0) {
            (*edges_data)[count_points_e] = negative_vertexes + tmp;
          } else {
            (*edges_data)[count_points_e] = --tmp;
          }
          if (next > 0) {
            (*edges_data)[count_points_e - 1] = (*edges_data)[count_points_e];
          }
          ++next;
          count_points_e += 2;
          part = strtok(NULL, sep);
        }
        if (close_vertex < 0) {
          (*edges_data)[count_points_e - 1] = negative_vertexes + close_vertex;
        } else {
          (*edges_data)[count_points_e - 1] = --close_vertex;
        }
      }
    }
    fclose(fp);
  }
}
