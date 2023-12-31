QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../s21_calc_funcs/main_calc.c \
    ../s21_calc_funcs/s21_base_func.c \
    ../s21_calc_funcs/s21_calc.c \
    ../s21_calc_funcs/s21_convert.c \
    ../s21_calc_funcs/s21_error.c \
    ../s21_calc_funcs/s21_parcer.c \
    credit.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    ../s21_calc_funcs/s21_calc.h \
    credit.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    credit.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
