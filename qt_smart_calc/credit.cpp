#include "credit.h"

#include "ui_credit.h"

Credit::Credit(QWidget *parent) : QDialog(parent), ui(new Ui::Credit) {
  ui->setupUi(this);
}

Credit::~Credit() { delete ui; }

void Credit::on_pushButton_clicked() {
  double principal =
      (ui->sum->toPlainText()).toDouble();  // Основная сумма кредита
  double interest_rate =
      (ui->percentage->toPlainText()).toDouble();  // Процентная ставка
  int num = (ui->term->toPlainText()).toInt();  // Срок кредита в месяцах

  if (ui->annuities->isChecked()) {
    double monthly_interest_rate = interest_rate / 12 / 100;

    // Расчет ежемесячного платежа
    double monthly_payment = (principal * monthly_interest_rate *
                              pow(1 + monthly_interest_rate, num)) /
                             (pow(1 + monthly_interest_rate, num) - 1);
    // Расчет общей суммы платежей
    double total_payment = monthly_payment * num;

    // Рассчет переплаьы по кредиту
    double overpayment = total_payment - principal;

    ui->monthly_payment->setText(QString::number(monthly_payment, 'f', 2));
    ui->total_payment->setText(QString::number(total_payment, 'f', 2));
    ui->overpayment->setText(QString::number(overpayment, 'f', 2));
  }
  if (ui->differentiated->isChecked()) {
    double principal_r = principal;
    double monthly_payment = principal / num;
    double monthly_interest_rate = interest_rate / 100 / 12;
    double total_payment = 0;
    double pay[num];
    for (int i = 1; i <= num; i++) {
      double interest = principal * monthly_interest_rate;
      double payment = monthly_payment + interest;
      pay[i] = payment;
      total_payment += payment;
      principal -= monthly_payment;
    }
    double minPayment = pay[1];
    double maxPayment = pay[1];
    for (int i = 1; i <= num; i++) {
      if (pay[i] < minPayment) {
        minPayment = pay[i];
      }
      if (pay[i] > maxPayment) {
        maxPayment = pay[i];
      }
    }
    char res[100];
    sprintf(res, "%.2lf ... %.2lf", maxPayment, minPayment);
    ui->monthly_payment->setText((QString)res);
    double overpayment = total_payment - principal_r;
    ui->total_payment->setText(QString::number(total_payment, 'f', 2));
    ui->overpayment->setText(QString::number(overpayment, 'f', 2));
  }
}

void Credit::on_clean_clicked() {
  ui->monthly_payment->setText("");
  ui->total_payment->setText("");
  ui->overpayment->setText("");
  ui->sum->setPlainText("");
  ui->percentage->setPlainText("");
  ui->term->setPlainText("");
}
