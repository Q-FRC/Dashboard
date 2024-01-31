/********************************************************************************
** Form generated from reading UI file 'PreferencesDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREFERENCESDIALOG_H
#define UI_PREFERENCESDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_PreferencesDialog
{
public:
    QFormLayout *formLayout;
    QLabel *label;
    QComboBox *choices;
    QDialogButtonBox *buttonBox;
    QLabel *label_2;
    QCheckBox *lastLoaded;

    void setupUi(QDialog *PreferencesDialog)
    {
        if (PreferencesDialog->objectName().isEmpty())
            PreferencesDialog->setObjectName("PreferencesDialog");
        PreferencesDialog->resize(388, 97);
        formLayout = new QFormLayout(PreferencesDialog);
        formLayout->setObjectName("formLayout");
        label = new QLabel(PreferencesDialog);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        choices = new QComboBox(PreferencesDialog);
        choices->addItem(QString());
        choices->addItem(QString());
        choices->addItem(QString());
        choices->addItem(QString());
        choices->setObjectName("choices");

        formLayout->setWidget(0, QFormLayout::FieldRole, choices);

        buttonBox = new QDialogButtonBox(PreferencesDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(2, QFormLayout::SpanningRole, buttonBox);

        label_2 = new QLabel(PreferencesDialog);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        lastLoaded = new QCheckBox(PreferencesDialog);
        lastLoaded->setObjectName("lastLoaded");

        formLayout->setWidget(1, QFormLayout::FieldRole, lastLoaded);


        retranslateUi(PreferencesDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), PreferencesDialog, SLOT(emitData()));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, PreferencesDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(PreferencesDialog);
    } // setupUi

    void retranslateUi(QDialog *PreferencesDialog)
    {
        PreferencesDialog->setWindowTitle(QCoreApplication::translate("PreferencesDialog", "QFRCDashboard Preferences", nullptr));
        label->setText(QCoreApplication::translate("PreferencesDialog", "Style:", nullptr));
        choices->setItemText(0, QCoreApplication::translate("PreferencesDialog", "Light", nullptr));
        choices->setItemText(1, QCoreApplication::translate("PreferencesDialog", "Dark", nullptr));
        choices->setItemText(2, QCoreApplication::translate("PreferencesDialog", "Light Purple", nullptr));
        choices->setItemText(3, QCoreApplication::translate("PreferencesDialog", "Dark Purple", nullptr));

        label_2->setText(QCoreApplication::translate("PreferencesDialog", "Default to last loaded file?", nullptr));
        lastLoaded->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PreferencesDialog: public Ui_PreferencesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREFERENCESDIALOG_H
