QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addstudent.cpp \
    authwindow.cpp \
    course.cpp \
    displaycourse.cpp \
    editstdgrade.cpp \
    main.cpp \
    mainwindow.cpp \
    person.cpp \
    professor.cpp \
    signupwindow.cpp \
    student.cpp \
    studentstab.cpp \
    professortab.cpp \
    addprofessor.cpp \
    addcourse2.cpp \
    card.cpp \
    coursestab.cpp \
    editcourse.cpp \
    editprofessor.cpp \
    editstudent.cpp

HEADERS += \
    addstudent.h \
    authwindow.h \
    course.h \
    displaycourse.h \
    editstdgrade.h \
    mainwindow.h \
    person.h \
    professor.h \
    signupwindow.h \
    student.h \
    studentstab.h \
    professortab.h \
    addprofessor.h \
    addcourse2.h \
    card.h \
    coursestab.h \
    editcourse.h \
    editprofessor.h \
    editstudent.h


FORMS += \
    addstudent.ui \
    authwindow.ui \
    displaycourse.ui \
    editstdgrade.ui \
    mainwindow.ui \
    signupwindow.ui \
    studentstab.ui \
    professortab.ui \
    addprofessor.ui \
    addcourse2.ui \
    coursestab.ui \
    card.ui \
    editcourse.ui \
    editprofessor.ui \
    editstudent.ui

RESOURCES += \
    resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
