#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <form.h>

#include <QAudioOutput>
#include <QColorDialog>
#include <QDesktopServices>
#include <QFileDialog>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QSettings>

#include "qgifimage.h"

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
  void mouse_rotation(double x, double y);
  void wheelEvent(QWheelEvent *event);
  void save_settings();
  void load_settings();

 private slots:
  void on_pushButton_clicked();

  void on_actionDocumentation_triggered();

  void on_actionAuthors_triggered();

  void on_translateButton_clicked();

  void on_rotateButton_clicked();

  void on_scaleButton_clicked();

  void on_none_radio_clicked(bool checked);

  void on_circle_radio_clicked(bool checked);

  void on_square_radio_clicked(bool checked);

  void on_vert_size_line_textChanged(const QString &arg1);

  void on_vertColorButton_clicked();

  void on_smooth_radio_clicked(bool checked);

  void on_stippled_radio_clicked(bool checked);

  void on_thick_line_textChanged(const QString &arg1);

  void on_edgeColorButton_clicked();

  void on_pushButton_2_clicked();

  void on_orthogonalRadio_clicked(bool checked);
  void on_perspectiveRadio_clicked(bool checked);
  void on_actiongif_triggered();
  void saveGifFrame();
  void on_actionImage_triggered();

 private:
  QMediaPlayer *player;
  QAudioOutput *audio_output;

  Ui::MainWindow *ui;
  QSettings *settings;
  Form form;

  QGifImage *gif;
  QImage *frame;
  QTimer *timer;
  QString gifSavePath;
  int time;
};
#endif  // MAINWINDOW_H
