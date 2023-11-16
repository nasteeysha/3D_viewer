#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gif_module/QtGifImage/src/gifimage/qgifimage.h>

#include <QFileDialog>
#include <QMainWindow>
#include <QSettings>
#include <QTimer>

#include "s21_objloader.h"

#define FRAMES_MAX 100

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  int edge_counter = 0;
  void saveSettings();
  void loadSettings();
  void load_vertex_Settings();
  void load_edge_Settings();
  void load_projection_Settings();
  void load_back_Settings();
  int check_loadSettings(double value_to_check, int lRange, int rRange);

 private slots:
  void on_file_pushButton_clicked();

  void on_projectionOrtho_radioButton_clicked();

  void on_projectionFrustum_radioButton_clicked();

  void on_angle_x_horizontalSlider_valueChanged(int value);
  void on_angle_y_horizontalSlider_valueChanged(int value);
  void on_angle_z_horizontalSlider_valueChanged(int value);

  void on_scale_horizontalSlider_valueChanged(int value);

  void on_move_x_horizontalSlider_valueChanged(int value);
  void on_move_y_horizontalSlider_valueChanged(int value);
  void on_move_z_horizontalSlider_valueChanged(int value);

  void on_back_red_horizontalSlider_valueChanged(int value);
  void on_back_green_horizontalSlider_valueChanged(int value);
  void on_back_blue_horizontalSlider_valueChanged(int value);

  void on_edge_red_horizontalSlider_valueChanged(int value);
  void on_edge_green_horizontalSlider_valueChanged(int value);
  void on_edge_blue_horizontalSlider_valueChanged(int value);

  void on_vertex_red_horizontalSlider_valueChanged(int value);
  void on_vertex_green_horizontalSlider_valueChanged(int value);
  void on_vertex_blue_horizontalSlider_valueChanged(int value);

  void on_vertex_size_horizontalSlider_valueChanged(int value);

  void on_vertexTypeSquare_radioButton_clicked();
  void on_vertexTypeSircle_radioButton_clicked();
  void on_vertexTypeDisabled_radioButton_clicked();

  void on_edge_width_horizontalSlider_valueChanged(int value);

  void on_edgeSolid_radioButton_clicked();

  void on_edgeDashed_radioButton_clicked();

  void on_screenshot_pushButton_clicked();

  void on_screencast_pushButton_clicked();

  void make_gif();

 private:
  Ui::MainWindow *ui;
  QTimer tmr;
  QSettings *settings;
  QImage frames[FRAMES_MAX];
  int frames_counter = 0;
};

#endif  // MAINWINDOW_H
