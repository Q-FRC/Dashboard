/********************************************************************************
** Form generated from reading UI file 'CameraSelectionDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERASELECTIONDIALOG_H
#define UI_CAMERASELECTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CameraSelectionDialog
{
public:
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *CameraSelectionDialog)
    {
        if (CameraSelectionDialog->objectName().isEmpty())
            CameraSelectionDialog->setObjectName("CameraSelectionDialog");
        CameraSelectionDialog->resize(480, 640);
        verticalLayout = new QVBoxLayout(CameraSelectionDialog);
        verticalLayout->setObjectName("verticalLayout");
        listWidget = new QListWidget(CameraSelectionDialog);
        listWidget->setObjectName("listWidget");

        verticalLayout->addWidget(listWidget);

        buttonBox = new QDialogButtonBox(CameraSelectionDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(CameraSelectionDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), CameraSelectionDialog, SLOT(emitCamera()));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, CameraSelectionDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(CameraSelectionDialog);
    } // setupUi

    void retranslateUi(QDialog *CameraSelectionDialog)
    {
        CameraSelectionDialog->setWindowTitle(QCoreApplication::translate("CameraSelectionDialog", "Select Camera...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CameraSelectionDialog: public Ui_CameraSelectionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERASELECTIONDIALOG_H
