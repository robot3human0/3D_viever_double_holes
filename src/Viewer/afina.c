#include "afina.h"

#include <math.h>
#include <stdio.h>

void afina_move(double *vertexes, unsigned amount_of_vertexes, Axis_t offset) {
  for (size_t i = 0; i < amount_of_vertexes * 3; i += 3) {
    vertexes[i] += offset.x;
    vertexes[i + 1] += offset.y;
    vertexes[i + 2] += offset.z;
  }
}

void afina_rotate_x(double *vertexes, unsigned amount_of_vertexes,
                    double angle) {
  for (size_t i = 0; i < (amount_of_vertexes * 3); i += 3) {
    double y = vertexes[i + 1];
    double z = vertexes[i + 2];
    vertexes[i + 1] = y * cos(angle) - z * sin(angle);
    vertexes[i + 2] = y * sin(angle) + z * cos(angle);
  }
}

void afina_rotate_y(double *vertexes, unsigned amount_of_vertexes,
                    double angle) {
  for (size_t i = 0; i < (amount_of_vertexes * 3); i += 3) {
    double x = vertexes[i];
    double z = vertexes[i + 2];
    vertexes[i] = x * cos(angle) + z * sin(angle);
    vertexes[i + 2] = -x * sin(angle) + z * cos(angle);
  }
}

void afina_rotate_z(double *vertexes, unsigned amount_of_vertexes,
                    double angle) {
  for (size_t i = 0; i < (amount_of_vertexes * 3); i += 3) {
    double x = vertexes[i];
    double y = vertexes[i + 1];
    vertexes[i] = x * cos(angle) - y * sin(angle);
    vertexes[i + 1] = x * sin(angle) + y * cos(angle);
  }
}

void afina_scale(double *vertexes, unsigned amount_of_vertexes, double scale) {
  for (size_t i = 0; i < (amount_of_vertexes * 3); i++) {
    vertexes[i] *= scale;
  }
}
