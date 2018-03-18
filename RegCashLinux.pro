#-------------------------------------------------
#
# Project created by QtCreator 2017-11-19T14:07:56
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RegCashLinux
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    regcashmain.cpp \
    formpagamento.cpp \
    main.cpp \
    formarticoli.cpp \
    formimpostazioni.cpp \
    dbutility.cpp \
    formsconti.cpp \
    formscontofisso.cpp \
    formreport.cpp

HEADERS += \
    customtable.h \
    formpagamento.h \
    formarticoli.h \
    regcashmain.h \
    formimpostazioni.h \
    tipologiepagamento.h \
    dbutility.h \
    formsconti.h \
    formscontofisso.h \
    checkshop.h \
    azioni.h \
    errori.h \
    formreport.h

FORMS += \
        regcashmain.ui \
    formarticoli.ui \
    formpagamento.ui \
    formimpostazioni.ui \
    formsconti.ui \
    formscontofisso.ui \
    formreport.ui

RESOURCES += \
    regcashresource.qrc

DISTFILES += \
    config/application.ini \
    db/regcash.sqlite \
    report/read.me

