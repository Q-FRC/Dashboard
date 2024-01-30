/********************************************************************************
** Form generated from reading UI file 'WidgetDialogGenerator.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETDIALOGGENERATOR_H
#define UI_WIDGETDIALOGGENERATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_WidgetDialogGenerator
{
public:
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *nameInput;
    QSpinBox *rowInput;
    QSpinBox *colInput;
    QSpinBox *rowSpanInput;
    QSpinBox *colSpanInput;

    void setupUi(QDialog *WidgetDialogGenerator)
    {
        if (WidgetDialogGenerator->objectName().isEmpty())
            WidgetDialogGenerator->setObjectName("WidgetDialogGenerator");
        WidgetDialogGenerator->resize(444, 171);
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WidgetDialogGenerator->sizePolicy().hasHeightForWidth());
        WidgetDialogGenerator->setSizePolicy(sizePolicy);
        formLayout = new QFormLayout(WidgetDialogGenerator);
        formLayout->setObjectName("formLayout");
        label = new QLabel(WidgetDialogGenerator);
        label->setObjectName("label");
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        formLayout->setWidget(1, QFormLayout::LabelRole, label);

        label_2 = new QLabel(WidgetDialogGenerator);
        label_2->setObjectName("label_2");
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        label_3 = new QLabel(WidgetDialogGenerator);
        label_3->setObjectName("label_3");
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);

        formLayout->setWidget(3, QFormLayout::LabelRole, label_3);

        label_4 = new QLabel(WidgetDialogGenerator);
        label_4->setObjectName("label_4");
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);

        formLayout->setWidget(4, QFormLayout::LabelRole, label_4);

        label_5 = new QLabel(WidgetDialogGenerator);
        label_5->setObjectName("label_5");
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);

        formLayout->setWidget(0, QFormLayout::LabelRole, label_5);

        nameInput = new QLineEdit(WidgetDialogGenerator);
        nameInput->setObjectName("nameInput");

        formLayout->setWidget(0, QFormLayout::FieldRole, nameInput);

        rowInput = new QSpinBox(WidgetDialogGenerator);
        rowInput->setObjectName("rowInput");
        rowInput->setMaximum(1000);

        formLayout->setWidget(1, QFormLayout::FieldRole, rowInput);

        colInput = new QSpinBox(WidgetDialogGenerator);
        colInput->setObjectName("colInput");
        colInput->setMaximum(1000);

        formLayout->setWidget(2, QFormLayout::FieldRole, colInput);

        rowSpanInput = new QSpinBox(WidgetDialogGenerator);
        rowSpanInput->setObjectName("rowSpanInput");
        rowSpanInput->setMaximum(1000);
        rowSpanInput->setValue(1);

        formLayout->setWidget(3, QFormLayout::FieldRole, rowSpanInput);

        colSpanInput = new QSpinBox(WidgetDialogGenerator);
        colSpanInput->setObjectName("colSpanInput");
        colSpanInput->setMaximum(1000);
        colSpanInput->setValue(1);

        formLayout->setWidget(4, QFormLayout::FieldRole, colSpanInput);


        retranslateUi(WidgetDialogGenerator);

        QMetaObject::connectSlotsByName(WidgetDialogGenerator);
    } // setupUi

    void retranslateUi(QDialog *WidgetDialogGenerator)
    {
        WidgetDialogGenerator->setWindowTitle(QCoreApplication::translate("WidgetDialogGenerator", "New Widget...", nullptr));
        label->setText(QCoreApplication::translate("WidgetDialogGenerator", "Row:", nullptr));
        label_2->setText(QCoreApplication::translate("WidgetDialogGenerator", "Column:", nullptr));
        label_3->setText(QCoreApplication::translate("WidgetDialogGenerator", "Row Span:", nullptr));
        label_4->setText(QCoreApplication::translate("WidgetDialogGenerator", "Column Span:", nullptr));
        label_5->setText(QCoreApplication::translate("WidgetDialogGenerator", "Name:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WidgetDialogGenerator: public Ui_WidgetDialogGenerator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETDIALOGGENERATOR_H
