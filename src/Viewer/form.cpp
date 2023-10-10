#include "form.h"

#include "ui_form.h"

Form::Form(QWidget *parent) : QWidget(parent), ui(new Ui::Form) {
  setFixedSize(541, 672);
  ui->setupUi(this);
}

Form::~Form() { delete ui; }
