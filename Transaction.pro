QT += gui core
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

HEADERS += \
    include/accounts/depositaccount.h \
    include/accounts/loanaccount.h \
    include/accounts/transactionaccount.h \
    include/general.h \
    include/accounts/abstractaccount.h


SOURCES += \
    main.cpp \
    src/accounts/abstractaccount.cpp \
    src/accounts/depositaccount.cpp \
    src/accounts/loanaccount.cpp \
    src/accounts/transactionaccount.cpp \
    src/general.cpp

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
