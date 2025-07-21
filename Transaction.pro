QT += gui
QT += core
QT += printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

HEADERS += \
    include/models/customermodel.h \
    include/widgets/accountview.h \
    include/elements/passwordedit.h \
    include/panels/customerpanel.h \
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
    include/users/admin.h \
    include/users/customer.h \
    include/users/user.h \
    include/widgets/abstractpanel.h \
    include/widgets/transferpanel.h \
    include/widgets/useredit.h \
    include/widgets/passwordeditor.h


SOURCES += \
    src/models/customermodel.cpp \
    src/widgets/passwordeditor.cpp \
    src/widgets/accountview.cpp \
    src/elements/passwordedit.cpp \
    src/panels/customerpanel.cpp \
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
    src/users/admin.cpp \
    src/users/customer.cpp \
    src/users/user.cpp \
    src/widgets/abstractpanel.cpp \
    src/widgets/transferpanel.cpp \
    src/widgets/useredit.cpp

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    ui/widgets/passwordeditor.ui \
    ui/widgets/accountview.ui \
    ui/panels/customerpanel.ui \
    ui/widgets/transferpanel.ui \
    ui/widgets/useredit.ui

RESOURCES += \
    resources.qrc
