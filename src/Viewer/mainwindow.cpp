#include "mainwindow.h"

#include <QDebug>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  player = new QMediaPlayer;
  audio_output = new QAudioOutput;
  player->setAudioOutput(audio_output);
  player->setSource(QUrl("qrc:/new/prefix1/gandolf_sax.mp3"));
  audio_output->setVolume(50);
  player->setLoops(-1);
  player->play();
  ui->setupUi(this);
  setFixedSize(1313, 847);
  connect(ui->widget, &MyClass::mousetrigger, this,
          &MainWindow::mouse_rotation);
  settings = new QSettings("Viewer", "3DViewer", this);
  load_settings();
}

MainWindow::~MainWindow() {
  save_settings();
  delete ui;
}

void MainWindow::wheelEvent(QWheelEvent *event) {
  double scale = 1.1;
  ui->widget->center();
  if (event->angleDelta().y() > 0) {
    afina_scale(ui->widget->vertexes_data, ui->widget->count_of_vertexes,
                scale);
  } else if (event->angleDelta().y() < 0) {
    afina_scale(ui->widget->vertexes_data, ui->widget->count_of_vertexes,
                scale - 0.2);
  }
  afina_move(ui->widget->vertexes_data, ui->widget->count_of_vertexes,
             ui->widget->positions);
  ui->widget->update();
}

void MainWindow::mouse_rotation(double x, double y) {
  x = x > .0 ? fmod(x, 2. * M_PI) : fmod(x, -2. * M_PI);
  y = y > .0 ? fmod(y, 2. * M_PI) : fmod(y, -2. * M_PI);
  ui->widget->angles.x = x;
  ui->widget->angles.y = y;
  ui->widget->rotate();
  ui->widget->update();
}

void MainWindow::on_pushButton_clicked() {
  QString Qpath;
  Qpath =
      QFileDialog::getOpenFileName(this, NULL, QDir::homePath(), "OBJ (*.obj)");
  if (!Qpath.isNull()) {
    ui->widget->path =
        (Qpath.toLocal8Bit()).data();  // QString->QByteArray->char*
    ui->widget->open_file();
    ui->label_name->setText("File name: " +
                            Qpath.sliced(Qpath.lastIndexOf('/') + 1));
    ui->label_vertexes->setText("Number of vertexes: " +
                                QString::number(ui->widget->count_of_vertexes));
    ui->label_edges->setText("Number of edges: " +
                             QString::number(ui->widget->count_of_edges / 2));
  }
}

void MainWindow::on_actionDocumentation_triggered() {
  QString readme_path =
      "file:///" + QCoreApplication::applicationDirPath() + "/readme.html";
  QDesktopServices::openUrl(QUrl(readme_path));
}

void MainWindow::on_actionAuthors_triggered() { form.show(); }

void MainWindow::on_translateButton_clicked() {
  ui->widget->offsets.x = ui->trans_x_line->text().toDouble();
  ui->widget->offsets.y = ui->trans_y_line->text().toDouble();
  ui->widget->offsets.z = ui->trans_z_line->text().toDouble();
  ui->widget->translate();
  ui->widget->update();
}

void MainWindow::on_rotateButton_clicked() {
  ui->widget->angles.x = ui->rotate_x_line->text().toDouble();
  ui->widget->angles.y = ui->rotate_y_line->text().toDouble();
  ui->widget->angles.z = ui->rotate_z_line->text().toDouble();
  ui->widget->rotate();
  ui->widget->update();
}

void MainWindow::on_scaleButton_clicked() {
  ui->widget->scale = ui->scale_line->text().toDouble();
  ui->widget->scale_model();
  ui->widget->update();
}

void MainWindow::on_none_radio_clicked(bool checked) {
  if (checked) {
    ui->widget->vertice_type = 0;
  }
  ui->widget->update();
}

void MainWindow::on_circle_radio_clicked(bool checked) {
  if (checked) {
    ui->widget->vertice_type = 1;
  }
  ui->widget->update();
}

void MainWindow::on_square_radio_clicked(bool checked) {
  if (checked) {
    ui->widget->vertice_type = 2;
  }
  ui->widget->update();
}

void MainWindow::on_vert_size_line_textChanged(const QString &arg1) {
  if (!arg1.isEmpty()) {
    ui->widget->vertices_size = ui->vert_size_line->text().toDouble();
    ui->widget->update();
  }
}

void MainWindow::on_vertColorButton_clicked() {
  ui->widget->vertices_color =
      QColorDialog::getColor(Qt::green, this, "Vertices Color");
}

void MainWindow::on_edgeColorButton_clicked() {
  ui->widget->edges_color =
      QColorDialog::getColor(Qt::green, this, "Edges Color");
}

void MainWindow::on_smooth_radio_clicked(bool checked) {
  if (checked) {
    ui->widget->line_type = false;
  }
  ui->widget->update();
}

void MainWindow::on_stippled_radio_clicked(bool checked) {
  if (checked) {
    ui->widget->line_type = true;
  }
  ui->widget->update();
}

void MainWindow::on_thick_line_textChanged(const QString &arg1) {
  if (!arg1.isEmpty()) {
    ui->widget->line_thickness = ui->thick_line->text().toDouble();
    ui->widget->update();
  }
}

void MainWindow::on_pushButton_2_clicked() {
  ui->widget->background_color =
      QColorDialog::getColor(Qt::white, this, "Background Color");
}

void MainWindow::on_orthogonalRadio_clicked(bool checked) {
  if (checked) {
    ui->widget->isOrthogonal = true;
  }
  ui->widget->update();
}

void MainWindow::on_perspectiveRadio_clicked(bool checked) {
  if (checked) {
    ui->widget->isOrthogonal = false;
  }
  ui->widget->update();
}

void MainWindow::save_settings() {
  settings->setValue("vertices_color", ui->widget->vertices_color);
  settings->setValue("background_color", ui->widget->background_color);
  settings->setValue("edge_color", ui->widget->edges_color);
  settings->setValue("projection_type", ui->widget->isOrthogonal);
  settings->setValue("line_type", ui->widget->line_type);
  settings->setValue("line_thickness", ui->widget->line_thickness);
  settings->setValue("vertice_type", ui->widget->vertice_type);
  settings->setValue("vertice_size", ui->widget->vertices_size);
}

void MainWindow::load_settings() {
  QVariant backgoundColorSetting =
      settings->value("background_color", QColor(Qt::black));
  ui->widget->background_color = backgoundColorSetting.value<QColor>();
  QVariant vertice_color = settings->value("vertices_color", QColor(Qt::red));
  ui->widget->vertices_color = vertice_color.value<QColor>();
  QVariant edgesColor = settings->value("edge_color", QColor(Qt::red));
  ui->widget->edges_color = edgesColor.value<QColor>();
  ui->widget->isOrthogonal = settings->value("projection_type", true).toBool();
  if (ui->widget->isOrthogonal) {
    ui->orthogonalRadio->setChecked(true);
  } else {
    ui->perspectiveRadio->setChecked(true);
  }
  ui->widget->line_type = settings->value("line_type", true).toBool();
  if (!ui->widget->line_type) {
    ui->smooth_radio->setChecked(true);
  } else {
    ui->stippled_radio->setChecked(true);
  }
  ui->widget->line_thickness = settings->value("line_thickness", 1).toDouble();
  ui->widget->vertice_type = settings->value("vertice_type", 1).toInt();
  if (ui->widget->vertice_type == 0) {
    ui->none_radio->setChecked(true);
  } else if (ui->widget->vertice_type == 1) {
    ui->circle_radio->setChecked(true);
  } else {
    ui->square_radio->setChecked(true);
  }
  ui->widget->vertices_size = settings->value("vertice_size", 1).toDouble();
}

void MainWindow::on_actiongif_triggered() {
  gif = new QGifImage;
  frame = new QImage;
  timer = new QTimer(this);
  time = 0;
  connect(timer, SIGNAL(timeout()), this, SLOT(saveGifFrame()));
  timer->start(100);
}

void MainWindow::saveGifFrame() {
  time++;
  *frame = ui->widget->grabFramebuffer();
  *frame = frame->scaled(640, 480);
  gif->addFrame(*frame, 100);
  if (time == 50) {
    timer->stop();
    gifSavePath = NULL;
    gifSavePath = QFileDialog::getSaveFileName(this, NULL, NULL, "GIF (*.gif)");
    if (!gifSavePath.isNull()) gif->save(gifSavePath);
  }
}

void MainWindow::on_actionImage_triggered() {
  QImage frame = ui->widget->grabFramebuffer();
  QString imgSavePath =
      QFileDialog::getSaveFileName(this, NULL, NULL, "BMP JPEG (*.bmp *.jpeg)");
  frame.save(imgSavePath);
}
