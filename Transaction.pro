QT += gui core
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

HEADERS += \
    include/account.h \
    include/accounts/depositaccount.h \
    include/accounts/loanaccount.h \
    include/accounts/transactionaccount.h \
    include/core/cashtransaction.h \
    include/core/errors.h \
    include/delegates/accountdelegate.h \
    include/entity.h \
    include/general.h \
    include/accounts/abstractaccount.h \
    include/models/accountlistmodel.h \
    include/users/admin.h \
    include/users/customer.h \
    include/users/user.h \
    include/widgets/abstractpanel.h \
    include/widgets/transferpanel.h


SOURCES += \
    main.cpp \
    src/account.cpp \
    src/accounts/abstractaccount.cpp \
    src/accounts/depositaccount.cpp \
    src/accounts/loanaccount.cpp \
    src/accounts/transactionaccount.cpp \
    src/core/cashtransaction.cpp \
    src/delegates/accountdelegate.cpp \
    src/entity.cpp \
    src/general.cpp \
    src/models/accountlistmodel.cpp \
    src/users/admin.cpp \
    src/users/customer.cpp \
    src/users/user.cpp \
    src/widgets/abstractpanel.cpp \
    src/widgets/transferpanel.cpp

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    ui/widgets/transferpanel.ui

RESOURCES += \
    resources.qrc
