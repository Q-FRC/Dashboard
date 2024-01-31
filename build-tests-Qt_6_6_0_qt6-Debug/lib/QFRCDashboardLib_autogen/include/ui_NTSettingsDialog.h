/********************************************************************************
** Form generated from reading UI file 'NTSettingsDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NTSETTINGSDIALOG_H
#define UI_NTSETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_NTSettingsDialog
{
public:
    QFormLayout *formLayout;
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QSpinBox *spinBox;
    QCheckBox *checkBox;
    QLineEdit *lineEdit;

    void setupUi(QDialog *NTSettingsDialog)
    {
        if (NTSettingsDialog->objectName().isEmpty())
            NTSettingsDialog->setObjectName("NTSettingsDialog");
        NTSettingsDialog->resize(440, 129);
        formLayout = new QFormLayout(NTSettingsDialog);
        formLayout->setObjectName("formLayout");
        buttonBox = new QDialogButtonBox(NTSettingsDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(3, QFormLayout::LabelRole, buttonBox);

        label = new QLabel(NTSettingsDialog);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        label_2 = new QLabel(NTSettingsDialog);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        label_3 = new QLabel(NTSettingsDialog);
        label_3->setObjectName("label_3");

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        spinBox = new QSpinBox(NTSettingsDialog);
        spinBox->setObjectName("spinBox");
        spinBox->setMinimum(1);
        spinBox->setMaximum(65535);
        spinBox->setValue(5810);

        formLayout->setWidget(2, QFormLayout::FieldRole, spinBox);

        checkBox = new QCheckBox(NTSettingsDialog);
        checkBox->setObjectName("checkBox");

        formLayout->setWidget(1, QFormLayout::FieldRole, checkBox);

        lineEdit = new QLineEdit(NTSettingsDialog);
        lineEdit->setObjectName("lineEdit");

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit);


        retranslateUi(NTSettingsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), NTSettingsDialog, SLOT(serializeData()));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, NTSettingsDialog, qOverload<>(&QDialog::reject));
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, NTSettingsDialog, qOverload<>(&QDialog::accept));

        QMetaObject::connectSlotsByName(NTSettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *NTSettingsDialog)
    {
        NTSettingsDialog->setWindowTitle(QCoreApplication::translate("NTSettingsDialog", "NetworkTables Settings", nullptr));
        label->setText(QCoreApplication::translate("NTSettingsDialog", "Server Address:", nullptr));
#if QT_CONFIG(whatsthis)
        label_2->setWhatsThis(QCoreApplication::translate("NTSettingsDialog", "Whether or not the server address is a team number.", nullptr));
#endif // QT_CONFIG(whatsthis)
        label_2->setText(QCoreApplication::translate("NTSettingsDialog", "Use Team Number?", nullptr));
        label_3->setText(QCoreApplication::translate("NTSettingsDialog", "Port:", nullptr));
        checkBox->setText(QString());
        lineEdit->setText(QCoreApplication::translate("NTSettingsDialog", "0.0.0.0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NTSettingsDialog: public Ui_NTSettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NTSETTINGSDIALOG_H
