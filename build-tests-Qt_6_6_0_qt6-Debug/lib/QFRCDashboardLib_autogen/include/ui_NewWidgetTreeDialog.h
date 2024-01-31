/********************************************************************************
** Form generated from reading UI file 'NewWidgetTreeDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWWIDGETTREEDIALOG_H
#define UI_NEWWIDGETTREEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_NewWidgetTreeDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTreeWidget *tree;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *NewWidgetTreeDialog)
    {
        if (NewWidgetTreeDialog->objectName().isEmpty())
            NewWidgetTreeDialog->setObjectName("NewWidgetTreeDialog");
        NewWidgetTreeDialog->resize(634, 629);
        verticalLayout = new QVBoxLayout(NewWidgetTreeDialog);
        verticalLayout->setObjectName("verticalLayout");
        tree = new QTreeWidget(NewWidgetTreeDialog);
        tree->setObjectName("tree");
        tree->header()->setDefaultSectionSize(100);
        tree->header()->setStretchLastSection(false);

        verticalLayout->addWidget(tree);

        buttonBox = new QDialogButtonBox(NewWidgetTreeDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(NewWidgetTreeDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, NewWidgetTreeDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(NewWidgetTreeDialog);
    } // setupUi

    void retranslateUi(QDialog *NewWidgetTreeDialog)
    {
        NewWidgetTreeDialog->setWindowTitle(QCoreApplication::translate("NewWidgetTreeDialog", "Select Widget...", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = tree->headerItem();
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("NewWidgetTreeDialog", "Type", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("NewWidgetTreeDialog", "Topic", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NewWidgetTreeDialog: public Ui_NewWidgetTreeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWWIDGETTREEDIALOG_H
