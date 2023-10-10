#include "myclass.h"

#include <QDebug>

MyClass::MyClass(QWidget* parent) : QOpenGLWidget(parent) {
  path = nullptr;
  count_of_vertexes = 0;
  count_of_edges = 0;
  vertexes_data = nullptr;
  edges_data = nullptr;
  min_max_t start_scale = {.0, .0, .0, .0};
  positions = {.0, .0, .0};
  offsets = {.0, .0, .0};
  angles = {.0, .0, .0};
  vertice_type = 0;
  vertices_size = 0;
  isOrthogonal = true;
  vertices_color = Qt::green;
  edges_color = Qt::green;
  background_color = Qt::white;
  line_type = false;
  line_thickness = 1;
}

MyClass::~MyClass() {
  free(vertexes_data);
  free(edges_data);
}

void MyClass::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslated(0., 0., -2.);
}

void MyClass::resizeGL(int w, int h) {}

void MyClass::changeProjection() {
  if (isOrthogonal) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double max = (start_scale.x_max * 1.5);
    glOrtho(-max, max, -max, max, -99999999999, 99999999999);
  } else {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double max = (start_scale.x_max * 1.5);
    glOrtho(-max, max, -max, max, -99999999999, 99999999999);
    float fov = 5.0 * M_PI / 180;
    float heapHeight = 580 / (2 * tan(fov / 2));
    float far = 100000;
    glFrustum(-510, 510, -580, 580, heapHeight, far);
  }
}

void MyClass::paintGL() {
  changeProjection();
  glClearColor(background_color.redF(), background_color.greenF(),
               background_color.blueF(), background_color.alphaF());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glVertexPointer(3, GL_DOUBLE, 0, vertexes_data);
  glEnableClientState(GL_VERTEX_ARRAY);
  if (vertice_type != 0) {
    if (vertice_type == 1) {
      glEnable(GL_POINT_SMOOTH);
    } else {
      glDisable(GL_POINT_SMOOTH);
    }
    glPointSize(vertices_size);
    glColor3d(vertices_color.redF(), vertices_color.greenF(),
              vertices_color.blueF());
    glDrawArrays(GL_POINTS, 0, count_of_vertexes);
  }
  glColor3d(edges_color.redF(), edges_color.greenF(), edges_color.blueF());
  glLineWidth(line_thickness);
  glLineStipple(1, 0x0101);
  if (line_type) {
    glEnable(GL_LINE_STIPPLE);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
  glDrawElements(GL_LINES, count_of_edges, GL_UNSIGNED_INT, edges_data);
  glDisableClientState(GL_VERTEX_ARRAY);
}

void MyClass::center() {
  Axis_t neg_positions = {-positions.x, -positions.y, -positions.z};
  afina_move(vertexes_data, count_of_vertexes, neg_positions);
}

void MyClass::open_file() {
  positions = {.0, .0, .0};
  offsets = {.0, .0, .0};
  angles = {.0, .0, .0};
  scale = 1.0;
  if (vertexes_data) {
    count_of_vertexes = 0;
    free(vertexes_data);
  }
  if (edges_data) {
    count_of_edges = 0;
    free(edges_data);
  }
  count_vertexes_and_edges(path, &count_of_vertexes, &count_of_edges,
                           &start_scale);
  get_vertexes_and_edges_data(path, count_of_vertexes, count_of_edges,
                              &vertexes_data, &edges_data);
  update();
}

void MyClass::mousePressEvent(QMouseEvent* mo) { mPos = mo->pos(); }

void MyClass::mouseMoveEvent(QMouseEvent* apEvent) {
  double xMouseRot = (0.01 / M_PI * (apEvent->pos().y() - mPos.y()) + angles.x);
  double yMouseRot = (0.01 / M_PI * (apEvent->pos().x() - mPos.x()) + angles.y);
  emit mousetrigger(xMouseRot, yMouseRot);
}

void MyClass::translate() {
  positions.x += offsets.x;
  positions.y += offsets.y;
  positions.z += offsets.z;
  afina_move(vertexes_data, count_of_vertexes, offsets);
  update();
}

void MyClass::rotate() {
  center();
  angles.x = angles.x * M_PI / 180;
  angles.y = angles.y * M_PI / 180;
  angles.z = angles.z * M_PI / 180;
  afina_rotate_y(vertexes_data, count_of_vertexes, angles.y);
  afina_rotate_x(vertexes_data, count_of_vertexes, angles.x);
  afina_rotate_z(vertexes_data, count_of_vertexes, angles.z);
  afina_move(vertexes_data, count_of_vertexes, positions);
  update();
}

void MyClass::scale_model() {
  center();
  afina_scale(vertexes_data, count_of_vertexes, scale);
  afina_move(vertexes_data, count_of_vertexes, positions);
  update();
}
