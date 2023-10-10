#ifndef SRC_AFINA_H_
#define SRC_AFINA_H_

typedef struct {
  double x;
  double y;
  double z;
} Axis_t;

void afina_move(double*, unsigned amount_of_vertexes, Axis_t offset);
void afina_rotate_x(double*, unsigned amount_of_vertexes, double angle);
void afina_rotate_y(double*, unsigned amount_of_vertexes, double angle);
void afina_rotate_z(double*, unsigned amount_of_vertexes, double angle);
void afina_scale(double*, unsigned amount_of_vertexes, double scale);

#endif  //  SRC_AFINA_H_
