/********************************************************************************
** Form generated from reading UI file 'TabMaxSizeDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABMAXSIZEDIALOG_H
#define UI_TABMAXSIZEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_TabMaxSizeDialog
{
public:
    QFormLayout *formLayout;
    QLabel *label;
    QSpinBox *yBox;
    QLabel *label_2;
    QSpinBox *xBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *TabMaxSizeDialog)
    {
        if (TabMaxSizeDialog->objectName().isEmpty())
            TabMaxSizeDialog->setObjectName("TabMaxSizeDialog");
        TabMaxSizeDialog->resize(184, 107);
        formLayout = new QFormLayout(TabMaxSizeDialog);
        formLayout->setObjectName("formLayout");
        label = new QLabel(TabMaxSizeDialog);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        yBox = new QSpinBox(TabMaxSizeDialog);
        yBox->setObjectName("yBox");

        formLayout->setWidget(0, QFormLayout::FieldRole, yBox);

        label_2 = new QLabel(TabMaxSizeDialog);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        xBox = new QSpinBox(TabMaxSizeDialog);
        xBox->setObjectName("xBox");

        formLayout->setWidget(1, QFormLayout::FieldRole, xBox);

        buttonBox = new QDialogButtonBox(TabMaxSizeDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(2, QFormLayout::SpanningRole, buttonBox);


        retranslateUi(TabMaxSizeDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), TabMaxSizeDialog, SLOT(emitData()));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, TabMaxSizeDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(TabMaxSizeDialog);
    } // setupUi

    void retranslateUi(QDialog *TabMaxSizeDialog)
    {
        TabMaxSizeDialog->setWindowTitle(QCoreApplication::translate("TabMaxSizeDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("TabMaxSizeDialog", "Rows:", nullptr));
        label_2->setText(QCoreApplication::translate("TabMaxSizeDialog", "Columns:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TabMaxSizeDialog: public Ui_TabMaxSizeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABMAXSIZEDIALOG_H
