#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <iostream>
#ifdef __cplusplus

extern "C" {
#endif
#include "../s21_calc_funcs/s21_calc.h"

#ifdef __cplusplus
}
#endif

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

 private:
  Ui::MainWindow *ui;
  QVector<double> x, y;

 private slots:
  void digits_numbers();
  void on_pushButton_point_clicked();
  void operations();
  void on_pushButton_AC_clicked();
  void math_func();
  void on_pushButton_left_clicked();
  void on_pushButton_right_clicked();
  void on_pushButton_res_clicked();
  void on_pushButton_del_clicked();
  void on_pushButton_plot_clicked();
  void on_pushButton_clean_plot_clicked();
  void on_pushButton_x_clicked();
};
#endif  // MAINWINDOW_H
