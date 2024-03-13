QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Expression.cpp \
    VariableSet.cpp \
    clearVar.cpp \
    delButton.cpp \
    funcTextChange.cpp \
    hidebutton.cpp \
    main.cpp \
    qcustomplot.cpp \
    varTextChange.cpp \
    viewer.cpp

HEADERS += \
    Expression.h \
    MyVector.h \
    P2_Of_Y.h \
    Union.h \
    VariableSet.h \
    function.h \
    qcustomplot.h \
    viewer.h

FORMS += \
    viewer.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

RC_ICONS = main.ico
