#ifndef MYCLASS_H
#define MYCLASS_H
#define GL_SILENCE_DEPRECATION

#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QtOpenGL>

extern "C" {
#include "afina.h"
#include "giga.h"
}

class MyClass : public QOpenGLWidget {
  Q_OBJECT

 public:
  void drawCube(float a);
  char *path;
  unsigned int count_of_vertexes;
  unsigned int count_of_edges;
  double *vertexes_data;
  unsigned int *edges_data;
  float xRot, yRot, zRot;
  QPoint mPos;
  MyClass(QWidget *parent = nullptr);
  ~MyClass();
  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void open_file();
  Axis_t positions;
  Axis_t offsets;
  Axis_t angles;
  int vertice_type;
  int vertices_size;
  double scale;
  void center();
  void translate();
  void rotate();
  void scale_model();
  min_max_t start_scale;
  bool isOrthogonal;
  void changeProjection();
  QColor vertices_color;
  QColor edges_color;
  QColor background_color;
  bool line_type;
  double line_thickness = 1;

 signals:
  void mousetrigger(double x, double y);

 private:
};

#endif  // MYCLASS_H
