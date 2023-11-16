#ifndef GLVIEW_H
#define GLVIEW_H

#include <GL/gl.h>
#include <GL/glu.h>

#include <QOpenGLFunctions>
#include <QOpenGLWidget>

#include "stack.h"
#include "transformations.h"

#define PARALLEL 1     // параллельная
#define PERSPECTIVE 0  // центральная
#define COLOR 255      // коэффициент перевода цвета
#define POINT_DISABLED 0  // отсутствует отображение точки
#define POINT_SIRCLE 1  // отображение точки - круг
#define POINT_SQUARE 2  // отображение точки - квадрат
#define LINE_SOLID 0    // отображение линии - сплошная
#define LINE_DASHED 1  // отображение линии - пунктирная

class glView : public QOpenGLWidget {
 public:
  glView(QWidget *parent = nullptr);

  double back_red = 0;
  double back_green = 24;
  double back_blue = 116;
  double edge_red = 255;
  double edge_green = 0;
  double edge_blue = 255;
  double edge_width = 500;
  int edge_type = LINE_SOLID;
  double vertex_red = 0;
  double vertex_green = 0;
  double vertex_blue = 255;
  double vertex_size = 100;
  int vertex_type = POINT_DISABLED;

  int projectionType = PERSPECTIVE;
  double angle_x = 0;
  double angle_y = 0;
  double angle_z = 0;
  double x_mov = 0;
  double y_mov = 0;
  double z_mov = 0;
  double scale = 0.4;

  double *vertex_array = NULL;
  int vertices_coordinates = 0;
  node *index_stack = NULL;
  int poligon_counter = 0;

 protected:
  void initializeGL() override;
  void resizeGL(int width, int height) override;
  void paintGL() override;
};

#endif  // GLVIEW_H
