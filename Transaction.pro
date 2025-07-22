QT += gui core
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

HEADERS += \
    include/dialogs/accounteditor.h \
    include/dialogs/accountpasswordeditor.h \
    include/models/customermodel.h \
    include/dialogs/accountview.h \
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
    include/dialogs/transferpanel.h \
    include/dialogs/useredit.h


SOURCES += \
    src/dialogs/accounteditor.cpp \
    src/dialogs/accountpasswordeditor.cpp \
    src/models/customermodel.cpp \
    src/dialogs/accountview.cpp \
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
    src/dialogs/transferpanel.cpp \
    src/dialogs/useredit.cpp

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    ui/dialogs/accounteditor.ui \
    ui/dialogs/accountpasswordeditor.ui \
    ui/dialogs/accountview.ui \
    ui/panels/customerpanel.ui \
    ui/dialogs/transferpanel.ui \
    ui/dialogs/useredit.ui

RESOURCES += \
    resources.qrc
