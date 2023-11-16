#include "glview.h"

glView::glView(QWidget *parent) : QOpenGLWidget(parent) {}

void glView::initializeGL() { glEnable(GL_DEPTH_TEST); }

void glView::resizeGL(int width, int height) {
  glViewport(0, 0, width, height);
}

void glView::paintGL() {
  // цвет фона и очищение буффера
  glClearColor(back_red / COLOR, back_green / COLOR, back_blue / COLOR, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // установка изначального центра
  double center[3] = {0, 0, 0};  // {x, y, z}

  if (vertices_coordinates > 0) {
    double *inner_vertex_array = NULL;
    while (inner_vertex_array == NULL)
      inner_vertex_array =
          (double *)malloc(sizeof(double) * vertices_coordinates);
    // коэф-ты для перспективы
    double fov = 60.0 * M_PI / 180;  // 60 угол в градусах
    double heapHeight = 1 / (2 * tan(fov / 2));
    // выбор проекции
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (projectionType == PERSPECTIVE) {
      glFrustum(-1, 1, -1, 1, heapHeight, 300);
    } else {
      glOrtho(-1, 1, -1, 1, -100, 100);
    }

    //    // заполнение массива для рисования
    for (int i = 0; i < vertices_coordinates; i++) {
      inner_vertex_array[i] = vertex_array[i];
    }

    // действия с моделью перед отрисовкой
    zoom_object(inner_vertex_array, vertices_coordinates, scale);

    if (projectionType == PERSPECTIVE)
      move_object(inner_vertex_array, vertices_coordinates, -(heapHeight * 3),
                  Z_AXIS, center);
    move_object(inner_vertex_array, vertices_coordinates, x_mov, X_AXIS,
                center);
    move_object(inner_vertex_array, vertices_coordinates, y_mov, Y_AXIS,
                center);
    move_object(inner_vertex_array, vertices_coordinates, z_mov, Z_AXIS,
                center);

    rotate_object(inner_vertex_array, vertices_coordinates, angle_x, X_AXIS,
                  center);
    rotate_object(inner_vertex_array, vertices_coordinates, angle_y, Y_AXIS,
                  center);
    rotate_object(inner_vertex_array, vertices_coordinates, angle_z, Z_AXIS,
                  center);

    // начала отрисовки
    glVertexPointer(3, GL_DOUBLE, 0, inner_vertex_array);
    glEnableClientState(GL_VERTEX_ARRAY);

    // отрисовка линий
    glColor3d(edge_red / COLOR, edge_green / COLOR, edge_blue / COLOR);
    glLineWidth(edge_width / 100);
    node *tmp = index_stack;
    if (edge_type == LINE_DASHED) {
      glEnable(GL_LINE_STIPPLE);
      glLineStipple(1, 0x00ff);
    }
    for (int i = 0; i < poligon_counter; i++) {
      glDrawElements(GL_LINES, tmp->size_of_array, GL_UNSIGNED_INT,
                     tmp->index_array);
      tmp = tmp->next_node;
    }
    if (edge_type == LINE_DASHED) glDisable(GL_LINE_STIPPLE);

    // отрисовка точек
    if (vertex_type != POINT_DISABLED) {
      if (vertex_type == POINT_SIRCLE) glEnable(GL_POINT_SMOOTH);
      glColor3d(vertex_red / COLOR, vertex_green / COLOR, vertex_blue / COLOR);
      glPointSize(vertex_size / 10);
      glDrawArrays(GL_POINTS, 0, (vertices_coordinates / 3));
      if (vertex_type == POINT_SIRCLE) glDisable(GL_POINT_SMOOTH);
    }

    // конец отрисовки
    glDisableClientState(GL_VERTEX_ARRAY);
    free(inner_vertex_array);
  }
}
