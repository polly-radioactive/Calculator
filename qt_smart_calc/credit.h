#ifndef CREDIT_H
#define CREDIT_H

#include <QDialog>

extern "C" {

#include <stdio.h>

#include "math.h"
}

namespace Ui {
class Credit;
}

class Credit : public QDialog {
  Q_OBJECT

 public:
  explicit Credit(QWidget *parent = nullptr);
  ~Credit();

 private slots:
  void on_pushButton_clicked();

  void on_clean_clicked();

 private:
  Ui::Credit *ui;
};

#endif  // CREDIT_H
