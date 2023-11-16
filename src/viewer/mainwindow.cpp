#include "mainwindow.h"

#include "glview.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(&tmr, SIGNAL(timeout()), this, SLOT(make_gif()));
  settings = new QSettings("School 21", "viewer", this);
  loadSettings();
}

MainWindow::~MainWindow() {
  saveSettings();
  free_model_data(&(ui->openGLWidget->vertex_array),
                  &(ui->openGLWidget->vertices_coordinates),
                  &(ui->openGLWidget->index_stack),
                  &(ui->openGLWidget->poligon_counter));
  delete ui;
}

void MainWindow::saveSettings() {
  settings->setValue("back_red", ui->openGLWidget->back_red);
  settings->setValue("back_green", ui->openGLWidget->back_green);
  settings->setValue("back_blue", ui->openGLWidget->back_blue);
  settings->setValue("edge_red", ui->openGLWidget->edge_red);
  settings->setValue("edge_green", ui->openGLWidget->edge_green);
  settings->setValue("edge_blue", ui->openGLWidget->edge_blue);
  settings->setValue("edge_width", ui->openGLWidget->edge_width);
  settings->setValue("edge_type", ui->openGLWidget->edge_type);
  settings->setValue("vertex_red", ui->openGLWidget->vertex_red);
  settings->setValue("vertex_green", ui->openGLWidget->vertex_green);
  settings->setValue("vertex_blue", ui->openGLWidget->vertex_blue);
  settings->setValue("vertex_size", ui->openGLWidget->vertex_size);
  settings->setValue("vertex_type", ui->openGLWidget->vertex_type);
  settings->setValue("projectionType", ui->openGLWidget->projectionType);
}

void MainWindow::loadSettings() {
  load_vertex_Settings();
  load_edge_Settings();
  load_projection_Settings();
  load_back_Settings();
}
void MainWindow::load_vertex_Settings() {
  ui->openGLWidget->vertex_red = settings->value("vertex_red", 0).toDouble();
  if (check_loadSettings(ui->openGLWidget->vertex_red, 0, 255) == 1)
    ui->openGLWidget->vertex_red = 0;
  ui->vertex_red_horizontalSlider->setValue(ui->openGLWidget->vertex_red);

  ui->openGLWidget->vertex_green =
      settings->value("vertex_green", 0).toDouble();
  if (check_loadSettings(ui->openGLWidget->vertex_green, 0, 255) == 1)
    ui->openGLWidget->vertex_green = 0;
  ui->vertex_green_horizontalSlider->setValue(ui->openGLWidget->vertex_green);

  ui->openGLWidget->vertex_blue =
      settings->value("vertex_blue", 255).toDouble();
  if (check_loadSettings(ui->openGLWidget->vertex_blue, 0, 255) == 1)
    ui->openGLWidget->vertex_blue = 255;
  ui->vertex_blue_horizontalSlider->setValue(ui->openGLWidget->vertex_blue);

  ui->openGLWidget->vertex_size =
      settings->value("vertex_size", 100).toDouble();
  if (check_loadSettings(ui->openGLWidget->vertex_size, 10, 300) == 1)
    ui->openGLWidget->vertex_size = 100;
  ui->vertex_size_horizontalSlider->setValue(ui->openGLWidget->vertex_size);

  ui->openGLWidget->vertex_type =
      settings->value("vertex_type", POINT_DISABLED).toInt();
  if (check_loadSettings(ui->openGLWidget->vertex_type, 0, 2) == 1)
    ui->openGLWidget->vertex_type = POINT_DISABLED;
  switch (ui->openGLWidget->vertex_type) {
    case POINT_SIRCLE:
      ui->vertexTypeSircle_radioButton->setChecked(true);
      ui->vertexTypeSquare_radioButton->setChecked(false);
      ui->vertexTypeDisabled_radioButton->setChecked(false);
      break;
    case POINT_SQUARE:
      ui->vertexTypeSircle_radioButton->setChecked(false);
      ui->vertexTypeSquare_radioButton->setChecked(true);
      ui->vertexTypeDisabled_radioButton->setChecked(false);
      break;
    default:
      ui->vertexTypeSircle_radioButton->setChecked(false);
      ui->vertexTypeSquare_radioButton->setChecked(false);
      ui->vertexTypeDisabled_radioButton->setChecked(true);
      break;
  }
}

void MainWindow::load_edge_Settings() {
  ui->openGLWidget->edge_red = settings->value("edge_red", 255).toDouble();
  if (check_loadSettings(ui->openGLWidget->edge_red, 0, 255) == 1)
    ui->openGLWidget->edge_red = 255;
  ui->edge_red_horizontalSlider->setValue(ui->openGLWidget->edge_red);

  ui->openGLWidget->edge_green = settings->value("edge_green", 0).toDouble();
  if (check_loadSettings(ui->openGLWidget->edge_green, 0, 255) == 1)
    ui->openGLWidget->edge_green = 0;
  ui->edge_green_horizontalSlider->setValue(ui->openGLWidget->edge_green);

  ui->openGLWidget->edge_blue = settings->value("edge_blue", 255).toDouble();
  if (check_loadSettings(ui->openGLWidget->edge_blue, 0, 255) == 1)
    ui->openGLWidget->edge_blue = 255;
  ui->edge_blue_horizontalSlider->setValue(ui->openGLWidget->edge_blue);

  ui->openGLWidget->edge_width = settings->value("edge_width", 500).toDouble();
  if (check_loadSettings(ui->openGLWidget->edge_width, 1, 1000) == 1)
    ui->openGLWidget->edge_width = 500;
  ui->edge_width_horizontalSlider->setValue(ui->openGLWidget->edge_width);

  ui->openGLWidget->edge_type =
      settings->value("edge_type", LINE_SOLID).toInt();
  if (check_loadSettings(ui->openGLWidget->edge_type, 0, 1) == 1)
    ui->openGLWidget->edge_type = LINE_SOLID;
  switch (ui->openGLWidget->edge_type) {
    case PARALLEL:
      ui->edgeDashed_radioButton->setChecked(true);
      ui->edgeSolid_radioButton->setChecked(false);
      break;
    default:
      ui->edgeDashed_radioButton->setChecked(false);
      ui->edgeSolid_radioButton->setChecked(true);
      break;
  }
}

void MainWindow::load_projection_Settings() {
  ui->openGLWidget->projectionType =
      settings->value("projectionType", PERSPECTIVE).toInt();
  if (check_loadSettings(ui->openGLWidget->projectionType, 0, 1) == 1)
    ui->openGLWidget->projectionType = PERSPECTIVE;
  switch (ui->openGLWidget->projectionType) {
    case PARALLEL:
      ui->projectionFrustum_radioButton->setChecked(false);
      ui->projectionOrtho_radioButton->setChecked(true);
      break;
    default:
      ui->projectionOrtho_radioButton->setChecked(false);
      ui->projectionFrustum_radioButton->setChecked(true);
      break;
  }
}

void MainWindow::load_back_Settings() {
  ui->openGLWidget->back_red = settings->value("back_red", 0).toDouble();
  if (check_loadSettings(ui->openGLWidget->back_red, 0, 255) == 1)
    ui->openGLWidget->back_red = 0;
  ui->back_red_horizontalSlider->setValue(ui->openGLWidget->back_red);

  ui->openGLWidget->back_green = settings->value("back_green", 24).toDouble();
  if (check_loadSettings(ui->openGLWidget->back_green, 0, 255) == 1)
    ui->openGLWidget->back_green = 24;
  ui->back_green_horizontalSlider->setValue(ui->openGLWidget->back_green);

  ui->openGLWidget->back_blue = settings->value("back_blue", 116).toDouble();
  if (check_loadSettings(ui->openGLWidget->back_blue, 0, 255) == 1)
    ui->openGLWidget->back_blue = 116;
  ui->back_blue_horizontalSlider->setValue(ui->openGLWidget->back_blue);
}

int MainWindow::check_loadSettings(double value_to_check, int lRange,
                                   int rRange) {
  int check_color_error = 0;  // 1 - error, 0 - normal
  if (value_to_check > rRange || value_to_check < lRange) {
    check_color_error = 1;
  }
  return check_color_error;
}

void MainWindow::on_file_pushButton_clicked() {
  QString fileStr =
      QFileDialog::getOpenFileName(this, "", "obj", "Object files (*.obj)");
  QByteArray ba = fileStr.toLocal8Bit();
  char *tmpStr = ba.data();
  if (load_array(tmpStr, &(ui->openGLWidget->vertex_array),
                 &(ui->openGLWidget->vertices_coordinates),
                 &(ui->openGLWidget->index_stack),
                 &(ui->openGLWidget->poligon_counter)) == 0) {
    QString vertexStr =
        QString::number(ui->openGLWidget->vertices_coordinates / 3);
    QString polygonStr = QString::number(ui->openGLWidget->poligon_counter);
    ui->statusBar->showMessage("Название файла: " + fileStr + " | Вершин: " +
                               vertexStr + " | Полигонов: " + polygonStr);
    ui->openGLWidget->update();
  } else {
    ui->statusBar->showMessage("Что-то не так с объектным файлом");
  }
}

void MainWindow::on_projectionOrtho_radioButton_clicked() {
  ui->openGLWidget->projectionType = 1;
  ui->openGLWidget->update();
}

void MainWindow::on_projectionFrustum_radioButton_clicked() {
  ui->openGLWidget->projectionType = 0;
  ui->openGLWidget->update();
}

void MainWindow::on_angle_x_horizontalSlider_valueChanged(int value) {
  ui->openGLWidget->angle_x = value;
  ui->openGLWidget->update();
}

void MainWindow::on_angle_y_horizontalSlider_valueChanged(int value) {
  ui->openGLWidget->angle_y = value;
  ui->openGLWidget->update();
}

void MainWindow::on_angle_z_horizontalSlider_valueChanged(int value) {
  ui->openGLWidget->angle_z = value;
  ui->openGLWidget->update();
}

void MainWindow::on_scale_horizontalSlider_valueChanged(int value) {
  double scale = value;
  ui->openGLWidget->scale = scale / 100;
  ui->openGLWidget->update();
}

void MainWindow::on_move_x_horizontalSlider_valueChanged(int value) {
  double x_mov = value;
  ui->openGLWidget->x_mov = x_mov / 100;
  ui->openGLWidget->update();
}

void MainWindow::on_move_y_horizontalSlider_valueChanged(int value) {
  double y_mov = value;
  ui->openGLWidget->y_mov = y_mov / 100;
  ui->openGLWidget->update();
}

void MainWindow::on_move_z_horizontalSlider_valueChanged(int value) {
  double z_mov = value;
  ui->openGLWidget->z_mov = z_mov / 100;
  ui->openGLWidget->update();
}

void MainWindow::on_back_red_horizontalSlider_valueChanged(int value) {
  double back_red = value;
  ui->openGLWidget->back_red = back_red;
  ui->openGLWidget->update();
}

void MainWindow::on_back_green_horizontalSlider_valueChanged(int value) {
  double back_green = value;
  ui->openGLWidget->back_green = back_green;
  ui->openGLWidget->update();
}

void MainWindow::on_back_blue_horizontalSlider_valueChanged(int value) {
  double back_blue = value;
  ui->openGLWidget->back_blue = back_blue;
  ui->openGLWidget->update();
}

void MainWindow::on_edge_red_horizontalSlider_valueChanged(int value) {
  double edge_red = value;
  ui->openGLWidget->edge_red = edge_red;
  ui->openGLWidget->update();
}

void MainWindow::on_edge_green_horizontalSlider_valueChanged(int value) {
  double edge_green = value;
  ui->openGLWidget->edge_green = edge_green;
  ui->openGLWidget->update();
}

void MainWindow::on_edge_blue_horizontalSlider_valueChanged(int value) {
  double edge_blue = value;
  ui->openGLWidget->edge_blue = edge_blue;
  ui->openGLWidget->update();
}

void MainWindow::on_vertex_red_horizontalSlider_valueChanged(int value) {
  double vertex_red = value;
  ui->openGLWidget->vertex_red = vertex_red;
  ui->openGLWidget->update();
}

void MainWindow::on_vertex_green_horizontalSlider_valueChanged(int value) {
  double vertex_green = value;
  ui->openGLWidget->vertex_green = vertex_green;
  ui->openGLWidget->update();
}

void MainWindow::on_vertex_blue_horizontalSlider_valueChanged(int value) {
  double vertex_blue = value;
  ui->openGLWidget->vertex_blue = vertex_blue;
  ui->openGLWidget->update();
}

void MainWindow::on_vertex_size_horizontalSlider_valueChanged(int value) {
  double vertex_size = value;
  ui->openGLWidget->vertex_size = vertex_size;
  ui->openGLWidget->update();
}

void MainWindow::on_vertexTypeSquare_radioButton_clicked() {
  ui->openGLWidget->vertex_type = POINT_SQUARE;
  ui->openGLWidget->update();
}

void MainWindow::on_vertexTypeSircle_radioButton_clicked() {
  ui->openGLWidget->vertex_type = POINT_SIRCLE;
  ui->openGLWidget->update();
}

void MainWindow::on_vertexTypeDisabled_radioButton_clicked() {
  ui->openGLWidget->vertex_type = POINT_DISABLED;
  ui->openGLWidget->update();
}

void MainWindow::on_edge_width_horizontalSlider_valueChanged(int value) {
  double edge_width = value;
  ui->openGLWidget->edge_width = edge_width;
  ui->openGLWidget->update();
}

void MainWindow::on_edgeSolid_radioButton_clicked() {
  ui->openGLWidget->edge_type = LINE_SOLID;
  ui->openGLWidget->update();
}

void MainWindow::on_edgeDashed_radioButton_clicked() {
  ui->openGLWidget->edge_type = LINE_DASHED;
  ui->openGLWidget->update();
}

void MainWindow::on_screenshot_pushButton_clicked() {
  QString file =
      QFileDialog::getSaveFileName(this, "", "", "Images (*.jpeg *.bmp)");
  ui->openGLWidget->grab().save(file, NULL, 100);
}

void MainWindow::on_screencast_pushButton_clicked() {
  if (frames_counter == 0) tmr.start(100);
}

void MainWindow::make_gif() {
  frames[frames_counter] = ui->openGLWidget->grab().toImage().scaled(771, 771);
  frames_counter++;
  if (frames_counter == FRAMES_MAX) {
    tmr.stop();
    QGifImage *gif_image = new QGifImage;
    gif_image->setDefaultDelay(100);
    for (int i = 0; i < frames_counter; i++) {
      gif_image->addFrame(frames[i], gif_image->defaultDelay());
    }
    QString file = QFileDialog::getSaveFileName(this, "", "", "GIF (*.gif)");
    gif_image->save(file);
    gif_image->~QGifImage();
    frames_counter = 0;
  }
}
