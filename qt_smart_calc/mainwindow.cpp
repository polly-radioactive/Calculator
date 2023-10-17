#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(operations()));

  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(math_func()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(math_func()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(math_func()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(math_func()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(math_func()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(math_func()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(math_func()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(math_func()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(math_func()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label;
  new_label = ui->result_show->text() + button->text();
  ui->result_show->setText(new_label);
}

void MainWindow::on_pushButton_point_clicked() {
  ui->result_show->setText(ui->result_show->text() + ".");
}

void MainWindow::operations() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label;
  new_label = ui->result_show->text() + button->text();
  ui->result_show->setText(new_label);
}

void MainWindow::math_func() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label;
  new_label = ui->result_show->text() + button->text() + "(";
  ui->result_show->setText(new_label);
}

void MainWindow::on_pushButton_AC_clicked() { ui->result_show->setText(""); }

void MainWindow::on_pushButton_left_clicked() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label;
  new_label = ui->result_show->text() + button->text();
  ui->result_show->setText(new_label);
}

void MainWindow::on_pushButton_right_clicked() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label;
  new_label = ui->result_show->text() + button->text();
  ui->result_show->setText(new_label);
}

void MainWindow::on_pushButton_res_clicked() {
  QString new_label;
  double x_v;
  QString x_label = ui->x_value->toPlainText();
  x_v = x_label.toDouble();
  new_label = ui->result_show->text() + '=';
  char *str = (char *)new_label.toLocal8Bit().constData();
  double result = 0;
  N stack;
  stack.top = -1;
  parser(str, &stack);
  stack = inverse(&stack);
  int flag = find_error(&stack);
  if (flag == SUCCESS) {
    stack = convert_to_reverse_polish_notation(&stack, x_v);
    N final;
    final.top = -1;
    flag = calc_reverse_polish_notation(&stack, &final);
    if (flag == SUCCESS) {
      result = final.value[final.top];
      ui->result_show->setText(QString::number(result, 'f', 7));
    } else {
      ui->result_show->setText("Error");
    }
    clean_stack(final);
  } else {
    ui->result_show->setText("Error");
  }
  clean_stack(stack);
}

void MainWindow::on_pushButton_del_clicked() {
  QString s = ui->result_show->text();
  if (s.length() > 0) {
    QString new_label = s.remove(s.length() - 1, 1);
    ui->result_show->setText(new_label);
  }
}

void MainWindow::on_pushButton_plot_clicked() {
  ui->widget->clearGraphs();
  x.clear();
  y.clear();
  ui->widget->replot();
  double xBegin, xEnd, h, X, Y;
  int flag;
  double x_mi = (ui->min_x_value->toPlainText()).toDouble();
  double x_ma = (ui->max_x_value->toPlainText()).toDouble();
  double y_mi = (ui->min_y_value->toPlainText()).toDouble();
  double y_ma = (ui->max_y_value->toPlainText()).toDouble();
  h = 0.1;
  xBegin = -9;
  xEnd = 9 + h;
  QString new_label;
  new_label = ui->result_show->text() + '=';
  for (X = xBegin; X <= xEnd; X += h) {
    char *str = (char *)new_label.toLocal8Bit().constData();
    N stack;
    stack.top = -1;
    parser(str, &stack);
    stack = inverse(&stack);
    flag = find_error(&stack);
    if (flag == SUCCESS) {
      stack = convert_to_reverse_polish_notation(&stack, X);
      ui->widget->xAxis->setRange(x_mi, x_ma);
      ui->widget->yAxis->setRange(y_mi, y_ma);
      N final;
      final.top = -1;
      flag = calc_reverse_polish_notation(&stack, &final);
      if (flag == SUCCESS) {
        Y = final.value[final.top];
        x.push_back(X);
        y.push_back(Y);
      }
    }
  }
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
}

void MainWindow::on_pushButton_clean_plot_clicked() {
  ui->widget->clearGraphs();
  x.clear();
  y.clear();
  ui->widget->replot();
  ui->result_show->setText("");
  ui->min_x_value->setPlainText("-10");
  ui->max_x_value->setPlainText("10");
  ui->min_y_value->setPlainText("-10");
  ui->max_y_value->setPlainText("10");
  ui->x_value->setPlainText("0");
}

void MainWindow::on_pushButton_x_clicked() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label;
  new_label = ui->result_show->text() + button->text();
  ui->result_show->setText(new_label);
}
